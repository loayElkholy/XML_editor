#ifndef JSON_H
#define JSON_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include <QtWidgets>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include<QIcon>
#include<QPixmap>
#include <QWidget>
#include <fstream>
#include <QTextEdit>
namespace Ui {
class json;
}

class json : public QWidget
{
    Q_OBJECT

public:
    explicit json(QWidget *parent = nullptr);
    ~json();
private slots:
    void on_push_button_clicked();
    void on_push_button_2_clicked();
private:
    Ui::json *ui;
    QPushButton *pushButton= new QPushButton;
    QPushButton *pushButton_2 = new QPushButton;
    QTextEdit *textEdit =new QTextEdit;
    void connect_fun();
    void connect_fun_2();

};

#endif // JSON_H
