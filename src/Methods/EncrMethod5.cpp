#include "EncrMethod5.h"
#include <QStringList>

QString EncrMethod5::processBlocks(const QString& text)
{
    QString paddedText = text;
    while (paddedText.length() % 5 != 0) {
        paddedText.append(' ');
    }

    QStringList blocks;
    for (int i = 0; i < paddedText.length(); i += 5) {
        blocks.append(paddedText.mid(i, 5));
    }

    if (blocks.size() >= 2) {
        blocks.swapItemsAt(0, 1);
    }

    if (blocks.size() >= 5) {
        blocks.swapItemsAt(3, 4);
    }

    return blocks.join(QString());
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
