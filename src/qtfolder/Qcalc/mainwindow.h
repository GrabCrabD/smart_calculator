#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QProcess>

//extern "C" {
//#include "../../s21_smart_calc.h"
//}


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
private slots:
    void NumPressed();
    void ClearLineEdit();
    void on_EqualButton_clicked();
//    void AtionPressed();
//    void FunctionPressed();
};
#endif // MAINWINDOW_H
