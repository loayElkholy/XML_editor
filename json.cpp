#include "json.h"
#include "ui_json.h"
#include "compress.h"
extern Tree *XML_Tree;
extern MainWindow *w;

json::json(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::json)
{
    ui->setupUi(this);

    ofstream out("json.txt");
    cout.rdbuf(out.rdbuf());
    XML_Tree->json();
    out.close();
    ifstream input("json.txt");
    string s2;
    QString json;
    if (input.is_open()) {
        while (getline(input, s2)) {
            json.append(QString::fromStdString(s2)+"\n");
        }
    }
    textBrowser->setText(json);

    MainWindow m;
    QVBoxLayout *vertical_widget =new QVBoxLayout();
    QHBoxLayout *horizontal_widget =new QHBoxLayout();

    QPixmap pixmap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-7-Save.ico");
    QIcon ButtonIcon(pixmap);
    pushButton->setText("Save File");
    pushButton->setIcon(ButtonIcon);


    QPixmap pixmap_2(":\\rec\\icons\\compress2.png");
    QIcon ButtonIcon_2(pixmap_2);
    pushButton_2->setText("Compress");
    pushButton_2->setIcon(ButtonIcon_2);

    horizontal_widget->addWidget(pushButton);
    horizontal_widget->addWidget(pushButton_2);

    vertical_widget->addLayout(horizontal_widget);
    vertical_widget->addWidget(textBrowser);

    connect_fun();

    setLayout(vertical_widget);
}
void json::connect_fun()
{
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_push_button_2_clicked()));

}

void json::on_push_button_2_clicked()
{
    w->tabWidget->addTab(new Compress(), "Compressed json File");
    w->tabWidget->setCurrentIndex(w->tabWidget->count() - 1);
}
void json::on_push_button_clicked()
{
    save_file(textBrowser);
}
json::~json()
{
    delete ui;
}
