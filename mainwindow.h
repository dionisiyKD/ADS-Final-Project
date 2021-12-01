#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void on_HeapSortButton_clicked();
    void on_HashTableButton_clicked();
    void on_BTreeButton_clicked();
    void on_GreedyAlgButton_clicked();
    void on_HuffmanButton_clicked();
    void on_DPButton_clicked();
    void on_DFS_BFSButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::mainwindow *ui;
};
#endif // MAINWINDOW_H
