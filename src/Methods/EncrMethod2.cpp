#include "EncrMethod2.h"
#include <QStringList>
#include <QRegularExpression>
#include <algorithm>

QString EncrMethod2::encrypt(const QString& text)
{
    QStringList parts = text.split(QRegularExpression("(\\s+)"));
    QString result;

    for (QString& word : parts) {
        if (word.trimmed().isEmpty()) {
            result += word;
            continue;
        }

        for (int i = 1; i < word.length() - 2; i += 4) {
            std::swap(word[i], word[i + 2]);
        }
        result += word;
    }
    return result;
}

QString EncrMethod2::decrypt(const QString& text)
{
    return encrypt(text);
}
