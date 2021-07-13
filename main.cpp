#include "mainwindow.h"

#include <QApplication>

extern Tree XML_Tree ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("XML Editor");
    return a.exec();
}
