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

        std::reverse(word.begin(), word.end());

        if (word.length() >= 2) {
            std::swap(word[0], word[1]);
        }
        result += word;
    }
    return result;
}

QString EncrMethod2::decrypt(const QString& text)
{
    QStringList parts = text.split(QRegularExpression("(\\s+)"));
    QString result;

    for (QString& word : parts) {
        if (word.trimmed().isEmpty()) {
            result += word;
            continue;
        }

        if (word.length() >= 2) {
            std::swap(word[0], word[1]);
        }

        std::reverse(word.begin(), word.end());

        result += word;
    }
    return result;
}
