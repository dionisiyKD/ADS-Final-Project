#ifndef BTREE_H
#define BTREE_H

#include <QDialog>

namespace Ui { class btree; }

class btree : public QDialog {
    Q_OBJECT

public:
    explicit btree(QWidget *parent = nullptr);
    ~btree();

private:
    Ui::btree *ui;
};

#endif // BTREE_H
