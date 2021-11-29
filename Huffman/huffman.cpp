#include "huffman.h"
#include "ui_huffman.h"

huffman::huffman(QWidget *parent) : QDialog(parent), ui(new Ui::huffman) {
    ui->setupUi(this);
}
huffman::~huffman() {
    delete ui;
}

void print_chars_codes(QMap<QChar, QVector<bool> > table) {
    QMap<QChar, QVector<bool> >::iterator i;
    for (i = table.begin(); i != table.end(); i++) {
        QVector<bool> a = i.value();
        int size = a.size();
        QString b;
        for (int i = 0; i < size; i++)
            if(a[i])
                b.push_back('1');
            else
                b.push_back('0');
        qCritical() << " [" << i.key() << "]: " + b;
    }
}

bool compare(const huff_node *l, const huff_node *r){
    return l->freq < r->freq;
}
void Huffman::BuildTable(huff_node* root) {
    if (root->left != NULL) {
        code.push_back(0);
        BuildTable(root->left);
    }
    if (root->right != NULL) {
        code.push_back(1);
        BuildTable(root->right);
    }
    if (root->left == NULL && root->right == NULL) table[root->data] = code;
    if (code.size() > 0) code.pop_back();
}
void Huffman::compress(QString text) {
    str = text;

    // 1 - Состовляю мапу символ/частота
    QMap<QChar, int> m;
    for (int i = 0; i < str.size(); i++)
        m[str[i]]++;

    // 2 - Конвертирую мапу в двусвязный список
    QList<huff_node*> t;
    QMap<QChar, int>::iterator i;
    for (i = m.begin(); i != m.end(); i++) {
        huff_node* p = new huff_node;
        p->data = i.key();
        p->freq = i.value();
        t.push_back(p);
    }

    // 3 - Состовляю дерево Хаффмана
    while (t.size() != 1) {
        std::sort(t.begin(), t.end(), compare);

        huff_node* sonl = t.front();
        t.pop_front();
        huff_node* sonr = t.front();
        t.pop_front();

        huff_node* parent = new huff_node(sonl, sonr);
        t.push_back(parent);
    }
    root = t.front();


    // 4 - Состовляю мапу символ/код
    BuildTable(root);
}
QString Huffman::decompress(QByteArray byte_array) {
    QString text;
    huff_node* p = root;
    huff_node* tmp_node;
    int count = 0; unsigned char byte;
    byte = byte_array[0];
    byte_array.remove(0,1);
    do {
        bool b;
        b = byte & (1 << (7 - count));
        if (b){
            qCritical() << "tqt";
            qCritical() << root->data;
            tmp_node = p->right;
            qCritical() << tmp_node->data;
            p = tmp_node;
        }
        else {
            qCritical() << root->data;
            tmp_node = p->left;
            qCritical() << tmp_node->data;
            p = tmp_node;
        }
        if (p->left == NULL && p->right == NULL) {
            text.append(p->data);
            p = root;
        }
        count++;
        if (count == 8) {
            count = 0;
            byte = byte_array[0];
            byte_array.remove(0,1);
        }
    } while (byte_array.size());
    return text;
}

QMap<QChar, QVector<bool> > Huffman::get_table(){
    return table;
}
huff_node* Huffman::get_root(){
    return root;
}

void huffman::on_CompressButton_clicked() {
    QString input_name, output_name;
    input_name = ui->InComEdit->text();
    output_name = ui->OutComEdit->text();
    QFile file_input(input_name);
    if(!file_input.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file_input.open(QIODevice::ReadWrite)){
        qCritical() << file_input.errorString();
        return;
    }
    QString whole_file;
    whole_file.append(file_input.readAll());
    file_input.close();

    Huffman huff;
    huff.compress(whole_file);
    table = huff.get_table();
    root = huff.get_root();

    QByteArray byte_array;
    int count = 0; char buf = 0;
    for (int i = 0; i < whole_file.size(); i++) {
        QChar c = whole_file[i];
        QVector<bool> x = table[c];
        for (int n = 0; n < x.size(); n++)
        {
            buf = buf | (x[n] << (7 - count));
            count++;
            if (count == 8) { count = 0;   byte_array.push_back(buf); buf = 0; }
        }
    }


    QFile file_output(output_name);
    if(!file_output.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file_output.open(QIODevice::ReadWrite)){
        qCritical() << file_output.errorString();
        return;
    }
    file_output.write(byte_array);
    file_output.close();
}
void huffman::on_DecompressButton_clicked() {
    QString input_name, output_name;
    input_name = ui->InDecomEdit->text();
    output_name = ui->OutDecomEdit->text();
    QFile file_input(input_name);
    if(!file_input.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file_input.open(QIODevice::ReadWrite)){
        qCritical() << file_input.errorString();
        return;
    }
    QFile file_output(output_name);
    if(!file_output.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file_output.open(QIODevice::WriteOnly)){
        qCritical() << file_output.errorString();
        return;
    }
    QByteArray byte_array = file_input.readAll();
    Huffman huff(table, root);
    QString text(" ");
    print_chars_codes(table);
    text = huff.decompress(byte_array);
    file_output.write(text.toUtf8());
    file_input.close();
}












