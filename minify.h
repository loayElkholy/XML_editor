#ifndef MINIFY_H
#define MINIFY_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include<QTabWidget>

namespace Ui {
class minify;
}

class minify : public QWidget
{
    Q_OBJECT

public:
    explicit minify(QWidget *parent = nullptr);
    ~minify();

private:
    Ui::minify *ui;
     QPushButton *pushButton_save = new QPushButton;
     QPushButton *pushButton_compress = new QPushButton;
     QTextBrowser *textBrowser_minify = new QTextBrowser;
     QTabWidget *tab_minify = new QTabWidget;
};

#endif // MINIFY_H
