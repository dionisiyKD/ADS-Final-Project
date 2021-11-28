#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QDialog>

namespace Ui { class huffman; }

class huffman : public QDialog
{
    Q_OBJECT

public:
    explicit huffman(QWidget *parent = nullptr);
    ~huffman();

private:
    Ui::huffman *ui;
};

#endif // HUFFMAN_H
