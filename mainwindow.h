#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void operatorClicked();
    void unaryFunctionClicked();
    void clearClicked();
    void equalsClicked();
    void toggleDegRad();

private:
    Ui::MainWindow *ui;
    bool degMode;
    double applyUnaryFunction(const QString& func, double x);
    double factorial(double x);
};
#endif
