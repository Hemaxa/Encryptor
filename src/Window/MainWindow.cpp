#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpacerItem>

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
    setWindowTitle("Encryptor");
    resize(900, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QVBoxLayout* fullLayout = new QVBoxLayout(this);
    fullLayout->setContentsMargins(10, 10, 10, 10);
    fullLayout->setSpacing(0);

    QHBoxLayout* mainContentLayout = new QHBoxLayout();
    mainContentLayout->setSpacing(10);
    mainContentLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* controlPanel = new QWidget;
    controlPanel->setObjectName("controlPanel");
    controlPanel->setFixedWidth(220);

    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);
    controlLayout->setContentsMargins(15, 15, 15, 15);
    controlLayout->setSpacing(10);

    QLabel* titleLabel = new QLabel("ENCRYPTOR");
    titleLabel->setObjectName("titleLabel");
    controlLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    controlLayout->addSpacing(20);

    m_loadButton = new QPushButton("Загрузить");
    m_loadButton->setObjectName("fileButton");
    controlLayout->addWidget(m_loadButton);

    m_saveButton = new QPushButton("Сохранить");
    m_saveButton->setObjectName("fileButton");
    controlLayout->addWidget(m_saveButton);

    controlLayout->addSpacing(20);

    QLabel* methodLabel = new QLabel("Метод:");
    methodLabel->setObjectName("controlLabel");
    controlLayout->addWidget(methodLabel);

    m_methodCombo = new QComboBox;
    for (const auto& cipher : m_ciphers) {
        m_methodCombo->addItem(cipher->methodName());
    }
    controlLayout->addWidget(m_methodCombo);

    controlLayout->addStretch(1);

    QWidget* editorPanel = new QWidget;
    editorPanel->setObjectName("editorPanel");

    QGridLayout* editorLayout = new QGridLayout(editorPanel);
    editorLayout->setSpacing(10);

    QLabel* inputLabel = new QLabel("Исходный текст:");
    editorLayout->addWidget(inputLabel, 0, 0);

    QLabel* outputLabel = new QLabel("Результат:");
    editorLayout->addWidget(outputLabel, 0, 2);

    m_inputText = new QTextEdit;
    m_inputText->setPlaceholderText("...");
    editorLayout->addWidget(m_inputText, 1, 0);

    m_outputText = new QTextEdit;
    m_outputText->setPlaceholderText("...");
    m_outputText->setReadOnly(true);
    editorLayout->addWidget(m_outputText, 1, 2);

    QVBoxLayout* actionLayout = new QVBoxLayout;
    actionLayout->setSpacing(15);
    actionLayout->addStretch(1);

    m_encryptButton = new QPushButton(">");
    m_encryptButton->setObjectName("encryptButton");
    m_encryptButton->setToolTip("Зашифровать");
    actionLayout->addWidget(m_encryptButton);

    m_decryptButton = new QPushButton("<");
    m_decryptButton->setObjectName("decryptButton");
    m_decryptButton->setToolTip("Расшифровать");
    actionLayout->addWidget(m_decryptButton);

    actionLayout->addStretch(1);

    editorLayout->addLayout(actionLayout, 1, 1);

    editorLayout->setColumnStretch(0, 1);
    editorLayout->setColumnStretch(1, 0);
    editorLayout->setColumnStretch(2, 1);

    mainContentLayout->addWidget(controlPanel);
    mainContentLayout->addWidget(editorPanel, 1);

    m_statusLabel = new QLabel("Готов");
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setWordWrap(true);
    m_statusLabel->setAlignment(Qt::AlignCenter);

    fullLayout->addLayout(mainContentLayout, 1);
    fullLayout->addWidget(m_statusLabel);

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

    if (m_currentCipher) {
        m_statusLabel->setText("Выбран метод: " + m_currentCipher->methodName());
    }
}

void MainWindow::onEncryptClicked()
{
    if (!m_currentCipher) {
        m_statusLabel->setText("Ошибка: Шифр не выбран.");
        return;
    }
    QString inputText = m_inputText->toPlainText();
    if (inputText.isEmpty()) {
        m_statusLabel->setText("Ошибка: Введите текст.");
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
        m_statusLabel->setText("Ошибка: Введите текст.");
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
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_statusLabel->setText("Ошибка открытия файла.");
        return;
    }

    QTextStream in(&file);
    m_inputText->setText(in.readAll());
    file.close();
    m_statusLabel->setText("Файл успешно загружен.");
}

void MainWindow::onSaveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_statusLabel->setText("Ошибка сохранения файла.");
        return;
    }

    QTextStream out(&file);
    out << m_outputText->toPlainText();
    file.close();
    m_statusLabel->setText("Файл успешно сохранен.");
}
