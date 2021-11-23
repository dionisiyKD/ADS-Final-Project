#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HeapSort/heapsort.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::on_HeapSortButton_clicked()
{
    HeapSort *window = new HeapSort;
    window->show();
}

