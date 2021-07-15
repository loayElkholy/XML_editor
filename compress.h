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
    vector<int> compress_file(string s1);
    void decode(vector<int> encoded_code);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Compress *ui;
    QTextEdit *textEdit = new QTextEdit;
    QPushButton *pushButton = new QPushButton;
    QPushButton *pushButton_2 = new QPushButton;
    QPushButton *pushButton_3 = new QPushButton;
};

#endif // COMPRESS_H
