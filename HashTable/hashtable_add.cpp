#include "hashtable_add.h"
#include "ui_hashtable_add.h"

hashtable_add::hashtable_add(QWidget *parent) : QDialog(parent), ui(new Ui::hashtable_add) {
    ui->setupUi(this);
}
hashtable_add::~hashtable_add() {
    delete ui;
}

void hashtable_add::set_human(HT_item *human) {
    new_human = human;
    ui->editName->setText(new_human->get_name());
    ui->editSurname->setText(new_human->get_surname());
    ui->editPatrnymic->setText(new_human->get_patronymic());
    ui->editRole->setText(new_human->get_role());
}

void hashtable_add::on_buttonBox_accepted() {
    new_human->set_name(ui->editName->text());
    new_human->set_surname(ui->editSurname->text());
    new_human->set_patronymic(ui->editPatrnymic->text());
    new_human->set_role(ui->editRole->text());
    emit humanChanged(new_human);
    close();
}
void hashtable_add::on_buttonBox_rejected() {
    close();
}

