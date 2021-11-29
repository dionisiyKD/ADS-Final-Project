#pragma once
#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <QDialog>
#include <QRegularExpression>
#include <QFile>
#include <QString>
#include <vector>
#include <QMap>
#include <cmath>
#include <QtAlgorithms>

namespace Ui { class dynamicprogramming; }

class sequence {
    int n;
    QVector<int> arr;
    QVector<QVector<int>> subsequences;
    QVector<int> result;
public:
    sequence(int a, QVector<int> b) : n(a), arr(b){}
    void split_subsequences();
    void find_max_subsequence();
    QVector<int> get_max_subsequence();
    void solve();
};

class Town {
    QMap<QString, int> results;

    int n;
    QVector<QVector<QString>> matrix;
public:
    Town(QVector<QVector<QString>> matr, int a): n(a), matrix(matr){}
    QMap<QString, int> solve();
};


class dynamicprogramming : public QDialog {
    Q_OBJECT

public:
    explicit dynamicprogramming(QWidget *parent = nullptr);
    ~dynamicprogramming();

private slots:
    void on_FirstTaskButton_clicked();
    void on_SecondTaskButton_clicked();
    void on_InputFromFileMatrixButton_clicked();

private:
    Ui::dynamicprogramming *ui;

    QVector<QVector<QString>> matr;
};

#endif // DYNAMICPROGRAMMING_H
