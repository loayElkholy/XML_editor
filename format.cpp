#include "format.h"
#include "ui_format.h"
#include "tree.h"
#include "mainwindow.h"
#include <QtWidgets>

extern Tree *XML_Tree;

Format::Format(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Format)
{
    ui->setupUi(this);
    QHBoxLayout *main_layout = new QHBoxLayout;
    QVBoxLayout *vertical_layout_f =new QVBoxLayout();
    QHBoxLayout *horizontal_layout_f = new QHBoxLayout();
    QPixmap pixmap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-7-Save.ico");
    QIcon ButtonIcon_s(pixmap);

    pushButton_save =new QPushButton();
    pushButton_save->setText("Save File");
    pushButton_save->setIcon(ButtonIcon_s);

    textEdit-> setReadOnly(true);
    textEdit->setFontPointSize(13);
    //textBrowser_format =new QTextBrowser();

    horizontal_layout_f ->addWidget(pushButton_save);
    vertical_layout_f->addLayout(horizontal_layout_f);
    vertical_layout_f->addWidget(textEdit);

    main_layout->addLayout(vertical_layout_f);
    setLayout(main_layout);

    string input;
    XML_Tree->format_public(input);
    QString text = QString::fromStdString(input);

    textEdit->setText(text);
    //textBrowser_format->setText(text);
    connect_save();
}

void Format::connect_save()
{
    connect(pushButton_save, SIGNAL(clicked()), this, SLOT(on_pushButton_save_clicked()));
}

void Format::on_pushButton_save_clicked() {
    save_file(textEdit);
}
Format::~Format()
{
    delete ui;
}
