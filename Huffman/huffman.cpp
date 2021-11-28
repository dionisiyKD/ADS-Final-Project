#include "huffman.h"
#include "ui_huffman.h"

huffman::huffman(QWidget *parent) : QDialog(parent), ui(new Ui::huffman) {
    ui->setupUi(this);
}
huffman::~huffman() {
    delete ui;
}
