#include "mainwindow.h"
#include "./ui_mainwindow.h"

QString calcVal = "0.0";
bool is_display_empty = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(calcVal);
    QPushButton *numButtons[29];
    for (int i = 0; i < 29; i++) {
        QString butName = "pushButton" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], &QPushButton::released, this, &MainWindow::ButPressed);
    }

    QPushButton *clearButton;
    clearButton = findChild<QPushButton *>("ClearButton");
    connect(clearButton, &QPushButton::released, this, &MainWindow::ClearLineEdit);

    QPushButton *equilButton;
    equilButton = findChild<QPushButton *>("Equals");
    connect(equilButton, &QPushButton::released, this, &MainWindow::EqualButton_clicked);

    QPushButton *graphicButton;
    graphicButton = findChild<QPushButton *>("Graphic");
    connect(graphicButton, &QPushButton::released, this, &MainWindow::GraphicButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButPressed() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if (is_display_empty) {
        ui->Display->setText(butVal);
        is_display_empty = false;
    } else {
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }
}


void MainWindow::ClearLineEdit() {
    ui->Display->clear();
//    ui->inputX->clear();
    is_display_empty = true;
}

void MainWindow::EqualButton_clicked()
{
    QString expression = ui->Display->text();

    if (expression.contains("x")) {
        QDoubleSpinBox* xValueSpinBox = findChild<QDoubleSpinBox*>("xExpressionValue");
        QString xValue = xValueSpinBox->text();
        QString tmp = expression;
        tmp.replace("x", xValue);
        QByteArray tmp_b_array = tmp.toLocal8Bit();
        const char *tmp_str = tmp_b_array.data();
        long double result = calculating(tmp_str);
        QString resultString = QString::number(result, 'g', 8);
        ui->Display->setText(resultString);
    } else {
        QByteArray b_array = expression.toLocal8Bit();
        const char *strin = b_array.data();
        long double result = calculating(strin);
        QString resultString = QString::number(result, 'g', 8);
        ui->Display->setText(resultString);
    }
}






void MainWindow::GraphicButton_clicked() {

    QString expression = ui->Display->text();

    if (expression.contains("x")) {
        ui->widget->clearGraphs();
        x.clear();
        y.clear();

        QSpinBox* xBeginSpinBox = findChild<QSpinBox*>("xBeginSpinBox");
        QSpinBox* xEndSpinBox = findChild<QSpinBox*>("xEndSpinBox");
        QSpinBox* yBeginSpinBox = findChild<QSpinBox*>("yBeginSpinBox");
        QSpinBox* yEndSpinBox = findChild<QSpinBox*>("yEndSpinBox");

        double xBeginValue = static_cast<double>(xBeginSpinBox->value());
        double xEndValue = static_cast<double>(xEndSpinBox->value());
        double yBeginValue = static_cast<double>(yBeginSpinBox->value());
        double yEndValue = static_cast<double>(yEndSpinBox->value());

        ui->widget->xAxis->setRange(xBeginValue, xEndValue);
        ui->widget->yAxis->setRange(yBeginValue, yEndValue);

        while (xBeginValue < xEndValue) {
            if (std::fabs(xBeginValue - 0) < 1e-8) {
                xBeginValue = 0;
            }
            QString tmp = expression;
            tmp.replace("x", "(" + QString::number(xBeginValue) + ")");
            QByteArray tmp_b_array = tmp.toLocal8Bit();
            const char *tmp_str = tmp_b_array.data();
            x.push_back(xBeginValue);
            y.push_back(calculating(tmp_str));
            xBeginValue += step;
        }
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x, y);
        ui->widget->replot();
    }else{
        ui->Display->setText("add X");
    }
}
