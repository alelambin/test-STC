#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QPushButton>
#include <QVector>
#include <QVBoxLayout>
#include <random>
#include <ctime>
#include "calculationstatus.h"

#define AMOUNT 10

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

signals:
    void started();

private slots:
    void endCalulations();
    void startCalulations();

private:
    QVector<CalculationStatus *> calculations;
    QPushButton *startButton;
    int countStatusCompleted;

};

#endif // MAINWINDOW_H
