#pragma once
#ifndef DFS_BFS_H
#define DFS_BFS_H

#include <QDialog>
#include <QFile>
#include <QString>
#include <QRegularExpression>

#include <QList>
#include <QStack>
#include <QQueue>
#include <QVector>

namespace Ui { class dfs_bfs; }

class Graph {
    QList<int>* adj;     // Adjency list
    int V;              // Number of Verticles

    // BFS
    QVector<int> BFS_list;
    QVector<int> distance_BFS;

    // DFS
    QVector<int> DFS_list;
    QVector<int> time_entry_DFS;
    QVector<int> time_exit_DFS;
    QVector<int> parent;

    bool* visited;
public:
    Graph();
    void enter_graph(QList<int>* adj_list, int n);

    void BFS(int s);

    void DFS_stack(int s);
    void DFS_with_time(int s);

    friend class dfs_bfs;
};
class Task_3_Graph {
    QList<int>* adj;         // Adjency list
    QVector<QString> words;  // Array of words
    int V;                   // Number of Verticles

    // DFS
    QVector<QString> result_path;
    bool* visited;
public:
    void enter_graph(QList<int>* adj_list, QVector<QString> words_vec, int n);

    bool DFS_search_word(int s, QString str);

    friend class dfs_bfs;
};

class dfs_bfs : public QDialog {
    Q_OBJECT

public:
    explicit dfs_bfs(QWidget *parent = nullptr);
    ~dfs_bfs();

private slots:
    void on_Task1Button_clicked();
    void on_Task2Button_clicked();
    void on_Task3Button_clicked();

private:
    Ui::dfs_bfs *ui;
};

#endif // DFS_BFS_H
