# S-DEC-by-qt
## 实验原理和标准设定：
1 分组长度：8-bit
2 密钥长度：10-bit
3 算法描述：
3.1 加密算法：  
C=IP^{-1}(f_{k_{2}}(SW(f_{k_{1}}(IP(P)))))  
3.2 解密算法：  
P=IP^{-1}(f_{k_{1}}(SW(f_{k_{2}}(IP(C)))))  
3.3 密钥扩展：  
k_{i}=P_{8}(Shift^{i}(P_{10}(K))), (i=1,2)  
4 转换装置设定：  
4.1 密钥扩展置  
P_{10}=(3,5,2,7,4,10,1,9,8,6)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/7bfc2bc3-f101-4bc3-bd06-2e947bf90944)  
P_{8}=(6,3,7,4,8,5,10,9)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/ed5c2cae-f642-4b4c-bea6-116213cfd593)  
Left_Shift^1=(2,3,4,5,1)  
Left_Shift^2=(3,4,5,1,2)  
4.2 初始置换盒  
IP=(2,6,3,1,4,8,5,7)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/914b8f2b-ece8-4c6b-9bfa-e21c0c20389a)  
最终置换盒  
IP^{-1}=(4,1,3,5,7,2,8,6)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/492fc769-e1d6-4e1f-a175-8caff69473ec)  
轮函数F  
EPBox=(4,1,2,3,2,3,4,1)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/b2a9ffae-2619-411b-882a-6e642a8f5e96)  

SBox_{1}=[(1,0,3,2);(3,2,1,0);(0,2,1,3);(3,1,0,2)]  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/dea7d561-a363-48b2-b706-17846ba9dbf9)

SBox_{2}=[(0,1,2,3);(2,3,1,0);(3,0,1,2);(2,1,0,3)]  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/31d731f5-d1a9-48d3-9d12-3e894ca9731c)

SPBox=(2,4,3,1)  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/b4543011-8acf-4a82-b755-a04fe2ead27c)

## 第1关：基本测试  
根据S-DES算法编写和调试程序，提供GUI解密支持用户交互。输入可以是8bit的数据和10bit的密钥，输出是8bit的密文。
### 1.1GUI界面设计
#### 1.1.1加密界面  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/1983256d-edf2-40f3-8a88-8ec041504f94)
#### 1.1.2解密界面  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/0566655e-a342-4cb6-bdf7-fd7ed0363610)
#### 1.1.3暴力破解界面  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/74abf707-43e1-4232-b451-fc2684325434)
#### 1.1.4界面间跳转  
三个界面可以通过点击界面下方的三个按钮进行跳转，点击“锁”可以跳转到加密界面，点击“开锁”按钮可以跳转到解密界面，点击“暴力破解”即可转为“暴力破解”界面。

### 1.2基本运行与功能实现
#### 1.2.1不规范输入  
加密、解密、暴力破解都需要输入对应的明文/密文/密钥才能运行，若提交为空，则会弹出相应错误提示。  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/2d73571c-f252-445a-b6ee-532f05536af2)
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/9ae3ad35-44fa-4c28-bec8-758fa90d4928)
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/d7bd7937-a834-471b-bd65-74cb2d0d1b5b)

密钥限定为10bits，不满足条件，则会弹出警告  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/f64c9884-dabf-4a01-bfda-675262ad3637)
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/8826184f-8e3a-4938-8de4-2743207b6393)

明密文必须是8bits的二进制数或者能转化为ASCII的字符串，否则会弹出警告  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/b39790d1-5c9e-45fb-813c-4c7fc47a710c)
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/c885dc68-086f-455f-a4c6-2fc7ef8b83cf)

#### 1.2.2加解密功能运行
【加密】测试用例1：  
明文：10101010 密钥：1111000010  加密后的密文：00101111  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/d000102c-20ed-489e-8224-676dce9ed75c)

【加密】测试用例2：  
明文：+ 密钥：1111111111  加密后的密文：2  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/c8f814bf-4b87-46d0-99ec-95571e9ba8d7)

