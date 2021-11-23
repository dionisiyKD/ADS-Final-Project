#pragma once
#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <QDialog>

#include <QFileDialog>
#include <QTextStream>

#include "list.h"

namespace Ui {
class HeapSort;
}

class HeapSort : public QDialog {
    Q_OBJECT
public:
    explicit HeapSort(QWidget *parent = nullptr);
    ~HeapSort();

private slots:
    void on_Add_to_tail_Button_clicked();
    void on_Input_From_File_clicked();
    void on_SortButton_clicked();
    void on_ClearButton_clicked();


    void onBookChanged(MyList::node* book);

    void on_DeleteButton_clicked();

    void on_SolveButton_clicked();

    void on_RefreshButton_clicked();

private:
    Ui::HeapSort *ui;

    MyList::list arr;
    QString input_file_name;


    void heapify(MyList::list& arr, int n, int i);
    void heapSort(MyList::list& arr);
    void populateTable();
    void addToTable(MyList::node* book);
};

#endif // HEAPSORT_H
