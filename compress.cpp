#include "compress.h"
#include "ui_compress.h"
#include <QtWidgets>
#include <QIcon>
#include <QPixmap>

extern Tree *XML_Tree;
extern MainWindow *w;
extern int flag;
extern QString json_file;

int mul_char_code = 256;
vector<int> code;
map<string, int> encoded_table;

Compress::Compress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compress)
{
    ui->setupUi(this);
    QHBoxLayout *main_tab_layout = new  QHBoxLayout;
    QVBoxLayout *vertical_tab_layout = new  QVBoxLayout;
    QHBoxLayout *horizontal_buttons_layout = new  QHBoxLayout;

    QPixmap pixMap(":\\rec\\icons\\Custom-Icon-Design-Pretty-Office-7-Save.ico");
    QIcon icon(pixMap);
    QPixmap pixMap_2(":\\rec\\icons\\decompress.png");
    QIcon icon_2(pixMap_2);
    QPixmap pixMap_3(":\\rec\\icons\\compress2.png");
    QIcon icon_3(pixMap_3);

    pushButton->setText("Save File");
    pushButton->setIcon(icon);
    pushButton_2->setText("Decompress File");
    pushButton_2->setIcon(icon_2);
    pushButton_3->setText("Compress File");
    pushButton_3->setIcon(icon_3);

    pushButton_3->hide();

    textEdit->setReadOnly(true);
    textEdit->setFontPointSize(13);
    horizontal_buttons_layout->addWidget(pushButton);
    horizontal_buttons_layout->addWidget(pushButton_2);
    horizontal_buttons_layout->addWidget(pushButton_3);
    vertical_tab_layout->addLayout(horizontal_buttons_layout);
    vertical_tab_layout->addWidget(textEdit);
    main_tab_layout->addLayout(vertical_tab_layout);
    setLayout(main_tab_layout);
    connect_tab_fn();

    string s1;
    if (flag == 1) {
        XML_Tree->minify(s1);
    }
    else if (flag == 2) {
        s1 = json_file.toStdString();
    }
    QString text_encoded;
    code = compress_file(s1, mul_char_code);
    for (int i = 0; i < code.size(); i++) {
        text_encoded += QString::number(code[i]);
    }
    textEdit->setText(text_encoded);
}

void Compress::connect_tab_fn() {
    connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
}

void Compress::on_pushButton_clicked() {
    save_file(textEdit);
}

void Compress::on_pushButton_2_clicked() {
    pushButton_2->hide();
    pushButton_3->show();
    map<int, string> table_decode;
    map<string, int>::iterator itr;
    for (itr = encoded_table.begin(); itr != encoded_table.end(); itr++) {
        table_decode[itr->second] = itr->first;
    }
    decode(table_decode, code);
}

void Compress::on_pushButton_3_clicked() {
    pushButton_3->hide();
    pushButton_2->show();
    vector<int> code;
    QString text_encoded;
    string s1;
    if (flag == 1) {
        XML_Tree->minify(s1);
    }
    else if (flag == 2) {
        s1 = json_file.toStdString();
    }
    code = compress_file(s1, mul_char_code);
    for (int i = 0; i < code.size(); i++) {
        text_encoded += QString::number(code[i]);
    }
    textEdit->setText(text_encoded);
}

vector<int> Compress::compress_file(string file_encode, int &mul_char_code) {
    for (int i = 0; i <= 255; i++) {
        string character = "";
        character += char(i);
        encoded_table[character] = i;
    }
    vector<int> encoded_code;
    string current = "", next = "";
    current += file_encode[0];
    for (int i = 0; i < file_encode.length(); i++) {
        if (i != file_encode.length() - 1) {
            next += file_encode[i + 1];
        }
        if (encoded_table.find(current + next) != encoded_table.end()) {
            current = current + next;
        }
        else {
            encoded_code.push_back(encoded_table[current]);
            encoded_table[current + next] = mul_char_code;
            mul_char_code++;
            current = next;
        }
        next = "";
    }
    encoded_code.push_back(encoded_table[current]);
    return encoded_code;
}

void Compress::decode(map<int, string> table_decode, vector<int> encoded_code) {
    string s;
    for (int i = 0; i < encoded_code.size(); i++) {
        s += table_decode[encoded_code[i]];
    }
    QString text_decoded = QString::fromStdString(s);
    textEdit->setText(text_decoded);
    encoded_table.clear();
    mul_char_code = 256;
}

Compress::~Compress()
{
    delete ui;
}
