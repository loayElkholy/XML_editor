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
#include "compress.h"

using namespace std;

Tree XML_Tree ;

void MainWindow::parse_xml(vector<xml_parse> &xml , string line, int& line_number) {
    xml_parse temp;
    int new_i = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '<' && (line[i + 1] != '!' && line[i + 1] != '?')) {
            new_i = line.find('>', i);
            temp = { line.substr(i, new_i + 1 - i), line_number };
            xml.push_back(temp);
            i = new_i - 1;
        }
        else if (line[i] == '>' && i != line.length() - 1 && line[i + 1] != '<') {
            new_i = line.find('<', i);
            temp = { line.substr(i + 1, line.length() - i), line_number };
            for (int j = 0; j < temp.xml_parsed.length(); j++) {
                if (temp.xml_parsed[j] == ' ') {
                    if (temp.xml_parsed[j] == ' ') {
                        if (j == 0) {
                            temp.xml_parsed.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.xml_parsed.length() - 1) {
                            temp.xml_parsed.erase(j, 1);
                            j = temp.xml_parsed.length() - 2;
                        }
                    }
                }
            }
            if (new_i == -1 && !temp.xml_parsed.empty()) {
                xml.push_back(temp);
                i = line.length();
            }
            else {
                temp = { line.substr(i + 1, new_i - 1 - i), line_number };
                for (int j = 0; j < temp.xml_parsed.length(); j++) {
                    if (temp.xml_parsed[j] == ' ') {
                        if (j == 0) {
                            temp.xml_parsed.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.xml_parsed.length() - 1) {
                            temp.xml_parsed.erase(j, 1);
                            j = temp.xml_parsed.length() - 2;
                        }
                    }
                }
                if (!temp.xml_parsed.empty()) {
                    xml.push_back(temp);
                }
                i = new_i - 1;
            }
        }
    }
        line_number++;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *widget= new QWidget() ;
    QHBoxLayout *main_layout =new QHBoxLayout();
    QVBoxLayout *vertical_layout =new QVBoxLayout();
    QHBoxLayout *horizontal_layout = new QHBoxLayout();
    QPixmap pixmap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-9-Open-file.ico");
    QIcon ButtonIcon(pixmap);
    QPixmap pixmap_2(":\\rec\\icons\\format.ico");
    QIcon ButtonIcon_2(pixmap_2);
    QPixmap pixmap_3(":\\rec\\icons\\json-icon-png-18.jpg");
    QIcon ButtonIcon_3(pixmap_3);
    QPixmap pixmap_4(":\\rec\\icons\\minify");
    QIcon ButtonIcon_4(pixmap_4);
    QPixmap pixmap_5(":\\rec\\icons\\compress.png");
    QIcon ButtonIcon_5(pixmap_5);




    pushButton =new QPushButton();
    pushButton->setText("Open file");
    pushButton ->setIcon(ButtonIcon);
    pushButton_2->setText("Format");
    pushButton_2 ->setIcon(ButtonIcon_2);
    pushButton_3->setText("Convert to Json");
    pushButton_3 ->setIcon(ButtonIcon_3);
    pushButton_4->setText("Minify");
    pushButton_4 ->setIcon(ButtonIcon_4);
    pushButton_5->setText("Compress");
    pushButton_5 ->setIcon(ButtonIcon_5);




    textBrowser =new QTextBrowser();

    horizontal_layout ->addWidget(pushButton);
    horizontal_layout ->addWidget(pushButton_2);
    horizontal_layout ->addWidget(pushButton_3);
    horizontal_layout ->addWidget(pushButton_4);
    horizontal_layout ->addWidget(pushButton_5);
    vertical_layout->addLayout(horizontal_layout);
    vertical_layout->addWidget(textBrowser);

    tabWidget->setTabsClosable(true);

    connect_fun();
    main_layout->addLayout(vertical_layout);
    widget->setLayout(main_layout);
    tabWidget ->addTab(widget,"input file");
    setCentralWidget(tabWidget);

}
void MainWindow::connect_fun()
{
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
    connect(pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_5_clicked()));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(on_tabWidget_tabCloseRequested(int)));
}
void MainWindow::on_push_button_clicked()
{
    QString filter = "All Files (*.*) ;; Text Files (*.txt) ;; XML Files (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"choose file","C:\\",filter);

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
        QString text;
        while (!in.atEnd()) {
            QString line = in.readLine();
            text.append(line+"\n");
            string line_string = line.toStdString();
            qDebug() << QString::fromStdString(line_string);
        }

        textBrowser->setText(text);
    file.close();
}

void MainWindow::on_pushButton_5_clicked() {
    tabWidget->addTab(new Compress(), "Compress File");
    tabWidget->setCurrentIndex(tabWidget->count() - 1);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index){
    tabWidget->removeTab(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}
























