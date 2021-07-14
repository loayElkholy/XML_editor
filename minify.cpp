#include "minify.h"
#include "ui_minify.h"
#include "mainwindow.h"
#include "tree.h"
#include <QtWidgets>
#include <QTextStream>
#include<QIcon>
#include<QPixmap>

extern Tree XML_Tree;

minify::minify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::minify)
{
    ui->setupUi(this);
    QHBoxLayout *main_layout =new QHBoxLayout();
    QVBoxLayout *vertical_layout =new QVBoxLayout();
    QHBoxLayout *horizontal_layout = new QHBoxLayout();
    QPixmap pixmap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-7-Save.ico");
    QIcon ButtonIcon(pixmap);
    QPixmap pixmap_2(":\\rec\\icons\\compress2.png");
    QIcon ButtonIcon_2(pixmap_2);
    pushButton_save->setText("Save file");
    pushButton_save ->setIcon(ButtonIcon);

    pushButton_compress->setText("Compress");
    pushButton_compress ->setIcon(ButtonIcon_2);

    horizontal_layout ->addWidget(pushButton_save);
    horizontal_layout ->addWidget(pushButton_compress);
    vertical_layout->addLayout(horizontal_layout);
    vertical_layout->addWidget(textBrowser_minify);

    main_layout->addLayout(vertical_layout);

    setLayout(main_layout);
    string s ="Lina";
    //XML_Tree.minify(s);
    QString text = QString::fromStdString(s);
    textBrowser_minify->setText(text);
}

minify::~minify()
{
    delete ui;
}
