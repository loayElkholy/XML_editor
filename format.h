#ifndef FORMAT_H
#define FORMAT_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class Format;
}

class Format : public QWidget
{
    Q_OBJECT

public:
    explicit Format(QWidget *parent = nullptr);
    void connect_save();
    ~Format();

private slots:
    void on_pushButton_save_clicked();

private:
    Ui::Format *ui;
    QPushButton *pushButton_save;
    QTextEdit *textEdit = new QTextEdit;
};

#endif // FORMAT_H
