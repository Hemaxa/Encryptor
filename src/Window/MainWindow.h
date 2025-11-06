#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVector>
#include <QSharedPointer>

#include "BaseEncrMethod.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onEncryptClicked();
    void onDecryptClicked();
    void onLoadFromFile();
    void onSaveToFile();

private:
    void setupUI();

    QTextEdit* m_inputText;
    QTextEdit* m_outputText;
    QPushButton* m_loadButton;
    QPushButton* m_saveButton;
    QPushButton* m_encryptButton;
    QPushButton* m_decryptButton;
    QComboBox* m_methodCombo;
    QLabel* m_statusLabel;

    QVector<QSharedPointer<BaseEncrMethod>> m_ciphers;
    BaseEncrMethod* m_currentCipher = nullptr;
};
