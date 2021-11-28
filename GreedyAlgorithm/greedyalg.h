#pragma once
#ifndef GREEDYALG_H
#define GREEDYALG_H

#include <QDialog>
#include <QRegularExpression>

#include <fstream>
#include <sstream>

#include <map>
#include <list>
#include <vector>

namespace Ui { class greedyalg; }

class greedyalg : public QDialog {
    Q_OBJECT

public:
    explicit greedyalg(QWidget *parent = nullptr);
    ~greedyalg();

private slots:
    void on_StartButton_clicked();

private:
    Ui::greedyalg *ui;
};

class water {
    int barrel;

    int n;
    QVector<int> bucket;
public:
    water();
    ~water();

    void set_variables(int a, int b, QVector<int> array);

    void bubble_sort();
    QVector<int> solve();
};

#endif // GREEDYALG_H
