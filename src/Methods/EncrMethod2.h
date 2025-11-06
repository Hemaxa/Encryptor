#pragma once
#include "BaseEncrMethod.h"

class EncrMethod2 : public BaseEncrMethod
{
public:
    QString encrypt(const QString& text) override;
    QString decrypt(const QString& text) override;
    QString methodName() const override { return "2. Переворот слова + сдвиг"; }
};
