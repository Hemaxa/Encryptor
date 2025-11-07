#include "EncrMethod3.h"

#include <QStringList>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <stdexcept>

EncrMethod3::EncrMethod3() {}

void EncrMethod3::initMaps()
{
    if (m_mapsInitialized) {
        return;
    }

    QFile file(m_tableFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Файл таблицы (table.txt) не найден.");
    }

    QByteArray fileData = file.readAll();
    file.close();

    QString fileContent = QString::fromUtf8(fileData);
    QStringList lines = fileContent.split('\n');

    if (lines.size() < 2) {
        throw std::runtime_error("Файл таблицы не содержит двух строк.");
    }

    QString from = lines[0].trimmed();
    QString to = lines[1].trimmed();

    if (from.length() != to.length()) {
        throw std::runtime_error("Строки в файле таблицы имеют разную длину.");
    }

    for (int i = 0; i < from.length(); ++i) {
        m_encryptMap[from[i]] = to[i];
        m_decryptMap[to[i]] = from[i];
    }
    m_mapsInitialized = true;
}

QString EncrMethod3::encrypt(const QString& text)
{
    initMaps();
    if (!m_mapsInitialized) return text;

    QStringList parts = text.split(QRegularExpression("(\\s+)"));
    QString result;

    for (QString word : parts) {
        if (word.trimmed().isEmpty()) {
            result += word;
            continue;
        }

        int len = word.length();

        if (len >= 1) {
            QChar upperChar = word[len - 1].toUpper();
            if (m_encryptMap.contains(upperChar)) {
                word[len - 1] = m_encryptMap.value(upperChar);
            }
        }

        if (len >= 2) {
            QChar upperChar = word[len - 2].toUpper();
            if (m_encryptMap.contains(upperChar)) {
                word[len - 2] = m_encryptMap.value(upperChar);
            }
        }

        if (len >= 3) {
            QChar upperChar = word[len - 3].toUpper();
            if (m_encryptMap.contains(upperChar)) {
                word[len - 3] = m_encryptMap.value(upperChar);
            }
        }

        result += word;
    }
    return result;
}

QString EncrMethod3::decrypt(const QString& text)
{
    initMaps();
    if (!m_mapsInitialized) return text;

    QStringList parts = text.split(QRegularExpression("(\\s+)"));
    QString result;

    for (QString word : parts) {
        if (word.trimmed().isEmpty()) {
            result += word;
            continue;
        }

        int len = word.length();

        if (len >= 1) {
            if (m_decryptMap.contains(word[len - 1])) {
                word[len - 1] = m_decryptMap.value(word[len - 1]);
            }
        }

        if (len >= 2) {
            if (m_decryptMap.contains(word[len - 2])) {
                word[len - 2] = m_decryptMap.value(word[len - 2]);
            }
        }

        if (len >= 3) {
            if (m_decryptMap.contains(word[len - 3])) {
                word[len - 3] = m_decryptMap.value(word[len - 3]);
            }
        }

        result += word;
    }
    return result;
}
