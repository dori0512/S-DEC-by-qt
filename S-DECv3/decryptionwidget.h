#ifndef DECRYPTWIDGET_H
#define DECRYPTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include "sdes.h"

class DecryptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DecryptWidget(QWidget *parent = nullptr);

private slots:
    void decrypt();

private:
    QPlainTextEdit *m_cipherTextEdit;
    QLineEdit *m_keyEdit;
    QLabel *m_decryptedLabel;
    SDES m_sdes;
};

#endif // DECRYPTWIDGET_H