【加密】测试用例3：  
明文：god 密钥：1010101011  加密后的密文：îdÆ  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/7cca3e63-8161-4cbd-aca9-99b0627bdd87)

【解密】测试用例1：  
密文：00101111 密钥：1111000010  解密后的明文：10101010  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/c3a22cb6-9306-4867-8ddd-12f79066f2ae)

【解密】测试用例2：  
密文：2 密钥：1111111111  解密后的明文：+  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/a67552dd-310e-4f65-9bbf-3c153d699d49)

【解密】测试用例3：  
密文：îdÆ 密钥：1010101011  解密后的明文：god  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/d2d428bc-02d1-4280-a116-e624eaec9a37)

**通过加解密的三个测试用例，我们清楚可以得出，明密文无论是8bits二进制数据，还是单个ascii码、或者ASCII码串，其加解密结果均匹配且互逆，实现对称加密的基本原理，实现了S-DES算法的基本功能。**

## 第2关：交叉测试
我们组与其他组的8bits二进制与ASCII码对应的加解密用例对比：  
二进制加密：（明文：10101010 密钥：1111100000）  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/efd2c0a0-1a2f-4d8a-83f4-d4edbabb99b5)

![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/beacd196-26db-42e7-af64-1a4f0a3f2699)

别组：  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/690317c1-26d0-40fb-b445-71537e4a23e1)

ASCII加密：（密文：svc 密钥：1111111111）  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/5b4d77ac-6b18-4b5e-8400-fd1c89c31043)

![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/d79e7499-3ba7-4a71-b4f9-c496283f1a79)

别组：  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/9c4d705b-50cf-4bc2-bb20-82a908f851b3)

**由上图可得，运用相同的密钥扩展置、IP初始置换盒、最终置换盒、轮函数F，加密而来的结果相同。使用相同算法流程和转换单元(P-Box、S-Box等)，以保证算法和程序在异构的系统或平台上都可以正常运行，即通过了交叉测试。**


## 第3关：扩展功能  
由第一关的测试用例2与测试用例3以及下图用例均可证实该系统已向实用性扩展，加密算法的数据输入扩展为可以是ASCII编码字符串(分组为1 Byte)，对应地输出也可以是ASCII字符串  


其中运用的中心思想是将明文密文中的ASCII编码字符串划分为单个的ASCII编码字符，再将其转化为对应的8bits的二进制，再作为输入进行加解密，经过加解密之后，再将得到的8bits二进制转化为对应的ASCII字符串，即完成了对应的ASCII加解密的扩展。  
下面展示了关于扩展的部分核心代码：  
`<
void EncryptWidget::encrypt()
{
    QString plainText = m_plainTextEdit->toPlainText();
    QString key = m_keyEdit->text();

    if (plainText.isEmpty() || key.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "加密失败：请输入密文和密钥");
        return;
    }
    if (key.length() != 10) { // 检查是否为10bit的密钥
        QMessageBox::information(this, "提示", "加密失败：请输入10bit的密钥");
        return;
    }
    // 检查输入是否为ASCII编码字符串或二进制字符串
    bool isAscii = true;
    bool isBinary = true;
    for (int i = 0; i < plainText.length(); i++) {
        if (plainText[i].unicode() > 255) {
            isAscii = false;
        }
        if (plainText[i] != '0' && plainText[i] != '1') {
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
        QMessageBox::information(this, "提示", "加密失败：明文需要是二进制或能转化为ASCII的字符串");
        return;
    }

    QString encryptedText;
    if (isBinary && plainText.length() == 8) {
        QString encryptedBinaryText = m_sdes.encrypt(plainText, key);
        encryptedText = encryptedBinaryText;
    }
    else if(isBinary && plainText.length() != 8){
        QMessageBox::information(this, "提示", "加密失败：明文需要是8bit二进制数或能转化为ASCII的字符串");
        return;
    }
    else {

        for (int i = 0; i < plainText.length(); i++) {
            // 将ASCII编码字符串转换为二进制字符串进行加密
            QString binaryChar = QString("%1").arg(plainText[i].unicode(), 8, 2, QChar('0'));
            QString encryptedBinaryText = m_sdes.encrypt(binaryChar, key);

            // 将加密后的二进制字符串转换为ASCII编码字符串输出
            QChar asciiChar(encryptedBinaryText.toInt(nullptr, 2));
            encryptedText += asciiChar;
        }
    }

    m_cipherLabel->setText(encryptedText);
}
>`


