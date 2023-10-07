#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "encryptionwidget.h"
#include "decryptionwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setCentralWidget(QWidget *widget);

private:
    EncryptWidget *m_encryptionWidget;
    DecryptWidget *m_decryptionWidget;

};

#endif // WIDGET_H
