#include "sdes.h"
#include <QDebug>

SDES::SDES()
{
    // 定义所需的转换装置和置换表
    P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    P8 = {6, 3, 7, 4, 8, 5, 10, 9};
    LS1 = {2, 3, 4, 5, 1};
    LS2 = {3, 4, 5, 1, 2};
    //const std::vector<int>
    IP = {2, 6, 3, 1, 4, 8, 5, 7};
    IP_inverse = {4, 1, 3, 5, 7, 2, 8, 6};
    EP = {4, 1, 2, 3, 2, 3, 4, 1};
    //const std::vector<std::vector<int>>
    SBox1 = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 0, 2}};
    //const std::vector<std::vector<int>>
    SBox2 = {{0, 1, 2, 3}, {2, 3, 1, 0}, {3, 0, 1, 2}, {2, 1, 0, 3}};
    SP = {2, 4, 3, 1};
}

QString SDES::decToBin(int num, int width)
{
    QString binStr = QString("%1").arg(num, width, 2, QChar('0'));//其中第一个参数是要填充的数字，第二个参数为最小宽度，第二个参数为进制，第四个参数为当原始数字长度不足最小宽度时用于填充的字符。
    return binStr.right(width);//取其填充后的最小宽度(width)
}

//检测字符若为二进制，则将其转化为int类整数型
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
