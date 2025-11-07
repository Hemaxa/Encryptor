#include "EncrMethod5.h"
#include <QStringList>
#include <algorithm>

QString EncrMethod5::processBlocks(const QString& text)
{
    QString paddedText = text;
    while (paddedText.length() % 3 != 0) {
        paddedText.append(' ');
    }

    QString result;
    for (int i = 0; i < paddedText.length(); i += 3) {
        QString block = paddedText.mid(i, 3);
        std::reverse(block.begin(), block.end());
        result.append(block);
    }

    return result;
}

QString EncrMethod5::encrypt(const QString& text)
{
    return processBlocks(text);
}

QString EncrMethod5::decrypt(const QString& text)
{
    QString decryptedPaddedText = processBlocks(text);
    return decryptedPaddedText.trimmed();
}
