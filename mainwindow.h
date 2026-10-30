#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNumberClicked();
    void onOperatorClicked();
    void onEqualClicked();
    void onClearClicked();

private:
    QLineEdit *display;
    double pendingOperand = 0.0;
    QString pendingOperator;
    bool waitingForOperand = true;

    bool calculate(double rightOperand, const QString &pendingOperator);
};

#endif // MAINWINDOW_H