## 第4关：暴力破解
### 4.1单线程破解
#### 4.1.1单线程破解思路  
首先，需要了解S-DES算法的工作原理和步骤。S-DES算法涉及到初始置换、加密轮函数、密钥生成和最终置换等步骤，因此破解对应的S-DES算法需要使用相同算法流程和转换单元(P-Box、S-Box等)，其次确定密钥空间：S-DES算法使用10位密钥，因此密钥空间为2^10 = 1024个可能的密钥。  
然后，将密钥从0至1023依次转换为8bits二进制带入进行破解，判断已知明文经由该密钥加密后的密文是否等同于已知的明密文对中的密文，如果等同，则求得了该明密文对中的密钥。  
#### 4.1.2单线程破解的实现  
已知明密文对：（明文：10101010，密文：00101111）  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/4e53a48e-106c-498b-af05-0365c5b9a0df)

可以找到该明密文对的四个密钥：1000011011 1011000010 1100011011 1111000010  
**相对应的破解时间为0.015572秒**  
通过下图的加密与解密均可证明根据明密文对找到的密钥正确：    
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/919be8e3-d071-4a06-9741-9eed97575b55)

#### 4.1.3单线程破解部分核心代码  
`<void CrackWidget::crack()
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
>`
### 4.2多线程破解  
#### 4.2.1多线程破解思路  
我们创建多个CrackWorker对象并将它们移动到单独的线程中。每个CrackWorker对象负责搜索可能的密钥的一个子集。当一个CrackWorker对象找到正确的密钥时，它会发出一个keyFound信号，该信号连接到CrackWidget的onKeyFound()槽。onKeyFound()槽停止所有线程并在m_keyEdit小部件中设置密钥。  
#### 4.2.2多线程破解的实现  
由于多线程破解的主要思想也是多个线程进行遍历，但暴力破解应尽可能找到所有能破解该明密文对的密钥，因此其所消耗的时间与单线程破解相差不大，且所涉及的运行环境更为严苛，其时间复杂度与单线程破解相近，在这里未做前端的展现。相关代码可参考如下。  
#### 4.2.3多线程破解部分核心代码
`<void CrackWidget::crack()
{
    QStringList plainTextList = m_plainTextEdit->toPlainText().split("\n");
    QStringList cipherTextList = m_cipherTextEdit->toPlainText().split("\n");

    if (plainTextList.isEmpty() || cipherTextList.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "破解失败：请输入明文和密文");
        return;
    }

    if (plainTextList.size() != cipherTextList.size()) { // 检查明文和密文数量是否一致
        QMessageBox::information(this, "提示", "破解失败：明文和密文数量不一致");
        return;
    }

    QTime startTime = QTime::currentTime(); // 记录开始时间

    QString key;
    bool found = false;

    // 创建多个线程
    QList<QThread*> threads;
    QList<CrackWorker*> workers;
    for (int i = 0; i < QThread::idealThreadCount(); i++) {
        CrackWorker *worker = new CrackWorker(&m_sdes, plainTextList, cipherTextList);
        QThread *thread = new QThread(this);
        worker->moveToThread(thread);
        connect(thread, &QThread::started, worker, &CrackWorker::process);
        threads.append(thread);
        workers.append(worker);
    }

    // 启动所有线程
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->start();
    }

    // 等待所有线程完成
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->wait();
    }

    // 查找是否有正确的密钥
    for (int i = 0; i < workers.size(); i++) {
        if (workers[i]->isKeyFound()) {
            key = workers[i]->getKey();
            found = true;
            break;
        }
    }

    if (found) {
        m_keyEdit->setText(key);
    } else {
        QMessageBox::information(this, "提示", "破解失败：未找到正确的密钥");
    }

    QTime endTime = QTime::currentTime(); // 记录结束时间
    int elapsedTime = startTime.msecsTo(endTime); // 计算破解时长
    QMessageBox::information(this, "提示", QString("破解完成，用时 %1 毫秒").arg(elapsedTime));
}>`
## 第5关：封闭测试
对于一个随机选择的明密文对，如果加密算法是单向的（即不可逆的），那么很可能存在多个密钥可以加密出相同的密文。这是因为单向加密算法通常是将明文映射到一个较小的密文空间中，而密钥则是用于控制这个映射的参数。因此，不同的密钥可能会将相同的明文映射到相同的密文上。  
对于一个给定的明文分组 P_n，如果加密算法是可逆的，那么不同的密钥 K_i 和 K_j 可能会加密出相同的密文 C_n。这是因为可逆加密算法是一种双向映射，它可以将明文空间和密文空间一一对应。因此，如果两个不同的密钥 K_i 和 K_j 都能将明文分组 P_n 加密为相同的密文 C_n，那么这两个密钥就是等效的，它们可以互相替换使用。  
需要注意的是，如果加密算法是强加密算法，那么即使给定相同的明文分组，不同的密钥也不太可能加密出相同的密文。这是因为强加密算法通常使用的是随机数或者伪随机数生成器来生成密钥和初始化向量，这样可以保证每次加密的结果都是不同。  
具体验证实例：  
已知明密文对（明文：+，密文：2）  
![image](https://github.com/dori0512/S-DEC-by-qt/assets/130364519/656639a1-065f-437d-9be0-c3004e085264)

Foun key: 0001000000 0010011000 0101000000 0110011000 1011111111 1111111111  
验证：  
![Uploading image.png…]()
![Uploading image.png…]()

## 相关用户手册、接口文档详见附件

## 核心代码附件：
### sdes.cpp
`<//检测字符若为二进制，则将其转化为int类整数型
int SDES::binToDec(const QString &binStr)
{
    return binStr.toInt(nullptr, 2);
}

//密钥扩展置(得到本轮密钥)
QString SDES::keyExpansion(const QString &key, int round)
{
    //p10置换盒
    QString p10key;
    for (int i : P10) {
        if (i - 1 < key.length()) {
            p10key += key.at(i - 1);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问p10";
        }
    }

    //leftshift左移
    QString ls1key = p10key.mid(0, 5);//从p10key中第0位开始截取，截取5个字符串
    QString ls2key = p10key.mid(5, 5);//从p10key中第5位开始截取，截取5个字符串
    ls1key = ls1key.mid(round) + ls1key.left(round);//从ls1key中第(round)位开始截取到末尾的字符串+ls1key中最左边的（round）个字符....此处改动
    ls2key = ls2key.mid(round) + ls2key.left(round);//从ls2key中第(round)位开始截取到末尾的字符串+ls2key中最左边的（round）个字符

    QString mergedKey = ls1key + ls2key;

    //p8置换盒
    QString subkey;
    for (int i : P8) {
        if (i - 1 < mergedKey.length()) {
            subkey += mergedKey.at(i - 1);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问p8";
        }
    }

    return subkey;//得到本轮密钥
}

//F轮函数(只需要对右半部分进行操作，因此参数为&right)
QString SDES::F(const QString &right, const QString &subkey)
{
    //通过EPBox进行E扩展
    QString expandedRight;
    for (int i : EP) {
        if (i - 1 < right.length()) {
            expandedRight += right.at(i - 1);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问ep";
        }
    }

    //与密钥进行异或
    QString xorResult;
    for (int i = 0; i < expandedRight.length(); ++i) {
        if (i < subkey.length() && expandedRight.at(i) == subkey.at(i)) {
            xorResult += '0';
        } else {
            xorResult += '1';
        }
    }

    //SBox置换运算
    QString sboxOutput;
    QString leftXor, rightXor;
    //将XorResult分为两部分
    if (xorResult.length() >= 8) {
        leftXor = xorResult.mid(0, 4);
        rightXor = xorResult.mid(4, 4);

        //对leftXor(左半部分)进行SBox1置换
        int row, col;
        row = binToDec(leftXor.mid(0, 1) + leftXor.mid(3, 1));//取第一位和最后一位组成二进制换算成十进制
        col = binToDec(leftXor.mid(1, 2));//取数组号1~2组成二进制换算成十进制....此处改动
        if (row < 4 && col < 4) {
            sboxOutput += decToBin(SBox1[row][col], 2);//用SBox对应行列位置的数值进行置换
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问row col";
        }

        //对RightXor(右半部分)进行SBox2置换
        row = binToDec(rightXor.mid(0, 1) + rightXor.mid(3, 1));//取第一位和最后一位组成二进制换算成十进制
        col = binToDec(rightXor.mid(1, 2));//取数组号1~2组成二进制换算成十进制....此处改动
        if (row < 4 && col < 4) {
            sboxOutput += decToBin(SBox2[row][col], 2);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问row col";
        }
    } else {
        // 处理访问越界的情况
        qDebug()<<"Error:xorResult.length() < 8";
    }

    //SP盒进行P置换
    QString spboxOutput;
    for (int i : SP) {
        if (i - 1 < sboxOutput.length()) {
            spboxOutput += sboxOutput.at(i - 1);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问Sp";
        }
    }

    return spboxOutput;//一轮F函数运算所得结果(每一轮除了F函数运算还有一次异或xor运算＋左右半边交换)
}

//初始置换盒(IP置换)
QString SDES::initialPermutation(const QString &plaintext)
{
    QString permutedPlaintext;
    for (int i : IP) {
        if (i - 1 < plaintext.length()) {
            permutedPlaintext += plaintext.at(i - 1);
        } else {
            qDebug()<<"Error:越界访问IP";
        }
    }
    return permutedPlaintext;
}

//最终置换盒(IP-1逆置换)
QString SDES::finalPermutation(const QString &ciphertext)
{
    QString permutedCiphertext;
    for (int i : IP_inverse) {
        if (i - 1 < ciphertext.length()) {
            permutedCiphertext += ciphertext.at(i - 1);
        } else {
            // 处理访问越界的情况
            qDebug()<<"Error:越界访问IP_inverse";
        }
    }
    return permutedCiphertext;
}

//加密算法
QString SDES::encrypt(const QString &plaintext, const QString &key)
{
    QString ip = initialPermutation(plaintext);

    QString subkey1 = keyExpansion(key, 1);//向左移动一位
    QString subkey2 = keyExpansion(key, 2);//在上一个密钥基础上再移动一位

    QString left, right;
    if (ip.length() >= 8) {
        left = ip.mid(0, 4);//L0
        right = ip.mid(4, 4);//R0

        QString fResult = F(right, subkey1);

        QString leftXor, rightXor;
        leftXor = right;//L1...有改动
        rightXor = "";//R1
        // L1与F(R0,K1)进行异或xor运算
        for (int i = 0; i < left.length(); ++i) {
            if (i < fResult.length() && left.at(i) == fResult.at(i)) {
                rightXor += '0';
            } else {
                rightXor += '1';
            }
        }

        QString fResult2 = F(rightXor, subkey2);

        QString leftXor2, rightXor2;
        leftXor2 = rightXor;//L2
        rightXor2 = "";//R2
        // L2与F(R0,K1)进行异或xor运算
        for (int i = 0; i < leftXor.length(); ++i) {
            if (i < fResult2.length() && leftXor.at(i) == fResult2.at(i)) {
                rightXor2 += '0';
            } else {
                rightXor2 += '1';
            }
        }

        QString ciphertext = rightXor2 + leftXor2;

        return finalPermutation(ciphertext);
    } else {
        // 处理访问越界的情况
        qDebug()<<"Error:ip.length() < 8 11";
        return "";
    }
}

QString SDES::decrypt(const QString &ciphertext, const QString &key)
{
    QString ip = initialPermutation(ciphertext);

    QString subkey1 = keyExpansion(key, 2);
    QString subkey2 = keyExpansion(key, 1);

    QString left, right;
    if (ip.length() >= 8) {
        left = ip.mid(0, 4);//L0
        right = ip.mid(4, 4);//R0

        QString fResult = F(right, subkey1);

        QString leftXor, rightXor;
        leftXor = right;//L1...有改动
        rightXor = "";//R1
        // L1与F(R0,K1)进行异或xor运算
        for (int i = 0; i < left.length(); ++i) {
            if (i < fResult.length() && left.at(i) == fResult.at(i)) {
                rightXor += '0';
            } else {
                rightXor += '1';
            }
        }

        QString fResult2 = F(rightXor, subkey2);

        QString leftXor2, rightXor2;
        leftXor2 = rightXor;//L2
        rightXor2 = "";//R2
        // L2与F(R0,K1)进行异或xor运算
        for (int i = 0; i < leftXor.length(); ++i) {
            if (i < fResult2.length() && leftXor.at(i) == fResult2.at(i)) {
                rightXor2 += '0';
            } else {
                rightXor2 += '1';
            }
        }

        QString plaintext = rightXor2 + leftXor2;

        return finalPermutation(plaintext);
    } else {
        // 处理访问越界的情况
        qDebug()<<"Error:ip.length() < 8 22";
        return "";
    }
}
>`
### mainwidget.cpp
`<// 各页面间跳转
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
>`
### encryptionwidget.cpp
`<void EncryptWidget::encrypt()
{
    QString plainText = m_plainTextEdit->toPlainText();
    QString key = m_keyEdit->text();

    if (plainText.isEmpty() || key.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "加密失败：请输入密文和密钥");
        return;
    }
    if (key.length() != 10) { // 检查是否为10bit的密钥
        QMessageBox::information(this, "提示", "加密失败：请输入10bit的密钥");
        return;
    }
    // 检查输入是否为ASCII编码字符串或二进制字符串
    bool isAscii = true;
    bool isBinary = true;
    for (int i = 0; i < plainText.length(); i++) {
        if (plainText[i].unicode() > 255) {
            isAscii = false;
        }
        if (plainText[i] != '0' && plainText[i] != '1') {
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
        QMessageBox::information(this, "提示", "加密失败：明文需要是二进制或能转化为ASCII的字符串");
        return;
    }

    QString encryptedText;
    if (isBinary && plainText.length() == 8) {
        QString encryptedBinaryText = m_sdes.encrypt(plainText, key);
        encryptedText = encryptedBinaryText;
    }
    else if(isBinary && plainText.length() != 8){
        QMessageBox::information(this, "提示", "加密失败：明文需要是8bit二进制数或能转化为ASCII的字符串");
        return;
    }
    else {

        for (int i = 0; i < plainText.length(); i++) {
            // 将ASCII编码字符串转换为二进制字符串进行加密
            QString binaryChar = QString("%1").arg(plainText[i].unicode(), 8, 2, QChar('0'));
            QString encryptedBinaryText = m_sdes.encrypt(binaryChar, key);

            // 将加密后的二进制字符串转换为ASCII编码字符串输出
            QChar asciiChar(encryptedBinaryText.toInt(nullptr, 2));
            encryptedText += asciiChar;
        }
    }

    m_cipherLabel->setText(encryptedText);
    m_cipherLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}
>`
### decryptionwidget.cpp
`<void DecryptWidget::decrypt()
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
}>`
### crackwidget.cpp
`<//单线程暴力破解关键代码
void CrackWidget::crack()
{
    // 获取开始时间戳
    qint64 startTime = QDateTime::currentMSecsSinceEpoch();

    QStringList plainTextList = m_plainTextEdit->toPlainText().split("\n");
    QStringList cipherTextList = m_cipherTextEdit->toPlainText().split("\n");

    if (plainTextList.isEmpty() || cipherTextList.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "破解失败：请输入明文和密文");
        return;
    }

    if (plainTextList.size() != cipherTextList.size()) { // 检查明文和密文数量是否一致
        QMessageBox::information(this, "提示", "破解失败：明文和密文数量不一致");
        return;
    }

    QString key;
    bool found = false;

    for (int k = 0; k < 1024; k++) { // 枚举所有可能的密钥
        QString binaryKey = QString("%1").arg(k, 10, 2, QChar('0'));

        bool success = true;
        for (int i = 0; i < plainTextList.size(); i++) {
            QString encryptedBinaryText = m_sdes.encrypt(plainTextList[i], binaryKey);
            if (encryptedBinaryText != cipherTextList[i]) {
                success = false;
                break;
            }
        }

        if (success) { // 找到正确的密钥
            key = binaryKey;
            found = true;
            break;
        }
    }

    if (found) {
        m_keyEdit->setText(key);
    } else {
        QMessageBox::information(this, "提示", "破解失败：未找到正确的密钥");
    }

    // 获取结束时间戳
    qint64 endTime = QDateTime::currentMSecsSinceEpoch();

    // 计算破解时长并显示
    qint64 elapsedTime = endTime - startTime;
    m_timeLabel->setText(QString("破解时长：%1 毫秒").arg(elapsedTime));
}

//多线程暴力破解关键代码
void CrackWidget::crack()
{
    QStringList plainTextList = m_plainTextEdit->toPlainText().split("\n");
    QStringList cipherTextList = m_cipherTextEdit->toPlainText().split("\n");

    if (plainTextList.isEmpty() || cipherTextList.isEmpty()) { // 检查输入是否为空
        QMessageBox::information(this, "提示", "破解失败：请输入明文和密文");
        return;
    }

    if (plainTextList.size() != cipherTextList.size()) { // 检查明文和密文数量是否一致
        QMessageBox::information(this, "提示", "破解失败：明文和密文数量不一致");
        return;
    }

    QTime startTime = QTime::currentTime(); // 记录开始时间

    QString key;
    bool found = false;

    // 创建多个线程
    QList<QThread*> threads;
    QList<CrackWorker*> workers;
    for (int i = 0; i < QThread::idealThreadCount(); i++) {
        CrackWorker *worker = new CrackWorker(&m_sdes, plainTextList, cipherTextList);
        QThread *thread = new QThread(this);
        worker->moveToThread(thread);
        connect(thread, &QThread::started, worker, &CrackWorker::process);
        threads.append(thread);
        workers.append(worker);
    }

    // 启动所有线程
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->start();
    }

    // 等待所有线程完成
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->wait();
    }

    // 查找是否有正确的密钥
    for (int i = 0; i < workers.size(); i++) {
        if (workers[i]->isKeyFound()) {
            key = workers[i]->getKey();
            found = true;
            break;
        }
    }

    if (found) {
        m_keyEdit->setText(key);
    } else {
        QMessageBox::information(this, "提示", "破解失败：未找到正确的密钥");
    }

    QTime endTime = QTime::currentTime(); // 记录结束时间
    int elapsedTime = startTime.msecsTo(endTime); // 计算破解时长
    QMessageBox::information(this, "提示", QString("破解完成，用时 %1 毫秒").arg(elapsedTime));
}

>`
### crackworker.cpp
`<//多线程暴力破解关键代码
void CrackWorker::process() {
    for (int i = 0; i < 1024; i++) {
        QString key = QString("%1%2%3%4%5%6%7%8")
            .arg((i & 0x01) ? "1" : "0")
            .arg((i & 0x02) ? "1" : "0")
            .arg((i & 0x04) ? "1" : "0")
            .arg((i & 0x08) ? "1" : "0")
            .arg((i & 0x10) ? "1" : "0")
            .arg((i & 0x20) ? "1" : "0")
            .arg((i & 0x40) ? "1" : "0")
            .arg((i & 0x80) ? "1" : "0");

        bool match = true;
        for (int j = 0; j < m_plainTextList.size(); j++) {
            QString plainText = m_plainTextList[j];
            QString cipherText = m_cipherTextList[j];

            QString encryptedText = m_sdes->encrypt(plainText,key);
            if (encryptedText != cipherText) {
                match = false;
                break;
            }
        }

        if (match) {
            m_key = key;
            m_keyFound = true;
            emit keyFound(key);
            return;
        }
    }>`
}

