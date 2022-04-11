#ifndef MATHCALCULATION_H
#define MATHCALCULATION_H

#include <QObject>
#include <QVector>
#include <functional>
#include <random>
#include <ctime>

/*!
 * \class MathCalculation
 * The class that performs mathematical operations on a matrix in a thread
 */
class MathCalculation : public QObject {
    Q_OBJECT

public:
    MathCalculation(int xSize, int ySize, std::function<float (float)> func);
    ~MathCalculation() = default;

public slots:
    void start();

signals:
    void result(int percent);
    void end();

private:
    QVector<QVector<float>> matrix;
    std::function<float (float)> func;

};

#endif // MATHCALCULATION_H
