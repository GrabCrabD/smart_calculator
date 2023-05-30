#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QVector>
#include <cmath>


extern "C" {
    #include"s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double step = 0.1;
    QVector<double> x, y;
private slots:
    void ButPressed();
    void ClearLineEdit();
    void EqualButton_clicked();
    //    void AtionPressed();
    void GraphicButton_clicked();
};
#endif // MAINWINDOW_H
