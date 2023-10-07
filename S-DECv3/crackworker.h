#ifndef CRACKWORKER_H
#define CRACKWORKER_H

#include <QObject>
#include <QStringList>
#include "sdes.h"

class CrackWorker : public QObject
{
    Q_OBJECT

public:
    explicit CrackWorker(SDES *sdes, const QStringList &plainTextList, const QStringList &cipherTextList, QObject *parent = nullptr);

    bool isKeyFound() const { return m_keyFound; }
    QString getKey() const { return m_key; }


public slots:
    void process();

signals:
    void keyFound(QString key);

private:
    SDES *m_sdes;
    QStringList m_plainTextList;
    QStringList m_cipherTextList;
    QString m_key;
    bool m_keyFound;
};

#endif // CRACKWORKER_H
