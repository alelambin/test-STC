#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> rand(0, 300);

    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);
    for (int i = 0; i < AMOUNT; i++) {
        CalculationStatus *calculationStatus = new CalculationStatus(i, rand(gen), rand(gen),
            [] (float x) {return x;}, this);
        layout->addWidget(calculationStatus);
        calculations.push_back(calculationStatus);
    }
    startButton = new QPushButton("Старт", this);
    layout->addWidget(startButton);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    countStatusCompleted = 0;
    connect(startButton, SIGNAL(released()), this, SLOT(startCalulations()));
    for (auto widget : calculations) {
        connect(this, SIGNAL(started()), widget, SLOT(start()));
        connect(widget, SIGNAL(end()), this, SLOT(endCalulations()));
    }
}

void MainWindow::endCalulations() {
    QCoreApplication::processEvents();

    countStatusCompleted++;
    if (countStatusCompleted == AMOUNT) {
        startButton->setDisabled(false);
        startButton->setText("Рестарт");
        countStatusCompleted = 0;
    }
}

void MainWindow::startCalulations() {
    startButton->setDisabled(true);
    emit started();
}
