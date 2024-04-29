#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QTimer>
#include "ui_mainwindow.h"
#include <QSoundEffect>
//#include"mypushbutton.h"
//#include"gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //设置背景的函数
    void paintEvent(QPaintEvent *);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
