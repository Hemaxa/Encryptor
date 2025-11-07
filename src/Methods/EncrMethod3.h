#pragma once
#include "BaseEncrMethod.h"
#include <QMap>

class EncrMethod3 : public BaseEncrMethod
{
public:
    EncrMethod3();
    QString encrypt(const QString& text) override;
    QString decrypt(const QString& text) override;
    QString methodName() const override { return "3. Замена последних 3 букв (таблица)"; }

private:
    void initMaps();
    QMap<QChar, QChar> m_encryptMap;
    QMap<QChar, QChar> m_decryptMap;

    const QString m_tableFileName = ":/table.txt";
    bool m_mapsInitialized = false;
};
