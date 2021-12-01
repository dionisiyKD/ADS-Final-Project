#pragma once
#ifndef LIST_H
#define LIST_H

#include <QString>
#include <QTextStream>
#include <iostream>

namespace MyList{

struct node{
    QString author;
    QString name;
    QString genre;
    QString publishing_house;
    QString publication_year;
    int number_of_pages;
    int number_of_copies;
    int number_of_copies_for_readers;
    int data;  //number_of_copies_in_library

    node* next;
    node* prev;
    node(){
        number_of_pages = 0;
        number_of_copies = 0;
        number_of_copies_for_readers = 0;
    }
};
class list {
    node* head;
    node* tail;
    int count;
public:
    list();
    ~list();

    int get_data(int index);
    int get_count();
    node* get_item(int index);

    void add_head(node* tmp);
    void add_tail(node* tmp);
    void insert_after(int index, node* new_node);

    void remove(int index);
    void clear();

    void swap(int first, int second);
    int search(int A);

    void print_from_head();
    void print_from_tail();

    void solve();
};

}
#endif // LIST_H
