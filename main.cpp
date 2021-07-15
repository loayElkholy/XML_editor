#include "mainwindow.h"

#include <QApplication>

MainWindow *w;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow();
    a.setStyle("Fusion");
    w->show();
    w->setWindowTitle("XML Editor");
    return a.exec();
}
