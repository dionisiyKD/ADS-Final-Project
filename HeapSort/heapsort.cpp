#include "heapsort.h"
#include "ui_heapsort.h"
#include "list.h"
#include "heapsort_add.h"
QTextStream & operator>> (QTextStream&fin, MyList::node* elem) {
    QString garbage = fin.readLine();
    elem->author = fin.readLine();
    elem->name = fin.readLine();
    elem->genre = fin.readLine();
    elem->publishing_house = fin.readLine();
    elem->publication_year = fin.readLine();
    fin >> elem->number_of_pages;
    fin >> elem->number_of_copies;
    fin >> elem->number_of_copies_for_readers;
    elem->data = elem->number_of_copies - elem->number_of_copies_for_readers;
    return fin;
}

HeapSort::HeapSort(QWidget *parent) : QDialog(parent), ui(new Ui::HeapSort) {
    ui->setupUi(this);
    input_file_name = "heapsort_input.txt";
}
HeapSort::~HeapSort() {
    delete ui;
}

void HeapSort::heapify(MyList::list& arr, int n, int i) {
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr.get_data(l+1) > arr.get_data(largest + 1))
        largest = l;

    if (r < n && arr.get_data(r + 1) > arr.get_data(largest + 1))
        largest = r;

    if (largest != i)
    {
        arr.swap(i, largest);
        heapify(arr, n, largest);
    }
}
void HeapSort::heapSort(MyList::list& arr) {
    int n = arr.get_count();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        arr.swap(0, i);
        heapify(arr, i, 0);
    }
}

void HeapSort::populateTable(){
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    for(int i = 1; i <= arr.get_count(); i++)
        addToTable(arr.get_item(i));
}
void HeapSort::addToTable(MyList::node* book){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;
    newItem = new QTableWidgetItem();
    newItem->setText(book->author);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(book->name);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(book->genre);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(book->publishing_house);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(book->publication_year);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(book->number_of_pages));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(book->number_of_copies));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 6, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(book->number_of_copies_for_readers));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 7, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(book->data));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 8, newItem);
}

void HeapSort::on_Add_to_tail_Button_clicked() {
    heapsort_add *window = new heapsort_add;
    window->set_book(new MyList::node);
    connect(window, SIGNAL(bookChanged(MyList::node*)), this, SLOT(onBookChanged(MyList::node*)));
    window->show();
}
void HeapSort::on_Input_From_File_clicked() {
    QFile file(input_file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    while(!fin.atEnd()) {
        MyList::node* new_node = new MyList::node;
        fin >> new_node;
        arr.add_tail(new_node);
        addToTable(new_node);
    }
    file.close();
}
void HeapSort::on_SortButton_clicked() {
    heapSort(arr);
    populateTable();
}
void HeapSort::on_DeleteButton_clicked() {
    if(arr.get_count() == 1)
        return;
    int index = ui->tableWidget->currentRow();
    arr.remove(index + 1);
    ui->tableWidget->removeRow(index);
}
void HeapSort::on_ClearButton_clicked() {
    arr.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
void HeapSort::on_RefreshButton_clicked() {
    populateTable();
}
void HeapSort::on_SolveButton_clicked() {
    heapSort(arr);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    for(int i = 1; i <= arr.get_count() / 2; i++)
        addToTable(arr.get_item(i));
}

void HeapSort::onBookChanged(MyList::node* book){
    arr.add_tail(book);
    addToTable(book);
}
