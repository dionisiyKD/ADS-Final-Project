#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "HeapSort/heapsort.h"
#include "HashTable/hashtable.h"
#include "BTree/btree.h"
#include "GreedyAlgorithm/greedyalg.h"
#include "Huffman/huffman.h"
#include "DynamicProgramming/dynamicprogramming.h"
#include "DFS_BFS/dfs_bfs.h"

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
void mainwindow::on_HuffmanButton_clicked() {
    huffman *HuffmanWindow = new huffman;
    HuffmanWindow->show();
}
void mainwindow::on_DPButton_clicked() {
    dynamicprogramming *DPWindow = new dynamicprogramming;
    DPWindow->show();
}
void mainwindow::on_DFS_BFSButton_clicked() {
    dfs_bfs *DFS_BFSWindow = new dfs_bfs;
    DFS_BFSWindow->show();
}

