#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "HeapSort/heapsort.h"
#include "HashTable/hashtable.h"
#include "BTree/btree.h"
#include "GreedyAlgorithm/greedyalg.h"
#include "Huffman/huffman.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
}
mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::on_HeapSortButton_clicked() {
    HeapSort *HeapSortWindow = new HeapSort;
    HeapSortWindow->show();
}
void mainwindow::on_HashTableButton_clicked() {
    hashtable *HashTableWindow = new hashtable;
    HashTableWindow->show();
}
void mainwindow::on_BTreeButton_clicked() {
    btree *BTreeWindow = new btree;
    BTreeWindow->show();
}
void mainwindow::on_GreedyAlgButton_clicked() {
    greedyalg *GreedyAlgWindow = new greedyalg;
    GreedyAlgWindow->show();
}
void mainwindow::on_pushButton_clicked() {
    huffman *HuffmanWindow = new huffman;
    HuffmanWindow->show();
}

