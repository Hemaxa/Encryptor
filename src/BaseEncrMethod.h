#pragma once

#include <QString>

class BaseEncrMethod
{
public:
    virtual ~BaseEncrMethod() = default;

    virtual QString encrypt(const QString& text) = 0;
    virtual QString decrypt(const QString& text) = 0;
    virtual QString methodName() const = 0;
};
