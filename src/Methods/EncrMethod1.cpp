#include "EncrMethod1.h"
#include <algorithm>

QString EncrMethod1::encrypt(const QString& text)
{
    QString result = text;
    for (int i = 1; i < result.length(); i += 2) {
        std::swap(result[i], result[i - 1]);
    }
    return result;
}

QString EncrMethod1::decrypt(const QString& text)
{
    return encrypt(text);
}
