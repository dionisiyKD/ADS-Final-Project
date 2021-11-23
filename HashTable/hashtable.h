#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>


namespace Ui { class hashtable; }

class HT_item {
    int key;
    QString name;
    QString surname;
    QString patronymic;
    QString role;
    HT_item* next;
public:
    int get_key() { return key; };
    void set_key(int k) { key = k; }

    QString get_name() { return name; }
    void set_name(QString str) { name = str; }

    QString get_surname() { return surname; }
    void set_surname(QString str) { surname = str; }

    QString get_patronymic() { return patronymic; }
    void set_patronymic(QString str) { patronymic = str; }

    QString get_role() { return role; }
    void set_role(QString str) { role = str; }

    HT_item* get_next() { return next; }
    void set_next(HT_item* n) { next = n; }

    void input_item();
    void output_item();

    int HashFunc(int TABLE_SIZE);
    int HashKey();

    bool operator==(HT_item& b) {
        if (key == b.get_key())
            return true;
        else{
            return false;
        }
    }
};

class hashtable : public QDialog {
    Q_OBJECT

public:
    explicit hashtable(QWidget *parent = nullptr);
    ~hashtable();

    void put_item(HT_item value);
    void remove(HT_item value);
    QString search_role(HT_item value);

private slots:
    void on_Input_From_File_clicked();
    void on_DeleteButton_clicked();
    void on_RefreshButton_clicked();
    void on_ClearButton_clicked();
    void on_Add_Button_clicked();
    void on_SearchButton_clicked();

    void onHumanChanged(HT_item* new_human);
    void onHumanSearching(HT_item* new_human);

private:
    Ui::hashtable *ui;

    QString path_in_hash;
    HT_item** table;
    int TABLE_SIZE;

    void populateTable();
    void addToTable(HT_item new_node);
};

#endif // HASHTABLE_H
