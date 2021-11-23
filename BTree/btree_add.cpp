#include "btree_add.h"
#include "ui_btree_add.h"

btree_add::btree_add(QWidget *parent) : QDialog(parent), ui(new Ui::btree_add) {
    ui->setupUi(this);
}
btree_add::~btree_add() {
    delete ui;
}

void btree_add::set_human(BTreeNodeData *human) {
    new_human = human;
    ui->editName->setText(new_human->name);
    ui->editSurname->setText(new_human->surname);
    ui->editPatrnymic->setText(new_human->patronymic);
    ui->editIdentNumb->setText(QString::number(new_human->ident_number));
    ui->editRegistrDate->setText(new_human->registr_date);
}

void btree_add::on_buttonBox_accepted() {
    new_human->name = ui->editName->text();
    new_human->surname = ui->editSurname->text();
    new_human->patronymic = ui->editPatrnymic->text();
    new_human->ident_number = ui->editIdentNumb->text().toInt();
    new_human->registr_date = ui->editRegistrDate->text();
    emit humanChanged(new_human);
    close();
}
void btree_add::on_buttonBox_rejected() {
    close();
}

