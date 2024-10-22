// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Salvage developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_QVALIDATEDLINEEDIT_H
#define BITCOIN_QT_QVALIDATEDLINEEDIT_H

#include <QLineEdit>

/** Line edit that can be marked as "invalid" to show input validation feedback. When marked as invalid,
   it will get a red background until it is focused.
 */
class QValidatedLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit QValidatedLineEdit(QWidget* parent);
    void clear();
    void setCheckValidator(const QValidator* v);

protected:
    void focusInEvent(QFocusEvent* evt);
    void focusOutEvent(QFocusEvent* evt);

private:
    bool valid;
    const QValidator* checkValidator;

public slots:
    void setValid(bool valid);
    void setEnabled(bool enabled);

private slots:
    void markValid();
    void checkValidity();
};

#endif // BITCOIN_QT_QVALIDATEDLINEEDIT_H
