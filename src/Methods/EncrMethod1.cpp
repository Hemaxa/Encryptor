#include "EncrMethod1.h"

QString EncrMethod1::encrypt(const QString& text)
{
    QString result;
    for (const QChar& ch : text) {
        result.append(QChar(ch.unicode() - 1));
    }
    return result;
}

QString EncrMethod1::decrypt(const QString& text)
{
    QString result;
    for (const QChar& ch : text) {
        result.append(QChar(ch.unicode() + 1));
    }
    return result;
}
