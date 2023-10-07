#ifndef CRACKWIDGET_H
#define CRACKWIDGET_H

#include <QWidget>
#include "sdes.h"
#include <QPlainTextEdit>
#include <QLineEdit>
#include "crackworker.h"

class CrackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CrackWidget(QWidget *parent = nullptr);

private slots:
    void crack();

private:
    QPlainTextEdit *m_plainTextEdit;
    QPlainTextEdit *m_cipherTextEdit;
    QLineEdit *m_keyEdit;
    QLineEdit *m_timeLabel;
    SDES m_sdes;
};

#endif // CRACKWIDGET_H
