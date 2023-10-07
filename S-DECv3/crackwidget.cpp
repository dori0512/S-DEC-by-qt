#include "crackwidget.h"

#include <QMessageBox>
#include <QIcon>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTime>
#include <QFormLayout>
#include <QThread>
#include <QDebug>

CrackWidget::CrackWidget(QWidget *parent) : QWidget(parent)
{
    m_plainTextEdit = new QPlainTextEdit(this);
    m_plainTextEdit->setPlaceholderText("明文");
    m_plainTextEdit->setFixedHeight(100);
    m_plainTextEdit->setStyleSheet("font: 25 10pt '微软雅黑 Light';" //字体
                                   "color: rgb(31,31,31);"		//字体颜色
                                   "padding-left:20px;"       //内边距-字体缩进
                                   "background-color: rgb(255, 255, 255);" //背景颜色
                                   "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    m_cipherTextEdit = new QPlainTextEdit(this);
    m_cipherTextEdit->setPlaceholderText("密文");
    m_cipherTextEdit->setFixedHeight(100);
    m_cipherTextEdit->setStyleSheet("font: 25 10pt '微软雅黑 Light';" //字体
                                   "color: rgb(31,31,31);"		//字体颜色
                                   "padding-left:20px;"       //内边距-字体缩进
                                   "background-color: rgb(255, 255, 255);" //背景颜色
                                   "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    m_keyEdit = new QLineEdit(this);
    m_keyEdit->setPlaceholderText("破解后的密钥");
    m_keyEdit->setStyleSheet("font: 25 10pt '微软雅黑';" //字体
                             "color: rgb(31,31,31);"		//字体颜色
                             "padding-left:20px;"       //内边距-字体缩进
                             "background-color: rgb(255, 255, 255);" //背景颜色
                             "border:2px solid rgb(20,196,188);border-radius:15px;height: 40px;");//边框粗细-颜色-圆角设置
    m_timeLabel = new QLineEdit(this);
    m_timeLabel->setPlaceholderText("00：00");
    m_timeLabel->setStyleSheet("font: 25 7pt '微软雅黑';" //字体
                             "color: rgb(31,31,31);"		//字体颜色
                             "padding-left:20px;"       //内边距-字体缩进
                             "background-color: rgb(255, 255, 255);" //背景颜色
                             "border:2px solid rgb(20,196,188);border-radius:15px;height: 40px;");//边框粗细-颜色-圆角设置
    QPushButton *crackButton = new QPushButton(this);

    crackButton->setText("点击进行破解");
    crackButton->setStyleSheet("QPushButton{font: 25 12pt '楷体';font-weight: bold; color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                 "border: none;border-radius:15px;height: 70px;}"
                                 "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                 "QPushButton:pressed{background-color: rgb(17,171,164);}");

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("明文 :", m_plainTextEdit);
    layout->addRow("密文 :", m_cipherTextEdit);
    layout->addRow("破解后的密钥 :", m_keyEdit);
    layout->addRow("破解时间 :", m_timeLabel);
    layout->addWidget(crackButton);
    this->setStyleSheet("font: 20 12pt '微软雅黑';font-weight: bold;}");
    setLayout(layout);

    setFixedSize(800, 400); // 设置固定大小

    connect(crackButton, &QPushButton::clicked, this, &CrackWidget::crack);
}

//void CrackWidget::crack()
//{
//    QStringList plainTextList = m_plainTextEdit->toPlainText().split("\n");
//    QStringList cipherTextList = m_cipherTextEdit->toPlainText().split("\n");

//    if (plainTextList.isEmpty() || cipherTextList.isEmpty()) { // 检查输入是否为空
//        QMessageBox::information(this, "提示", "破解失败：请输入明文和密文");
//        return;
//    }

//    if (plainTextList.size() != cipherTextList.size()) { // 检查明文和密文数量是否一致
//        QMessageBox::information(this, "提示", "破解失败：明文和密文数量不一致");
//        return;
//    }

//    QTime startTime = QTime::currentTime(); // 记录开始时间

//    QString key;
//    bool found = false;

//    // 创建多个线程
//    QList<QThread*> threads;
//    QList<CrackWorker*> workers;
//    for (int i = 0; i < QThread::idealThreadCount(); i++) {
//        CrackWorker *worker = new CrackWorker(&m_sdes, plainTextList, cipherTextList);
//        QThread *thread = new QThread(this);
//        worker->moveToThread(thread);
//        connect(thread, &QThread::started, worker, &CrackWorker::process);
//        threads.append(thread);
//        workers.append(worker);
//    }

//    // 启动所有线程
//    for (int i = 0; i < threads.size(); i++) {
//        threads[i]->start();
//    }

//    // 等待所有线程完成
//    for (int i = 0; i < threads.size(); i++) {
//        threads[i]->wait();
//    }

//    // 查找是否有正确的密钥
//    for (int i = 0; i < workers.size(); i++) {
//        if (workers[i]->isKeyFound()) {
//            key = workers[i]->getKey();
//            found = true;
//            break;
//        }
//    }

//    if (found) {
//        m_keyEdit->setText(key);
//    } else {
//        QMessageBox::information(this, "提示", "破解失败：未找到正确的密钥");
//    }

//    QTime endTime = QTime::currentTime(); // 记录结束时间
//    int elapsedTime = startTime.msecsTo(endTime); // 计算破解时长
//    QMessageBox::information(this, "提示", QString("破解完成，用时 %1 毫秒").arg(elapsedTime));
//}
void CrackWidget::crack()
{
    QStringList plainTextList = m_plainTextEdit->toPlainText().split("\n");
    QStringList cipherTextList = m_cipherTextEdit->toPlainText().split("\n");
    QString knownPlaintext = m_plainTextEdit->toPlainText();
    QString knownCiphertext = m_cipherTextEdit->toPlainText();

    if (knownPlaintext.isEmpty() || knownCiphertext.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "破解失败：请输入明文和密文");
        return;
    }

    if (knownPlaintext.size() != knownCiphertext.size()) { // 检查明文和密文数量是否一致
        QMessageBox::information(this, "提示", "破解失败：明文和密文数量不一致");
        return;
    }

    bool isAscii_p = true;
    bool isBinary_p = true;
    for (int i = 0; i < knownPlaintext.length(); i++) {
        if (knownPlaintext[i].unicode() > 255) {
            isAscii_p = false;
        }
        if (knownPlaintext[i] != '0' && knownPlaintext[i] != '1') {
            isBinary_p = false;
        }
    }
    bool isAscii_c = true;
    bool isBinary_c = true;
    for (int i = 0; i < knownCiphertext.length(); i++) {
        if (knownCiphertext[i].unicode() > 255) {
            isAscii_c = false;
        }
        if (knownCiphertext[i] != '0' && knownCiphertext[i] != '1') {
            isBinary_c = false;
        }
    }

    if (!isAscii_c && !isBinary_c && !isAscii_p && !isBinary_p) {
        QMessageBox::information(this, "提示", "破解失败：明密文需要是二进制或能转化为ASCII的字符串");
        return;
    }

    if (isBinary_c && isBinary_p && knownCiphertext.length() == 8 && knownPlaintext.length() == 8) {

    }
    else if(isBinary_c && isBinary_p && knownCiphertext.length() != 8 && knownPlaintext.length() != 8){
        QMessageBox::information(this, "提示", "加密失败：明文需要是8bit二进制数或能转化为ASCII的字符串");
        return;
    }
    else {

        for (int i = 0; i < knownPlaintext.length(); i++) {
            // 将ASCII编码字符串转换为二进制字符串进行加密
            QString binaryChar_p = QString("%1").arg(knownPlaintext[i].unicode(), 8, 2, QChar('0'));
            knownPlaintext =binaryChar_p;
            QString binaryChar_c = QString("%1").arg(knownCiphertext[i].unicode(), 8, 2, QChar('0'));
            knownCiphertext =binaryChar_c;
        }
    }

    QElapsedTimer timer;
    timer.start();

    int key;
    int count = 0;
    QString binaryKey;
    QString allkey = "Foun key: \n";

            for (key = 0; key <= 1023; ++key) {
                binaryKey = QString::number(key, 2).rightJustified(10, '0');
                QString encryptedText = m_sdes.encrypt(knownPlaintext, binaryKey);

                if (encryptedText == knownCiphertext) {
                    qDebug() << "Found key: " << binaryKey;
                    allkey = allkey + binaryKey + "\n";
                    count++;
                    //break;
                }
            }

    if (count) {
            m_keyEdit->setText(allkey);
    } else {
            qDebug() << "Key not found.";
            QMessageBox::information(this, "提示", "破解失败：未找到正确的密钥");
                    }

    // 获取结束时间戳
    qint64 elapsedTimeUs = timer.nsecsElapsed() / 1000;
    double elapsedTimeSec = static_cast<double>(elapsedTimeUs) / 1000000.0;

    // 计算破解时长并显示
    m_timeLabel->setText(QString("破解时长：%1 秒").arg(QString::number(elapsedTimeSec, 'f', 6)));
}
