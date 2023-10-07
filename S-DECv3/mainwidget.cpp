#include "mainwidget.h"
#include "encryptionwidget.h"
#include "decryptionwidget.h"
#include "crackwidget.h"
#include "sdes.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    // 创建 QStackedWidget
    m_stackedWidget = new QStackedWidget(this);

    // 创建 EncryptWidget 和 DecryptWidget、CrackWidget
    EncryptWidget *encryptWidget = new EncryptWidget(this);
    DecryptWidget *decryptWidget = new DecryptWidget(this);
    CrackWidget *crackWidget = new CrackWidget(this);

    // 将 EncryptWidget 和 DecryptWidget 添加到 QStackedWidget 中
    m_stackedWidget->addWidget(encryptWidget);
    m_stackedWidget->addWidget(decryptWidget);
    m_stackedWidget->addWidget(crackWidget);

    // 创建按钮
    QPushButton *encryptButton = new QPushButton(" ", this);
    QPushButton *decryptButton = new QPushButton(" ", this);
    QPushButton *crackButton = new QPushButton("暴力破解", this);
    encryptButton->setIcon(QIcon(":/image/icons/lock.jpg"));
    encryptButton->setIconSize(QSize(36, 36));
    decryptButton->setIcon(QIcon(":/image/icons/unlock.jpg"));
    decryptButton->setIconSize(QSize(36, 36));
    encryptButton->setFixedHeight(70);
    decryptButton->setFixedHeight(70);
    crackButton->setFixedHeight(60);
    // 创建垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_stackedWidget);
    layout->addWidget(encryptButton);
    layout->addWidget(decryptButton);
    layout->addWidget(crackButton);

    // 设置布局
    setLayout(layout);

    // 连接按钮的 clicked 信号到 QStackedWidget 的 setCurrentIndex 槽
    connect(encryptButton, &QPushButton::clicked, m_stackedWidget, [this]() {
        m_stackedWidget->setCurrentIndex(0);
    });
    connect(decryptButton, &QPushButton::clicked, m_stackedWidget, [this]() {
        m_stackedWidget->setCurrentIndex(1);
    });
    connect(crackButton, &QPushButton::clicked, m_stackedWidget, [this]() {
        m_stackedWidget->setCurrentIndex(2);
    });
}
