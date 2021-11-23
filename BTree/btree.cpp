#include "btree.h"
#include "ui_btree.h"

btree::btree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::btree)
{
    ui->setupUi(this);
}

btree::~btree()
{
    delete ui;
}
