#ifndef CALCULATIONSTATUS_H
#define CALCULATIONSTATUS_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QThread>
#include "mathcalculation.h"

class CalculationStatus : public QWidget {
    Q_OBJECT

public:
    CalculationStatus(int num, int xSize, int ySize, std::function<float (float)> func, QWidget *parent = nullptr);
    ~CalculationStatus();
    int n;

public slots:
    void start();
    void changeStatus(int percent);
    void endCalculate();

signals:
    void calculate();
    void end();

private:
    MathCalculation *mathCalculation;
    QThread mathThread;
    QLabel *label;
    QProgressBar *progressBar;

};

#endif // CALCULATIONSTATUS_H
