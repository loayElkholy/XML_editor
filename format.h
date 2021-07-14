#ifndef FORMAT_H
#define FORMAT_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>

namespace Ui {
class Format;
}

class Format : public QWidget
{
    Q_OBJECT

public:
    explicit Format(QWidget *parent = nullptr);
    ~Format();

private:
    Ui::Format *ui;
    QPushButton *pushButton_save;
    QTextBrowser *textBrowser_format;
};

#endif // FORMAT_H
