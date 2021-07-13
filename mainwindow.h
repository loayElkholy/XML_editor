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
    void parse_xml(vector<xml_parse> &xml, string line, int &line_number);
private slots:
    void on_push_button_clicked();
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
