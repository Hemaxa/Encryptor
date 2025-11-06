#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "EncrMethod1.h"
#include "EncrMethod2.h"
#include "EncrMethod3.h"
#include "EncrMethod4.h"
#include "EncrMethod5.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("MainWindow");

    m_ciphers.append(QSharedPointer<BaseEncrMethod>(new EncrMethod1));
    m_ciphers.append(QSharedPointer<BaseEncrMethod>(new EncrMethod2));
    m_ciphers.append(QSharedPointer<BaseEncrMethod>(new EncrMethod3));
    m_ciphers.append(QSharedPointer<BaseEncrMethod>(new EncrMethod4));
    m_ciphers.append(QSharedPointer<BaseEncrMethod>(new EncrMethod5));

    if (!m_ciphers.isEmpty()) {
        m_currentCipher = m_ciphers.first().data();
    }

    setupUI();
    setWindowTitle("Шифратор");
    resize(700, 500);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    m_inputText = new QTextEdit;
    m_inputText->setPlaceholderText("Введите текст здесь или загрузите из файла...");

    m_outputText = new QTextEdit;
    m_outputText->setPlaceholderText("Результат шифрования/дешифрования...");
    m_outputText->setReadOnly(true);

    m_loadButton = new QPushButton("Загрузить из файла...");
    m_saveButton = new QPushButton("Сохранить в файл...");

    m_methodCombo = new QComboBox;
    for (const auto& cipher : m_ciphers) {
        m_methodCombo->addItem(cipher->methodName());
    }

    m_encryptButton = new QPushButton("Зашифровать");
    m_decryptButton = new QPushButton("Расшифровать");

    m_statusLabel = new QLabel("Готов к работе.");
    m_statusLabel->setObjectName("m_statusLabel");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* fileLayout = new QHBoxLayout;
    fileLayout->addWidget(m_loadButton);
    fileLayout->addStretch();
    fileLayout->addWidget(m_saveButton);

    QHBoxLayout* actionLayout = new QHBoxLayout;
    actionLayout->addWidget(m_encryptButton);
    actionLayout->addWidget(m_decryptButton);

    mainLayout->addWidget(new QLabel("Исходный текст:"));
    mainLayout->addWidget(m_inputText, 1);
    mainLayout->addLayout(fileLayout);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(new QLabel("Метод шифрования:"));
    mainLayout->addWidget(m_methodCombo);
    mainLayout->addLayout(actionLayout);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(new QLabel("Результат:"));
    mainLayout->addWidget(m_outputText, 1);
    mainLayout->addWidget(m_statusLabel);

    connect(m_loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
    connect(m_encryptButton, &QPushButton::clicked, this, &MainWindow::onEncryptClicked);
    connect(m_decryptButton, &QPushButton::clicked, this, &MainWindow::onDecryptClicked);

    connect(m_methodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int index) {
                if (index >= 0 && index < m_ciphers.size()) {
                    m_currentCipher = m_ciphers[index].data();
                    m_statusLabel->setText("Выбран метод: " + m_currentCipher->methodName());
                }
            });
}

void MainWindow::onEncryptClicked()
{
    if (!m_currentCipher) {
        m_statusLabel->setText("Ошибка: Шифр не выбран.");
        return;
    }
    QString inputText = m_inputText->toPlainText();
    if (inputText.isEmpty()) {
        m_statusLabel->setText("Ошибка: Введите текст для шифрования.");
        return;
    }

    try {
        QString encryptedText = m_currentCipher->encrypt(inputText);
        m_outputText->setText(encryptedText);
        m_statusLabel->setText("Текст успешно зашифрован.");
    } catch (const std::exception& e) {
        m_statusLabel->setText(QString("Ошибка шифрования: %1").arg(e.what()));
    }
}

void MainWindow::onDecryptClicked()
{
    if (!m_currentCipher) {
        m_statusLabel->setText("Ошибка: Шифр не выбран.");
        return;
    }
    QString inputText = m_inputText->toPlainText();
    if (inputText.isEmpty()) {
        m_statusLabel->setText("Ошибка: Введите текст для дешифрования.");
        return;
    }

    try {
        QString decryptedText = m_currentCipher->decrypt(inputText);
        m_outputText->setText(decryptedText);
        m_statusLabel->setText("Текст успешно расшифрован.");
    } catch (const std::exception& e) {
        m_statusLabel->setText(QString("Ошибка дешифрования: %1").arg(e.what()));
    }
}

void MainWindow::onLoadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_statusLabel->setText("Ошибка: Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    m_inputText->setText(in.readAll());
    file.close();
    m_statusLabel->setText("Файл успешно загружен.");
}

void MainWindow::onSaveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_statusLabel->setText("Ошибка: Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    out << m_outputText->toPlainText();
    file.close();
    m_statusLabel->setText("Файл успешно сохранен.");
}
