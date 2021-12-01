#include "hashtable.h"
#include "ui_hashtable.h"
#include "HashTable/hashtable_add.h"
#include "HashTable/hashtable_search.h"

int HT_item::HashFunc(int TABLE_SIZE) {
    double A = 0.618033;
    int h = TABLE_SIZE * fmod(key * A, 1);
    return h;
}
int HT_item::HashKey() {
    return (name[0].toLatin1() + surname[0].toLatin1() + patronymic[0].toLatin1());
}

hashtable::hashtable(QWidget *parent) : QDialog(parent), ui(new Ui::hashtable) {
    ui->setupUi(this);

    path_in_hash = "hashtable_input.txt";
    TABLE_SIZE = 3;
    table = new HT_item * [TABLE_SIZE]();
}
hashtable::~hashtable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HT_item* item = table[i];
        while (item != NULL) {
            HT_item* prev = item;
            item = item->get_next();
            delete prev;
        }
        table[i] = NULL;
    }
    delete[] table;
    delete ui;
}

void hashtable::put_item(HT_item value) {
    int key = value.HashFunc(TABLE_SIZE);
    HT_item* prev = NULL;
    HT_item* entry = table[key];

    while (entry != NULL) {
        prev = entry;
        entry = entry->get_next();
    }

    entry = new HT_item;
    *entry = value;

    if (prev == NULL)
        table[key] = entry;
    else
        prev->set_next(entry);
}
void hashtable::remove(HT_item value) {
    int key = value.HashFunc(TABLE_SIZE);
    HT_item* prev = NULL;
    HT_item* entry = table[key];

    while (entry != NULL && !(*entry == value)) {
        prev = entry;
        entry = entry->get_next();
    }

    if (entry == NULL) {
        qCritical() << "Didnt find...";
        return;
    }

    if (prev == NULL)
        table[key] = entry->get_next();
    else
        prev->set_next(entry->get_next());
    delete entry;
}
QString hashtable::search_role(HT_item value) {
    int key = value.HashFunc(TABLE_SIZE);
    //HT_item* prev = NULL;
    HT_item* entry = table[key];

    while (entry != NULL && !(*entry == value)) {
        //prev = entry;
        entry = entry->get_next();
    }

    if (entry == NULL)
        return "0";
    return entry->get_role();
}

void hashtable::addToTable(HT_item new_node){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;
    newItem = new QTableWidgetItem();
    newItem->setText(new_node.get_name());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.get_surname());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.get_patronymic());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.get_role());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, newItem);
}
void hashtable::populateTable(){
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int key = 0;
    HT_item* entry = table[key];
    do {
        while (entry != NULL) {


            HT_item tmp;
            tmp.set_name(entry->get_name());
            tmp.set_surname(entry->get_surname());
            tmp.set_patronymic(entry->get_patronymic());
            tmp.set_role(entry->get_role());

            addToTable(tmp);

            entry = entry->get_next();
        }
        key++;
        entry = table[key];
    } while (key < TABLE_SIZE);


}

void hashtable::on_Input_From_File_clicked() {
    QFile file(path_in_hash);
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
        HT_item new_node;
        new_node.set_name(fin.readLine());
        new_node.set_surname(fin.readLine());
        new_node.set_patronymic(fin.readLine());
        new_node.set_role(fin.readLine());
        new_node.set_key(new_node.HashKey());
        new_node.set_next(NULL);

        put_item(new_node);
        addToTable(new_node);
    }

    file.close();
}
void hashtable::on_RefreshButton_clicked() {
    populateTable();
}
void hashtable::on_DeleteButton_clicked() {
    int index = ui->tableWidget->currentRow();

    HT_item tmp;
    tmp.set_name(ui->tableWidget->item(index, 0)->text());
    tmp.set_surname(ui->tableWidget->item(index, 1)->text());
    tmp.set_patronymic(ui->tableWidget->item(index, 2)->text());
    tmp.set_role(ui->tableWidget->item(index, 3)->text());
    tmp.set_key(tmp.HashKey());
    remove(tmp);

    ui->tableWidget->removeRow(index);
}
void hashtable::on_ClearButton_clicked() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HT_item* item = table[i];
        while (item != NULL) {
            HT_item* prev = item;
            item = item->get_next();
            delete prev;
        }
        table[i] = NULL;
    }
    delete[] table;

    table = new HT_item * [TABLE_SIZE]();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
void hashtable::on_Add_Button_clicked() {
    hashtable_add *window = new hashtable_add;
    window->set_human(new HT_item);
    connect(window, SIGNAL(humanChanged(HT_item*)), this, SLOT(onHumanChanged(HT_item*)));
    window->show();
}
void hashtable::on_SearchButton_clicked() {
    hashtable_search *window = new hashtable_search;
    window->set_human(new HT_item);
    connect(window, SIGNAL(humanSearching(HT_item*)), this, SLOT(onHumanSearching(HT_item*)));
    window->show();
}

void hashtable::onHumanChanged(HT_item* new_human){
    HT_item tmp;
    tmp.set_name(new_human->get_name());
    tmp.set_surname(new_human->get_surname());
    tmp.set_patronymic(new_human->get_patronymic());
    tmp.set_role(new_human->get_role());
    tmp.set_key(tmp.HashKey());
    tmp.set_next(NULL);
    put_item(tmp);
    addToTable(tmp);
}
void hashtable::onHumanSearching(HT_item* new_human){
    HT_item tmp;
    tmp.set_name(new_human->get_name());
    tmp.set_surname(new_human->get_surname());
    tmp.set_patronymic(new_human->get_patronymic());
    tmp.set_key(tmp.HashKey());
    QString result = search_role(tmp);
    if(result == "0"){
        QMessageBox::about(this, "Error", "Didn't find such an employee");
    }
    else{
        QMessageBox::about(this, "Yay", "The role of this employee: " + result);
    }
}




















