#include "calculationstatus.h"

/*!
 * CalculationStatus class constructor
 * \param num widget's number (0 - 9)
 * \param xSize, ySize size of the matrix on which the calculations will be performed
 * \param func performed function
 * \param parent pointer on parent's widget
 */
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

/*!
 * CalculationStatus class destructor
 */
CalculationStatus::~CalculationStatus() {
    mathThread.quit();
    mathThread.wait();
    delete mathCalculation;
}

/*!
 * Slot that generates the calculate() signal
 */
void CalculationStatus::start() {
    emit calculate();
}

/*!
 * Slot that changes the value of the progress bar
 */
void CalculationStatus::changeStatus(int percent) {
    progressBar->setValue(percent);
}

/*!
 * Slot that generates the end() signal
 */
void CalculationStatus::endCalculate() {
    emit end();
}
