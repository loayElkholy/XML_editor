#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minify.h"
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

vector<int> compress_file(map<string, int> &table, string s1, int &mul_char_code) {
    vector<int> encoded_code;
    string current = "", next = "";
    current += s1[0];
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1) {
            next += s1[i + 1];
        }
        if (table.find(current + next) != table.end()) {
            current = current + next;
        }
        else {
            encoded_code.push_back(table[current]);
            table[current + next] = mul_char_code;
            mul_char_code++;
            current = next;
        }
        next = "";
    }
    encoded_code.push_back(table[current]);
    return encoded_code;
}

void decode(map<int, string> table_decode, vector<int> encoded_code) {
    string s;
    for (int i = 0; i < encoded_code.size(); i++) {
        s += table_decode[encoded_code[i]];
    }
    cout << s;
}

//********************************************** should be placed in button of compressing *********************************
//int mul_char_code = 256;
//vector<int> code;
//vector<int> total_code;
//map<string, int> table;
//for (int i = 0; i <= 255; i++) {
//    string character = "";
//    character += char(i);
//    table[character] = i;
//}

//map<int, string> table_decode;
//map<string, int>::iterator itr;
//for (itr = table.begin(); itr != table.end(); itr++) {
//    table_decode[itr->second] = itr->first;
//}
//****************************************************************************************************************************

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


    connect_fun();
    main_layout->addLayout(vertical_layout);
    widget->setLayout(main_layout);
    tabWidget ->addTab(widget,"input file");
    setCentralWidget(tabWidget);

}
void MainWindow::connect_fun()
{
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
    connect(pushButton_4,SIGNAL(clicked()),this,SLOT(on_push_button_4_clicked()));
}
void MainWindow::on_push_button_clicked()
{
    QString filter = "All Files (*.*) ;; Text Files (*.txt) ;; XML Files (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"choose file","D:\\loay\\College\\3rd year\\2nd term\\datastructure and algorithm",filter);

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
void MainWindow::on_push_button_4_clicked()
{
     tabWidget ->addTab(new minify(),"minified file");
     tabWidget ->setCurrentIndex(tabWidget->count()-1);
}
MainWindow::~MainWindow()
{
    delete ui;
}
























