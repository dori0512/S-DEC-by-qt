#include "crackworker.h"

CrackWorker::CrackWorker(SDES *sdes, const QStringList &plainTextList, const QStringList &cipherTextList, QObject *parent)
    : QObject(parent), m_sdes(sdes), m_plainTextList(plainTextList), m_cipherTextList(cipherTextList), m_keyFound(false) {}

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
    }
}
