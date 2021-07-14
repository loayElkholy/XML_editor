#include "json.h"
#include "ui_json.h"

extern Tree XML_Tree;

json::json(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::json)
{
    ui->setupUi(this);

    ofstream out("json.txt");
    cout.rdbuf(out.rdbuf());
    cout<<"loay";
    XML_Tree.json();

    ifstream input("json.txt");
    string s2;
    QString json;
    if (input.is_open()) {
        while (getline(input, s2)) {
            json += QString::fromStdString(s2);
            json += "\n";
        }
    }
    textBrowser->setText(json);

    MainWindow m;
    QVBoxLayout *vertical_widget =new QVBoxLayout();
    QHBoxLayout *horizontal_widget =new QHBoxLayout();

    QPixmap pixmap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-7-Save.ico");
    QIcon ButtonIcon(pixmap);
    pushButton->setText("save");
    pushButton->setIcon(ButtonIcon);


    QPixmap pixmap_2(":\\rec\\icons\\compress.png");
    QIcon ButtonIcon_2(pixmap_2);
    pushButton_2->setText("Compress");
    pushButton_2->setIcon(ButtonIcon_2);

    horizontal_widget->addWidget(pushButton);
    horizontal_widget->addWidget(pushButton_2);

    vertical_widget->addLayout(horizontal_widget);
    vertical_widget->addWidget(textBrowser);

    setLayout(vertical_widget);
}
void json::connect_fun()
{
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
}
void json::connect_fun_2()
{
    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_push_button_2_clicked()));
}
void json::on_push_button_2_clicked()
{

}
void json::on_push_button_clicked()
{

}
json::~json()
{
    delete ui;
}
