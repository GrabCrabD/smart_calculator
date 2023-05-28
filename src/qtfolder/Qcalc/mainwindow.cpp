#include "mainwindow.h"
#include "./ui_mainwindow.h"

QString calcVal = "0.0";
bool is_empty = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(calcVal);
    QPushButton *numButtons[28];
    for (int i = 0; i < 28; i++) {
        QString butName = "pushButton" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], &QPushButton::released, this, &MainWindow::NumPressed);
    }

    QPushButton *clearButton;
    clearButton = findChild<QPushButton *>("ClearButton");
    connect(clearButton, &QPushButton::released, this, &MainWindow::ClearLineEdit);

    QPushButton *equilButton;
    equilButton = findChild<QPushButton *>("Equals");
    connect(equilButton, &QPushButton::released, this, &MainWindow::on_EqualButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if (is_empty) {
        ui->Display->setText(butVal);
        is_empty = false;
    } else {
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }
}


void MainWindow::ClearLineEdit() {
    ui->Display->clear();
    ui->inputX->clear();
    is_empty = true;
}

void MainWindow::on_EqualButton_clicked()
{
    QString expression = ui->Display->text(); // Получаем текст из QLineEdit

    QProcess process;
    process.start("/Users/dmitriy/repository/school projects/C7_SmartCalc_v1.0-1/src/a.out", QStringList() << "-expr" << expression); // Передаем выражение в аргументе командной строки
    process.waitForFinished(); // Ждем завершения процесса

    QByteArray output = process.readAllStandardOutput(); // Получаем вывод программы
    QString result = QString::fromUtf8(output); // Преобразуем вывод в строку

    // Отображаем результат парсинга в интерфейсе
    ui->Display->setText(result);

    // Очищаем QLineEdit после отправки выражения
//    ui->Display->clear();
}

