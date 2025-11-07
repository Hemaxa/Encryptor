#pragma once
#include "BaseEncrMethod.h"

class EncrMethod5 : public BaseEncrMethod
{
public:
    QString encrypt(const QString& text) override;
    QString decrypt(const QString& text) override;
    QString methodName() const override { return "5. Переворот блоков (3)"; }

private:
    QString processBlocks(const QString& text);
};
