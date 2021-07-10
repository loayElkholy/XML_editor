#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <QString>
using namespace std;
class Node {
public:
   QString name ;
    QString value;
    Node* parent;
    vector <Node*> children;
    Node(QString value) : value{ value }, children{ {} }, parent{nullptr}{}
};

class Tree
{
    Node* root;
    Node* add;

public:

};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

