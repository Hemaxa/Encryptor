#include "EncrMethod4.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <stdexcept>

QString EncrMethod4::encrypt(const QString& text)
{
    QString key = generateKeyFile(text.length());
    if (key.length() != text.length()) {
        throw std::runtime_error("Не удалось сгенерировать файл ключа нужной длины.");
    }

    QString result;
    for (int i = 0; i < text.length(); ++i) {
        if (i % 2 != 0) {
            int value = text[i].unicode() - key[i].unicode() + i;
            result += QString("<%1>").arg(value);
        } else {
            result += text[i];
        }
    }
    return result;
}

QString EncrMethod4::decrypt(const QString& text)
{
    QString key = readKeyFile();
    if (key.isEmpty()) {
        throw std::runtime_error("Файл ключа (method4_key.txt) не найден или пуст.");
    }

    QString result;
    int keyIndex = 0;
    int textIndex = 0;

    while (textIndex < text.length()) {
        if (keyIndex >= key.length()) {
            throw std::runtime_error("Ошибка формата: шифртекст не соответствует ключу.");
        }

        if (keyIndex % 2 != 0) {
            if (text[textIndex] != '<') {
                throw std::runtime_error("Ошибка формата: ожидался '<'.");
            }

            textIndex++;
            int endIndex = text.indexOf('>', textIndex);
            if (endIndex == -1) {
                throw std::runtime_error("Ошибка формата: ожидался '>'.");
            }

            QString numStr = text.mid(textIndex, endIndex - textIndex);
            bool ok;
            int value = numStr.toInt(&ok);
            if (!ok) {
                throw std::runtime_error("Ошибка формата: не удалось прочитать число.");
            }

            QChar originalChar = QChar(value + key[keyIndex].unicode() - keyIndex);
            result += originalChar;

            textIndex = endIndex + 1;
        } else {
            result += text[textIndex];
            textIndex++;
        }

        keyIndex++;
    }

    return result;
}

QString EncrMethod4::generateKeyFile(int length)
{
    QFile file(m_keyFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не могу создать файл ключа.");
    }

    QTextStream out(&file);
    QString key;
    for (int i = 0; i < length; ++i) {
        QChar randomChar(QRandomGenerator::global()->bounded(33, 127));
        key.append(randomChar);
        out << randomChar;
    }
    file.close();
    return key;
}

QString EncrMethod4::readKeyFile()
{
    QFile file(m_keyFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream in(&file);
    QString key = in.readAll();
    file.close();
    return key;
}
