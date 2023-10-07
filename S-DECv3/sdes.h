#ifndef SDES_H
#define SDES_H

#include <QString>
#include <QVector>

class SDES
{
public:
    SDES();

    QString encrypt(const QString &plaintext, const QString &key);
    QString decrypt(const QString &ciphertext, const QString &key);

private:
    std::vector<int> P10;
    std::vector<int> P8;
    std::vector<int> LS1;
    std::vector<int> LS2;
    std::vector<int> IP;
    std::vector<int> IP_inverse;
    std::vector<int> EP;
    std::vector<std::vector<int>> SBox1;
    std::vector<std::vector<int>> SBox2;
    std::vector<int> SP;

    QString decToBin(int num, int width);
    int binToDec(const QString &binStr);
    QString keyExpansion(const QString &key, int round);
    QString F(const QString &right, const QString &subkey);
    QString initialPermutation(const QString &plaintext);
    QString finalPermutation(const QString &ciphertext);
};

#endif // SDES_H
