#include "calculationstatus.h"

CalculationStatus::CalculationStatus(int num, int xSize, int ySize, std::function<float (float)> func, QWidget *parent) :
    QWidget(parent), mathCalculation(new MathCalculation(xSize, ySize, func)) {
    label = new QLabel(QString::number(num) + ". ", this);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, xSize * ySize);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(progressBar);
    setLayout(layout);

    mathCalculation->moveToThread(&mathThread);
    connect(&mathThread, &QThread::finished, mathCalculation, &QObject::deleteLater);
    connect(this, SIGNAL(calculate()), mathCalculation, SLOT(start()));
    connect(mathCalculation, SIGNAL(result(int)), this, SLOT(changeStatus(int)));
    connect(mathCalculation, SIGNAL(end()), this, SLOT(endCalculate()));
    mathThread.start();
}

CalculationStatus::~CalculationStatus() {
    mathThread.quit();
    mathThread.wait();
    delete mathCalculation;
}

void CalculationStatus::start() {
    emit calculate();
}


void CalculationStatus::changeStatus(int percent) {
    progressBar->setValue(percent);
}

void CalculationStatus::endCalculate() {
    emit end();
}
