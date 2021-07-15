#include "compress.h"
#include "ui_compress.h"
#include <QtWidgets>
#include <QIcon>
#include <QPixmap>

extern Tree *XML_Tree;
extern MainWindow *w;
extern int flag;
extern QString json_file;


vector<int> code;


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
    textEdit->setFontPointSize(13);

    horizontal_buttons_layout->addWidget(pushButton);
    horizontal_buttons_layout->addWidget(pushButton_2);
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
    code.clear();
    code = compress_file(s1);
    for (int i = 0; i < code.size(); i++) {
        text_encoded += QString::number(code[i]);
        text_encoded += " ";
    }
    textEdit->setText(text_encoded);
}

void Compress::connect_tab_fn() {
    connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
}

void Compress::on_pushButton_clicked() {
    save_file(textEdit);
}

void Compress::on_pushButton_2_clicked() {
//    map<int, string> table_decode;
//    map<string, int>::iterator itr;
//    for (itr = encoded_table.begin(); itr != encoded_table.end(); itr++) {
//        table_decode[itr->second] = itr->first;
//    }
    decode(code);
    code.clear();
}

vector<int> Compress::compress_file(string file_encode) {
    map<string, int> encoded_table;
    for (int i = 0; i <= 255; i++) {
        string character = "";
        character += char(i);
        encoded_table[character] = i;
    }
    int mul_char_code = 256;
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

void Compress::decode(vector<int> encoded_code) {
    string s;
//    for (int i = 0; i < encoded_code.size(); i++) {
//        s += table_decode[encoded_code[i]];
//    }
    map<int, string> decode_table;
    for (int i = 0; i <= 255; i++) {
        string character = "";
        character += char(i);
        decode_table[i] = character;
    }
    int pre = encoded_code[0];
    int next;
    string str = decode_table[pre];
    string current = "";
    current += str[0];
    s += str;
    //textEdit->append(QString::fromStdString(str));
    int mul_char_count = 256;
    for (int i = 0; i < encoded_code.size() - 1; i++) {
        next = encoded_code[i + 1];
        if (decode_table.find(next) == decode_table.end()) {
            str = decode_table[pre];
            str = str + current;
        }
        else {
            str = decode_table[next];
        }
        s += str;
        //textEdit->append(QString::fromStdString(str));
        current = "";
        current += str[0];
        decode_table[mul_char_count] = decode_table[pre] + current;
        mul_char_count++;
        pre = next;
    }
    QString text_decoded = QString::fromStdString(s);
    textEdit->setText(text_decoded);
}

Compress::~Compress()
{
    delete ui;
}
