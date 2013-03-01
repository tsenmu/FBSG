#include <QtGui/QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QDesktopWidget>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/splash_screen"));
    splash.show();
    a.processEvents();
    MainWindow w;

    QTimer::singleShot(100, &w, SLOT(show()));
    splash.finish(&w);
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    return a.exec();
}

