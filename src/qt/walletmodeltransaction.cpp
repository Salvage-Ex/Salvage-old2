// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Salvage developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletmodeltransaction.h"

#include "wallet.h"

WalletModelTransaction::WalletModelTransaction(const QList<SendCoinsRecipient>& recipients) : recipients(recipients),
                                                                                              walletTransaction(0),
                                                                                              keyChange(0),
                                                                                              fee(0)
{
    walletTransaction = new CWalletTx();
}

WalletModelTransaction::~WalletModelTransaction()
{
    delete keyChange;
    delete walletTransaction;
}

QList<SendCoinsRecipient> WalletModelTransaction::getRecipients()
{
    return recipients;
}

CWalletTx* WalletModelTransaction::getTransaction()
{
    return walletTransaction;
}

unsigned int WalletModelTransaction::getTransactionSize()
{
    return (!walletTransaction ? 0 : (::GetSerializeSize(*(CTransaction*)walletTransaction, SER_NETWORK, PROTOCOL_VERSION)));
}

CAmount WalletModelTransaction::getTransactionFee()
{
    return fee;
}

void WalletModelTransaction::setTransactionFee(const CAmount& newFee)
{
    fee = newFee;
}

CAmount WalletModelTransaction::getTotalTransactionAmount()
{
    CAmount totalTransactionAmount = 0;
    foreach (const SendCoinsRecipient& rcp, recipients) {
        totalTransactionAmount += rcp.amount;
    }
    return totalTransactionAmount;
}

void WalletModelTransaction::newPossibleKeyChange(CWallet* wallet)
{
    keyChange = new CReserveKey(wallet);
}

CReserveKey* WalletModelTransaction::getPossibleKeyChange()
{
    return keyChange;
}
