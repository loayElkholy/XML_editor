#ifndef COMPRESS_H
#define COMPRESS_H

#include <QWidget>
#include "mainwindow.h"
#include "json.h"
#include <QTextEdit>
#include <QPushButton>

namespace Ui {
class Compress;
}

class Compress : public QWidget
{
    Q_OBJECT

public:
    explicit Compress(QWidget *parent = nullptr);
    ~Compress();
    void connect_tab_fn();
    vector<int> compress_file(map<string, int> &table, string s1, int &mul_char_code);
    void decode(map<int, string> table_decode, vector<int> encoded_code);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Compress *ui;
    QTextEdit *textEdit = new QTextEdit;
    QPushButton *pushButton = new QPushButton;
    QPushButton *pushButton_2 = new QPushButton;
};

#endif // COMPRESS_H
