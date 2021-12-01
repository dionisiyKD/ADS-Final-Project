#include "hashtable_search.h"
#include "ui_hashtable_search.h"

hashtable_search::hashtable_search(QWidget *parent) : QDialog(parent), ui(new Ui::hashtable_search) {
    ui->setupUi(this);
}
hashtable_search::~hashtable_search() {
    delete ui;
}

void hashtable_search::set_human(HT_item *hum) {
    human = hum;
    ui->editName->setText(human->get_name());
    ui->editSurname->setText(human->get_surname());
    ui->editPatrnymic->setText(human->get_patronymic());
}

void hashtable_search::on_buttonBox_accepted() {
    human->set_name(ui->editName->text());
    human->set_surname(ui->editSurname->text());
    human->set_patronymic(ui->editPatrnymic->text());
    emit humanSearching(human);
    close();
}
void hashtable_search::on_buttonBox_rejected() {
    close();
}
