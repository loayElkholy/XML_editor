#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include <QPushButton>
#include <QTextBrowser>
#include<QTabWidget>
#include "tree.h"

using namespace std;




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connect_fun();
    void connect_fun_json();
    void parse_xml(vector<xml_parse> &xml, string line, int &line_number);

private slots:
    void on_push_button_clicked();
    void on_push_button_format_clicked();
    void on_push_button_4_clicked();
    void on_push_button_3_clicked();
    void on_pushButton_5_clicked();
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;
    QPushButton *pushButton_2 = new QPushButton;
    QPushButton *pushButton_3 = new QPushButton;
    QPushButton *pushButton_4 = new QPushButton;
    QPushButton *pushButton_5 = new QPushButton;
    QTextBrowser *textBrowser;
    QTabWidget *tabWidget = new QTabWidget;
};
#endif // MAINWINDOW_H
