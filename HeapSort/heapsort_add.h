#pragma once
#ifndef HEAPSORT_ADD_H
#define HEAPSORT_ADD_H
#include "list.h"
#include <QDialog>

namespace Ui { class heapsort_add; }

class heapsort_add : public QDialog {
    Q_OBJECT

public:
    explicit heapsort_add(QWidget *parent = nullptr);
    ~heapsort_add();

    void set_book(MyList::node* book);

signals:
    void bookChanged(MyList::node* new_book);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::heapsort_add *ui;

    MyList::node* new_book;
};

#endif // HEAPSORT_ADD_H
