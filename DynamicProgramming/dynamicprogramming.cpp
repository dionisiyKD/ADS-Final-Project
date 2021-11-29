#include "dynamicprogramming.h"
#include "ui_dynamicprogramming.h"

dynamicprogramming::dynamicprogramming(QWidget *parent) : QDialog(parent), ui(new Ui::dynamicprogramming) {
    ui->setupUi(this);
}
dynamicprogramming::~dynamicprogramming() {
    delete ui;
}

void sequence::split_subsequences() {
    QVector<int> tmp;
    for (int i = 0; i < n - 1; i++) {
        tmp.push_back(arr[i]);
        if ((arr[i + 1] >= arr[i]) || (i + 1 == n)) {
            subsequences.push_back(tmp);
            tmp.clear();
        }
    }
}
void sequence::find_max_subsequence() {
    for (int i = 0; i < subsequences.size(); i++)
        if (subsequences[i].size() > result.size())
            result = subsequences[i];
}
QVector<int> sequence::get_max_subsequence() {
    return result;
//    cout << "\nМаксимально длинная спадная последоватльность: ";
//    for (int i = 0; i < result.size(); i++)
//        cout << result[i] << " ";
//    cout << "\nЕё размер: ";
//    cout << result.size() << endl;
}

QMap<QString, int> Town::solve() {
    QString tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++) {
            if (j != i) {
                tmp += matrix[i][j];
                tmp += matrix[i + 1][j];
                std::sort(tmp.begin(), tmp.end());
                results[tmp]++;
                tmp.clear();
            }
            if(j!=n-1) {
                tmp += matrix[i][j];
                tmp += matrix[i][j+1];
                std::sort(tmp.begin(), tmp.end());
                results[tmp]++;
                tmp.clear();
            }
        }
    QMap<QString, int>::iterator i;
    for (i = results.begin(); i != results.end(); i++)
        i.value() *= 2;
    return results;
}

void dynamicprogramming::on_FirstTaskButton_clicked() {
    int num = ui->NumberOfElemEdit->text().toInt();
    QString text = ui->ElementsEdit->toPlainText();
    QStringList list = text.split(QRegularExpression("\\s+"));

    QVector<int> arr;
    for (int i = 0; i < list.count(); i++)
        arr.push_back(list[i].toInt());

    sequence seq(num, arr);
    seq.split_subsequences();
    seq.find_max_subsequence();
    QVector<int> res = seq.get_max_subsequence();

    QString result_string("Result: ");
    for (int i = 0; i<res.size(); i++)
        result_string.append(" " + QString::number(res[i]));
    result_string.append("\nSize of the sequence: " + QString::number(res.size()));
    ui->FirstTaskAnswearLabel->setText(result_string);
}

void dynamicprogramming::on_InputFromFileMatrixButton_clicked() {
    QFile file("dp_matrix.txt");
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }

    QVector<QString> cells;
    QString text = file.readAll();
    QStringList list = text.split(QRegularExpression("\\s+"));

    for (int i = 0; i < list.count(); i++)
        cells.push_back(list[i]);
    int n = sqrt(list.size());

    QVector<QVector<QString>> matrix;
    QVector<QString> tmp_line; QString tmp_str;
    for (int i = 0; i < cells.size(); i++){
        tmp_line.push_back(cells[i]);
        if(tmp_line.size() == n){
            matrix.push_back(tmp_line);
            tmp_line.clear();
        }
    }

    matr.clear();
    matr = matrix;
    file.close();
}
void dynamicprogramming::on_SecondTaskButton_clicked() {
    QVector<QVector<QString>> matrix = matr;
    int n = matr[0].size();

    Town twn(matrix, n);
    QMap<QString, int> result = twn.solve();
    QString result_string("Result: \n");
    QMap<QString, int>::iterator i;
    for (i = result.begin(); i != result.end(); i++)
        result_string.append("[" + i.key() + "]: " + QString::number(i.value()) + '\n');
    ui->SecondTaskAnswearEdit->setPlainText(result_string);
}




