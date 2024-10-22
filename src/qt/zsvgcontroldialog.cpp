// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2018 The Salvage developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "zsvgcontroldialog.h"
#include "ui_zsvgcontroldialog.h"

#include "accumulators.h"
#include "main.h"
#include "walletmodel.h"

using namespace std;
using namespace libzerocoin;

std::set<std::string> ZSvgControlDialog::setSelectedMints;
std::set<CMintMeta> ZSvgControlDialog::setMints;

bool CZSvgControlWidgetItem::operator<(const QTreeWidgetItem &other) const {
    int column = treeWidget()->sortColumn();
    if (column == ZSvgControlDialog::COLUMN_DENOMINATION || column == ZSvgControlDialog::COLUMN_VERSION || column == ZSvgControlDialog::COLUMN_CONFIRMATIONS)
        return data(column, Qt::UserRole).toLongLong() < other.data(column, Qt::UserRole).toLongLong();
    return QTreeWidgetItem::operator<(other);
}


ZSvgControlDialog::ZSvgControlDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::ZSvgControlDialog),
    model(0)
{
    ui->setupUi(this);
    setMints.clear();
    privacyDialog = (PrivacyDialog*)parent;

    // click on checkbox
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(updateSelection(QTreeWidgetItem*, int)));

    // push select/deselect all button
    connect(ui->pushButtonAll, SIGNAL(clicked()), this, SLOT(ButtonAllClicked()));
}

ZSvgControlDialog::~ZSvgControlDialog()
{
    delete ui;
}

void ZSvgControlDialog::setModel(WalletModel *model)
{
    this->model = model;
    updateList();
}


//Update the tree widget
void ZSvgControlDialog::updateList()
{
    // need to prevent the slot from being called each time something is changed
    ui->treeWidget->blockSignals(true);
    ui->treeWidget->clear();

    // add a top level item for each denomination
    QFlags<Qt::ItemFlag> flgTristate = Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsTristate;
    map<libzerocoin::CoinDenomination, int> mapDenomPosition;
    for (auto denom : libzerocoin::zerocoinDenomList) {
        CZSvgControlWidgetItem* itemDenom(new CZSvgControlWidgetItem);
        ui->treeWidget->addTopLevelItem(itemDenom);

        //keep track of where this is positioned in tree widget
        mapDenomPosition[denom] = ui->treeWidget->indexOfTopLevelItem(itemDenom);

        itemDenom->setFlags(flgTristate);
        itemDenom->setText(COLUMN_DENOMINATION, QString::number(denom));
        itemDenom->setData(COLUMN_DENOMINATION, Qt::UserRole, QVariant((qlonglong) denom));
    }

    // select all unused coins - including not mature. Update status of coins too.
    std::set<CMintMeta> set;
    model->listZerocoinMints(set, true, false, true);
    this->setMints = set;

    //populate rows with mint info
    int nBestHeight = chainActive.Height();
    map<CoinDenomination, int> mapMaturityHeight = GetMintMaturityHeight();
    for (const CMintMeta& mint : setMints) {
        // assign this mint to the correct denomination in the tree view
        libzerocoin::CoinDenomination denom = mint.denom;
        CZSvgControlWidgetItem *itemMint = new CZSvgControlWidgetItem(ui->treeWidget->topLevelItem(mapDenomPosition.at(denom)));

        // if the mint is already selected, then it needs to have the checkbox checked
        std::string strPubCoinHash = mint.hashPubcoin.GetHex();

        if (setSelectedMints.count(strPubCoinHash))
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Checked);
        else
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Unchecked);

        itemMint->setText(COLUMN_DENOMINATION, QString::number(mint.denom));
        itemMint->setData(COLUMN_DENOMINATION, Qt::UserRole, QVariant((qlonglong) denom));
        itemMint->setText(COLUMN_PUBCOIN, QString::fromStdString(strPubCoinHash));
        itemMint->setText(COLUMN_VERSION, QString::number(mint.nVersion));
        itemMint->setData(COLUMN_VERSION, Qt::UserRole, QVariant((qlonglong) mint.nVersion));

        int nConfirmations = (mint.nHeight ? nBestHeight - mint.nHeight : 0);
        if (nConfirmations < 0) {
            // Sanity check
            nConfirmations = 0;
        }

        itemMint->setText(COLUMN_CONFIRMATIONS, QString::number(nConfirmations));
        itemMint->setData(COLUMN_CONFIRMATIONS, Qt::UserRole, QVariant((qlonglong) nConfirmations));

        // check for maturity
        bool isMature = false;
        if (mapMaturityHeight.count(mint.denom))
            isMature = mint.nHeight < mapMaturityHeight.at(denom);

        // disable selecting this mint if it is not spendable - also display a reason why
        bool fSpendable = isMature && nConfirmations >= Params().Zerocoin_MintRequiredConfirmations();
        if(!fSpendable) {
            itemMint->setDisabled(true);
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Unchecked);

            //if this mint is in the selection list, then remove it
            if (setSelectedMints.count(strPubCoinHash))
                setSelectedMints.erase(strPubCoinHash);

            string strReason = "";
            if(nConfirmations < Params().Zerocoin_MintRequiredConfirmations())
                strReason = strprintf("Needs %d more confirmations", Params().Zerocoin_MintRequiredConfirmations() - nConfirmations);
            else
                strReason = strprintf("Needs %d more mints added to network", Params().Zerocoin_RequiredAccumulation());

            itemMint->setText(COLUMN_ISSPENDABLE, QString::fromStdString(strReason));
        } else {
            itemMint->setText(COLUMN_ISSPENDABLE, QString("Yes"));
        }
    }

    ui->treeWidget->blockSignals(false);
    updateLabels();
}

