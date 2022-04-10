#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Thread App");
    window.resize(800, 600);
    window.setWindowIcon(QIcon(":img/icon.png"));
    window.show();

    return app.exec();
}
