#include "compress.h"
#include "ui_compress.h"
#include <QtWidgets>
#include <QIcon>
#include <QPixmap>

int mul_char_code = 256;
vector<int> code;
//vector<int> total_code;
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

    pushButton->setText("Save File");
    pushButton->setIcon(icon);
    pushButton_2->setText("Decompress File");
    pushButton_2->setIcon(icon_2);

    horizontal_buttons_layout->addWidget(pushButton);
    horizontal_buttons_layout->addWidget(pushButton_2);
    vertical_tab_layout->addLayout(horizontal_buttons_layout);
    vertical_tab_layout->addWidget(textBrowser);
    main_tab_layout->addLayout(vertical_tab_layout);
    setLayout(main_tab_layout);

    connect_tab_fn();


    for (int i = 0; i <= 255; i++) {
        string character = "";
        character += char(i);
        encoded_table[character] = i;
    }
    string s1;
    QString text_encoded;
    code = compress_file(encoded_table, s1, mul_char_code);
    for (int i = 0; i < code.size(); i++) {
        text_encoded += QString::number(code[i]);
    }
    textBrowser->setText(text_encoded);
}

void Compress::connect_tab_fn() {
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
}

void Compress::on_pushButton_2_clicked() {
    map<int, string> table_decode;
    map<string, int>::iterator itr;
    for (itr = encoded_table.begin(); itr != encoded_table.end(); itr++) {
        table_decode[itr->second] = itr->first;
    }
    decode(table_decode, code);
}

vector<int> Compress::compress_file(map<string, int> &table, string file_encode, int &mul_char_code) {
    vector<int> encoded_code;
    string current = "", next = "";
    current += file_encode[0];
    for (int i = 0; i < file_encode.length(); i++) {
        if (i != file_encode.length() - 1) {
            next += file_encode[i + 1];
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

void Compress::decode(map<int, string> table_decode, vector<int> encoded_code) {
    string s;
    for (int i = 0; i < encoded_code.size(); i++) {
        s += table_decode[encoded_code[i]];
    }
    QString text_decoded = QString::fromStdString(s);
    textBrowser->setText(text_decoded);
}

Compress::~Compress()
{
    delete ui;
}
