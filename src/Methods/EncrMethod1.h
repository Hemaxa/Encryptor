#pragma once
#include "BaseEncrMethod.h"

class EncrMethod1 : public BaseEncrMethod
{
public:
    QString encrypt(const QString& text) override;
    QString decrypt(const QString& text) override;
    QString methodName() const override { return "1. Сдвиг нечетных символов влево"; }
};
