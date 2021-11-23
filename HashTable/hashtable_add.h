#pragma once
#ifndef HASHTABLE_ADD_H
#define HASHTABLE_ADD_H

#include <QDialog>

#include "HashTable/hashtable.h"

namespace Ui { class hashtable_add; }

class hashtable_add : public QDialog {
    Q_OBJECT

public:
    explicit hashtable_add(QWidget *parent = nullptr);
    ~hashtable_add();

    void set_human(HT_item* human);

signals:
    void humanChanged(HT_item* new_human);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::hashtable_add *ui;

    HT_item *new_human;
};

#endif // HASHTABLE_ADD_H
