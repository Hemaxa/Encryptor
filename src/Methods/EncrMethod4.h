#pragma once
#include "BaseEncrMethod.h"

class EncrMethod4 : public BaseEncrMethod
{
public:
    QString encrypt(const QString& text) override;
    QString decrypt(const QString& text) override;
    QString methodName() const override { return "4. Четный символ + код из файла"; }

private:
    const QString m_keyFileName = "method4_key.txt";
    QString generateKeyFile(int length);
    QString readKeyFile();
};
