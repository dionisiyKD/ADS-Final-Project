#include "greedyalg.h"
#include "ui_greedyalg.h"

greedyalg::greedyalg(QWidget *parent) : QDialog(parent), ui(new Ui::greedyalg) {
    ui->setupUi(this);
}
greedyalg::~greedyalg() {
    delete ui;
}

water::water() {}
water::~water() {}
void water::bubble_sort() {
    int tmp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (bucket[j] < bucket[j + 1]) {
                tmp = bucket[j];
                bucket[j] = bucket[j + 1];
                bucket[j + 1] = tmp;
            }
        }
}
QVector<int>  water::solve() {
    QVector<int> result;
    int tmp_barrel = barrel;
    this->bubble_sort();
    for (int i = 0; i < n; i++) {
        if (tmp_barrel <= 0) break;
        if ((tmp_barrel >= bucket[i]) || (i == n - 1))
        {
            tmp_barrel -= bucket[i];
            result.push_back(bucket[i]);
        }
    }
//    if (tmp_barrel > 0)
//    {
//        result.clear();
//        int i = 0;
//        if (bucket[i] > barrel) {
//            while (bucket[i + 1] > barrel)
//                i++;
//            result.push_back(bucket[i]);
//            return result;
//        }
//    }
    return result;
//    for (int i = 0; i < result.size(); i++)
//        cout << result[i] << " ";
//    cout << endl;
}
void water::set_variables(int a, int b, QVector<int> array) {
    barrel = a;
    n = b;
    bucket = array;
}

void greedyalg::on_StartButton_clicked() {
    int barrel = ui->BarrelVolumeEdit->text().toInt();
    int n = ui->NumberBucketsEdit->text().toInt();
    QVector<int> buckets;
    QString text = ui->BucketsVolumeEdit->toPlainText();
    QStringList list = text.split(QRegularExpression("\\s+"));
    for (int i = 0; i < list.count(); i++){
        buckets.push_back(list[i].toInt());
    }
    water a;
    a.set_variables(barrel, n, buckets);
    QVector<int> result = a.solve();
    QString result_string("Result: ");
    for (int i = 0; i<result.size(); i++)
        result_string.append(" " + QString::number(result[i]));
    ui->AnswearLabel->setText(result_string);
}
