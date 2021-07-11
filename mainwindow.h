#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>

using namespace std;

struct xml_parse {
    string xml_parsed;
    int line_no;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void parse_xml(vector<xml_parse> &xml, string line, int &line_number);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
