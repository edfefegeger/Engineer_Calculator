#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), degMode(false)
{
    ui->setupUi(this);

    QList<QPushButton*> digits = {ui->btn0, ui->btn1, ui->btn2, ui->btn3, ui->btn4,
                                  ui->btn5, ui->btn6, ui->btn7, ui->btn8, ui->btn9};
    for (auto btn : digits)
        connect(btn, &QPushButton::clicked, this, &MainWindow::digitClicked);

    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    QList<QPushButton*> funcs = {ui->btnSin, ui->btnCos, ui->btnTan, ui->btnLn, ui->btnLog,
                                 ui->btnSqrt, ui->btnSqr, ui->btnInv, ui->btnAbs,
                                 ui->btnExp, ui->btnFact};
    for (auto btn : funcs)
        connect(btn, &QPushButton::clicked, this, &MainWindow::unaryFunctionClicked);

    connect(ui->btnPi, &QPushButton::clicked, [this]() {
        ui->lineEdit->insert(QString::number(M_PI));
    });

    connect(ui->btnEqual, &QPushButton::clicked, this, &MainWindow::equalsClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(ui->btnDegRad, &QPushButton::clicked, this, &MainWindow::toggleDegRad);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digitClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) ui->lineEdit->insert(button->text());
}

void MainWindow::operatorClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) ui->lineEdit->insert(" " + button->text() + " ");
}

void MainWindow::clearClicked() {
    ui->lineEdit->clear();
}

void MainWindow::toggleDegRad() {
    degMode = !degMode;
    ui->btnDegRad->setText(degMode ? "Deg" : "Rad");
}

double MainWindow::applyUnaryFunction(const QString& func, double x) {
    if (func == "sin") return degMode ? sin(x * M_PI / 180.0) : sin(x);
    if (func == "cos") return degMode ? cos(x * M_PI / 180.0) : cos(x);
    if (func == "tan") return degMode ? tan(x * M_PI / 180.0) : tan(x);
    if (func == "ln") return log(x);
    if (func == "log") return log10(x);
    if (func == "√") return sqrt(x);
    if (func == "x²") return x * x;
    if (func == "1/x") return 1.0 / x;
    if (func == "|x|") return fabs(x);
    if (func == "e^x") return exp(x);
    if (func == "!") return factorial(x);
    return x;
}

double MainWindow::factorial(double x) {
    if (x < 0) return 0;
    double result = 1;
    for (int i = 1; i <= int(x); ++i)
        result *= i;
    return result;
}

void MainWindow::unaryFunctionClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;
    bool ok;
    double x = ui->lineEdit->text().toDouble(&ok);
    if (!ok) return;
    double result = applyUnaryFunction(button->text(), x);
    ui->lineEdit->setText(QString::number(result));
}

void MainWindow::equalsClicked() {
    QString text = ui->lineEdit->text();
    QStringList parts = text.split(" ");
    if (parts.size() != 3) return;
    double a = parts[0].toDouble();
    double b = parts[2].toDouble();
    QString op = parts[1];
    double res = 0;
    if (op == "+") res = a + b;
    else if (op == "-") res = a - b;
    else if (op == "*") res = a * b;
    else if (op == "/") res = b != 0 ? a / b : 0;
    ui->lineEdit->setText(QString::number(res));
}
