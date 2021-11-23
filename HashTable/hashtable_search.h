#pragma once
#ifndef HASHTABLE_SEARCH_H
#define HASHTABLE_SEARCH_H

#include <QDialog>

#include "HashTable/hashtable.h"

namespace Ui { class hashtable_search; }

class hashtable_search : public QDialog {
    Q_OBJECT

public:
    explicit hashtable_search(QWidget *parent = nullptr);
    ~hashtable_search();

    void set_human(HT_item* hum);

signals:
    void humanSearching(HT_item* new_human);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::hashtable_search *ui;

    HT_item *human;
};

#endif // HASHTABLE_SEARCH_H
