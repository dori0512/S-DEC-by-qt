#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "sdes.h"

class EncryptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EncryptWidget(QWidget *parent = nullptr);

private slots:
    void encrypt();

private:
    QPlainTextEdit *m_plainTextEdit;
    QLineEdit *m_keyEdit;
    QLabel *m_cipherLabel;
    SDES m_sdes;
};

#endif // ENCRYPTWIDGET_H
