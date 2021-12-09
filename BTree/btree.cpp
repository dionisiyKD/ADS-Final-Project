#include "btree.h"
#include "ui_btree.h"
#include "BTree/btree_add.h"

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new BTreeNodeData[2 * t - 1]();
    C = new BTreeNode* [2 * t];

    n = 0;
}
void BTreeNode::insertNonFull(BTreeNodeData k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i].ident_number > k.ident_number) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && keys[i].ident_number > k.ident_number)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1].ident_number < k.ident_number)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n = n + 1;
}
BTreeNodeData BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i].ident_number)
        i++;

    if (keys[i].ident_number == k)
        return keys[i];

    if (leaf == true) {
        BTreeNodeData garbage;
        return garbage;
    }

    return C[i]->search(k);
}

btree::btree(QWidget *parent) : QDialog(parent), ui(new Ui::btree) {
    ui->setupUi(this);

    path_in_b_tree = "btree_input.txt";
    root = NULL;
    set_t(3);
}
btree::~btree() {
    delete ui;
}

void btree::set_t(int _t) { t = _t; }
BTreeNodeData btree::search(int k) { return root->search(k); }

void btree::insert(BTreeNodeData k) {
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].ident_number < k.ident_number)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

void btree::addToTable(BTreeNodeData new_node){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    QTableWidgetItem *newItem;
    newItem = new QTableWidgetItem();
    newItem->setText(new_node.name);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.surname);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.patronymic);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(QString::number(new_node.ident_number));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, newItem);

    newItem = new QTableWidgetItem();
    newItem->setText(new_node.registr_date);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, newItem);

}

void btree::on_Input_From_File_clicked() {
    QFile file(path_in_b_tree);
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
        BTreeNodeData new_node;
        new_node.name = fin.readLine();
        new_node.surname = fin.readLine();
        new_node.patronymic = fin.readLine();
        new_node.ident_number = fin.readLine().toInt();
        new_node.registr_date = fin.readLine();
        insert(new_node);
        addToTable(new_node);
    }
    file.close();

}
void btree::on_Add_Button_clicked() {
    btree_add *window = new btree_add;
    window->set_human(new BTreeNodeData);
    connect(window, SIGNAL(humanChanged(BTreeNodeData*)), this, SLOT(onHumanChanged(BTreeNodeData*)));
    window->show();
}
void btree::on_SearchButton_clicked() {
    int search = ui->editSearch->text().toInt();
    BTreeNodeData search_key = root->search(search);

    QString result = "Имя: " + search_key.name
            + "\nФамилия: " + search_key.surname
            + "\nОтчество: " + search_key.patronymic;
    QMessageBox::about(this, "ФИО владельца этой машины", result);
}

void btree::onHumanChanged(BTreeNodeData* new_human){
    BTreeNodeData tmp;
    tmp.name = new_human->name;
    tmp.surname = new_human->surname;
    tmp.patronymic = new_human->patronymic;
    tmp.ident_number = new_human->ident_number;
    tmp.registr_date = new_human->registr_date;
    insert(tmp);
    addToTable(tmp);
}



