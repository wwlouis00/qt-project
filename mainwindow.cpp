#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 設定視窗標題與大小
    setWindowTitle("我的第一個 Qt 程式");
    resize(400, 300);

    // 建立一個中央 Widget 與垂直排版管理器
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 建立文字標籤
    QLabel *label = new QLabel("歡迎使用 Qt C++！", this);
    label->setAlignment(Qt::AlignCenter); // 文字置中

    // 建立按鈕
    QPushButton *button = new QPushButton("點擊我", this);

    // 將元件加入排版中
    layout->addWidget(label);
    layout->addWidget(button);

    setCentralWidget(centralWidget);

    // 連結按鈕點擊事件：當按鈕被按下時，改變文字標籤的內容
    connect(button, &QPushButton::clicked, [label]() {
        label->setText("按鈕被點擊了！");
    });
}

MainWindow::~MainWindow() {}
