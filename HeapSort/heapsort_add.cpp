#include "heapsort_add.h"
#include "ui_heapsort_add.h"
#include <string>

heapsort_add::heapsort_add(QWidget *parent) : QDialog(parent), ui(new Ui::heapsort_add) {
    ui->setupUi(this);
}
heapsort_add::~heapsort_add() {
    delete ui;
}

void heapsort_add::set_book(MyList::node* book){
    new_book = book;
    ui->editAuthor->setText(new_book->author);
    ui->editName->setText(new_book->name);
    ui->editGenre->setText(new_book->genre);
    ui->editPublishingHouse->setText(new_book->publishing_house);
    ui->editPublicatioYear->setText(new_book->publication_year);
    ui->editNumberOfPages->setText(QString::number(new_book->number_of_pages));
    ui->editNumberOfCopies->setText(QString::number(new_book->number_of_copies));
    ui->editNumberOfCopiesForReaders->setText(QString::number(new_book->number_of_copies_for_readers));
}
void heapsort_add::on_buttonBox_accepted() {
    new_book->author = ui->editAuthor->text();
    new_book->name = ui->editName->text();
    new_book->genre = ui->editGenre->text();
    new_book->publishing_house = ui->editPublishingHouse->text();
    new_book->publication_year = ui->editPublicatioYear->text();
    new_book->number_of_pages = ui->editNumberOfPages->text().toInt();
    new_book->number_of_copies = ui->editNumberOfCopies->text().toInt();
    new_book->number_of_copies_for_readers = ui->editNumberOfCopiesForReaders->text().toInt();
    emit bookChanged(new_book);
    close();
}
void heapsort_add::on_buttonBox_rejected() {
    close();
}