// Update the list when a checkbox is clicked
void ZSvgControlDialog::updateSelection(QTreeWidgetItem* item, int column)
{
    // only want updates from non top level items that are available to spend
    if (item->parent() && column == COLUMN_CHECKBOX && !item->isDisabled()){

        // see if this mint is already selected in the selection list
        std::string strPubcoin = item->text(COLUMN_PUBCOIN).toStdString();
        bool fSelected = setSelectedMints.count(strPubcoin);

        // set the checkbox to the proper state and add or remove the mint from the selection list
        if (item->checkState(COLUMN_CHECKBOX) == Qt::Checked) {
            if (fSelected) return;
            setSelectedMints.insert(strPubcoin);
        } else {
            if (!fSelected) return;
            setSelectedMints.erase(strPubcoin);
        }
        updateLabels();
    }
}

// Update the Quantity and Amount display
void ZSvgControlDialog::updateLabels()
{
    int64_t nAmount = 0;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            nAmount += mint.denom;
    }

    //update this dialog's labels
    ui->labelZSvg_int->setText(QString::number(nAmount));
    ui->labelQuantity_int->setText(QString::number(setSelectedMints.size()));

    //update PrivacyDialog labels
    privacyDialog->setZSvgControlLabels(nAmount, setSelectedMints.size());
}

std::vector<CMintMeta> ZSvgControlDialog::GetSelectedMints()
{
    std::vector<CMintMeta> listReturn;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            listReturn.emplace_back(mint);
    }

    return listReturn;
}

// select or deselect all of the mints
void ZSvgControlDialog::ButtonAllClicked()
{
    ui->treeWidget->blockSignals(true);
    Qt::CheckState state = Qt::Checked;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
        if(ui->treeWidget->topLevelItem(i)->checkState(COLUMN_CHECKBOX) != Qt::Unchecked) {
            state = Qt::Unchecked;
            break;
        }
    }

    //much quicker to start from scratch than to have QT go through all the objects and update
    ui->treeWidget->clear();

    if (state == Qt::Checked) {
        for(const CMintMeta& mint : setMints)
            setSelectedMints.insert(mint.hashPubcoin.GetHex());
    } else {
        setSelectedMints.clear();
    }

    updateList();
}
