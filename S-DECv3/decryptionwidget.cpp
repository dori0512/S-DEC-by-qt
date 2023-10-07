#include "decryptionwidget.h"
#include "sdes.h"
#include <QFormLayout>
#include <QMessageBox>
#include <QIcon>

DecryptWidget::DecryptWidget(QWidget *parent) : QWidget(parent)
{
    m_cipherTextEdit = new QPlainTextEdit(this);
    m_cipherTextEdit->setPlaceholderText("密文");
    m_cipherTextEdit->setFixedHeight(100);
    m_cipherTextEdit->setStyleSheet("QPlainTextEdit { font: 25 10pt '微软雅黑 Light';" // 字体
                                     "color: rgb(31, 31, 31);" // 字体颜色
                                     "padding-left: 20px;" // 内边距-字体缩进
                                     "background-color: rgb(255, 255, 255);" // 背景颜色
                                     "border: 2px solid rgb(244, 67, 54);" // 边框样式和颜色
                                     "border-radius: 15px; }"); // 圆角半径

    m_keyEdit = new QLineEdit(this);
    m_keyEdit->setPlaceholderText("密钥");
    m_keyEdit->setStyleSheet("QLineEdit { font: 25 10pt '微软雅黑';" // 字体
                              "color: rgb(31, 31, 31);" // 字体颜色
                              "padding-left: 20px;" // 内边距-字体缩进
                              "background-color: rgb(255, 255, 255);" // 背景颜色
                              "border: 2px solid rgb(244, 67, 54);" // 边框样式和颜色
                              "border-radius: 15px;" // 圆角半径
                              "height: 40px; }"); // 控件高度

    QPushButton *decryptButton = new QPushButton(this);
    decryptButton->setText("点击进行解密");
    decryptButton->setStyleSheet("QPushButton { font: 25 12pt '楷体';" // 字体
                                 "font-weight: bold;" // 字体加粗
                                 "color: rgb(255, 255, 255);" // 字体颜色
                                 "background-color: rgb(244, 67, 54);" // 背景颜色
                                 "border: none;" // 边框样式
                                 "border-radius: 15px;" // 圆角半径
                                 "height: 70px; }" // 控件高度
                                 "QPushButton:hover { background-color: rgb(229, 57, 53); }" // 鼠标悬停时的背景颜色
                                 "QPushButton:pressed { background-color: rgb(198, 40, 34); }"); // 鼠标按下时的背景颜色

    m_decryptedLabel = new QLabel(this);
    m_decryptedLabel->setText("......");
    m_decryptedLabel->setFixedHeight(70);
    m_decryptedLabel->setStyleSheet("QLabel { font: 25 11pt '微软雅黑 Light';" // 字体
                                     "color: rgb(31, 31, 31);" // 字体颜色
                                     "padding-left: 20px;" // 内边距-字体缩进
                                     "background-color: rgb(255, 255, 255);" // 背景颜色
                                     "border: 2px solid rgb(244, 67, 54);" // 边框样式和颜色
                                     "border-radius: 15px; }"); // 圆角半径

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("密文:", m_cipherTextEdit);
    layout->addRow("密钥:", m_keyEdit);
    layout->addWidget(decryptButton);
    layout->addRow("解密结果:", m_decryptedLabel);
    setLayout(layout);
    this->setStyleSheet("font: 20 12pt '微软雅黑';font-weight: bold;}");
    setFixedSize(800, 400); // 设置固定大小

    connect(decryptButton, &QPushButton::clicked, this, &DecryptWidget::decrypt);
}

void DecryptWidget::decrypt()
{
    QString cipherText = m_cipherTextEdit->toPlainText();
    QString key = m_keyEdit->text();

    if (cipherText.isEmpty() || key.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "解密失败：请输入密文和密钥");
        return;
    }
    if (key.length() != 10) { // 检查是否为10bit的密钥
        QMessageBox::information(this, "提示", "解密失败：请输入10bit的密钥");
        return;
    }

    // 检查输入是否为ASCII编码字符串或二进制字符串
    bool isAscii = true;
    bool isBinary = true;
    for (int i = 0; i < cipherText.length(); i++) {
        if (cipherText[i].unicode() > 255) {
            isAscii = false;
        }
        if (cipherText[i] != '0' && cipherText[i] != '1') {
            isBinary = false;
        }
    }
    for (int i = 0; i < key.length(); i++) {
        if (key[i] != '0' && key[i] != '1' && key.length() != 10) {
            QMessageBox::information(this, "提示", "加密失败：请输入10bit的二进制密钥");
            return;
        }
    }
    if (!isAscii && !isBinary) {
        QMessageBox::information(this, "提示", "解密失败：密文需要是二进制或能转化为ASCII的字符串");
        return;
    }

    QString decryptedText;
    if (isBinary && cipherText.length() == 8) {
        QString decryptedBinaryText = m_sdes.decrypt(cipherText, key);
        decryptedText = decryptedBinaryText;
    }
    else if(isBinary && cipherText.length() != 8){
        QMessageBox::information(this, "提示", "解密失败：密文需要是8bit二进制数或能转化为ASCII的字符串");
        return;
    }
    else {
        for (int i = 0; i < cipherText.length(); i++) {
            // 将ASCII编码字符串转换为二进制字符串进行解密
            QString binaryChar = QString("%1").arg(cipherText[i].unicode(), 8, 2, QChar('0'));
            QString decryptedBinaryText = m_sdes.decrypt(binaryChar, key);

            // 将解密后的二进制字符串转换为ASCII编码字符串输出
            QChar asciiChar(decryptedBinaryText.toInt(nullptr, 2));
            decryptedText += asciiChar;
        }
    }

    m_decryptedLabel->setText(decryptedText);
    m_decryptedLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}
