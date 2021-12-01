#pragma once
#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QFile>

namespace Ui { class shortest_path; }

class shortest_path : public QDialog {
    Q_OBJECT

public:
    explicit shortest_path(QWidget *parent = nullptr);
    ~shortest_path();

private slots:
    void on_Task1Button_clicked();

    void on_Task2Button_clicked();

    void on_Task3Button_clicked();

private:
    Ui::shortest_path *ui;
};



class Graph_dij_floyd {
    int V;
    QVector<QVector<double>> graph;

    int minDistance(double* shortest_dist, bool* incl_path);
public:
    void input_graph(QVector<QVector<double>> g, int v);

    double* dijkstra(int src);
    QVector<QVector<double>> floydWarshall();

    void convert();
};


struct Edge {
    int u;  // Start vertex
    int v;  // End vertex
    int w;  // Weight of the vertex
};
class GraphBellman{
    QVector<Edge> edge;  // Array of edges
    int V;              // Total number of vertices
    int E;              // Total number of edges
public:
    void inputGraph(QVector<Edge> edg, int v, int e);
    QVector<int> BellmanFord(int u);     // u - source vertex

    void discount(QVector<QPair<int, int>> discounts);
};














#endif // SHORTEST_PATH_H
