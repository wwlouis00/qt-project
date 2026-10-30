#include "mainwindow.h"
#include <QVBoxLayout>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 建立顯示螢幕
    display = new QLineEdit("0", this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setStyleSheet("font-size: 28px; padding: 10px;");
    mainLayout->addWidget(display);

    // 建立按鈕網格
    QGridLayout *gridLayout = new QGridLayout();
    QString buttonLabels[4][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", "C", "=", "+"}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            QString text = buttonLabels[row][col];
            QPushButton *btn = new QPushButton(text, this);
            btn->setStyleSheet("font-size: 20px; min-height: 50px;");

            if (text == "C") {
                connect(btn, &QPushButton::clicked, this, &MainWindow::onClearClicked);
            } else if (text == "=") {
                connect(btn, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
            } else if (text == "+" || text == "-" || text == "*" || text == "/") {
                connect(btn, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
            } else {
                connect(btn, &QPushButton::clicked, this, &MainWindow::onNumberClicked);
            }

            gridLayout->addWidget(btn, row, col);
        }
    }

    mainLayout->addLayout(gridLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Qt 計算機 (純程式碼版)");
    resize(320, 420);
}

MainWindow::~MainWindow() {}

void MainWindow::onNumberClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    if (display->text() == "0" || waitingForOperand) {
        display->setText(btn->text());
        waitingForOperand = false;
    } else {
        display->setText(display->text() + btn->text());
    }
}

void MainWindow::onOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString clickedOperator = btn->text();
    double operand = display->text().toDouble();

    if (!pendingOperator.isEmpty()) {
        if (!calculate(operand, pendingOperator)) {
            display->setText("Error");
            return;
        }
        display->setText(QString::number(pendingOperand));
    } else {
        pendingOperand = operand;
    }

    pendingOperator = clickedOperator;
    waitingForOperand = true;
}

void MainWindow::onEqualClicked()
{
    double operand = display->text().toDouble();

    if (!pendingOperator.isEmpty()) {
        if (!calculate(operand, pendingOperator)) {
            display->setText("Error");
            return;
        }
        display->setText(QString::number(pendingOperand));
        pendingOperator.clear();
    }

    waitingForOperand = true;
}

void MainWindow::onClearClicked()
{
    pendingOperand = 0.0;
    pendingOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

bool MainWindow::calculate(double rightOperand, const QString &op)
{
    if (op == "+") {
        pendingOperand += rightOperand;
    } else if (op == "-") {
        pendingOperand -= rightOperand;
    } else if (op == "*") {
        pendingOperand *= rightOperand;
    } else if (op == "/") {
        if (rightOperand == 0.0) return false;
        pendingOperand /= rightOperand;
    }
    return true;
}