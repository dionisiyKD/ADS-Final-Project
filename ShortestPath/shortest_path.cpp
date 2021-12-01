#include "shortest_path.h"
#include "ui_shortest_path.h"

shortest_path::shortest_path(QWidget *parent) : QDialog(parent), ui(new Ui::shortest_path) {
    ui->setupUi(this);
}
shortest_path::~shortest_path() {
    delete ui;
}

void Graph_dij_floyd::input_graph(QVector<QVector<double>> g, int v) {
    V = v;
    graph = g;
}
int Graph_dij_floyd::minDistance(double* shortest_dist, bool* incl_path) {
    int min = INT_MAX, min_index = 0;
    for (int i = 0; i < V; i++)
        if (incl_path[i] == false && shortest_dist[i] <= min) {
            min = shortest_dist[i];
            min_index = i;
        }
    return min_index;
}
double* Graph_dij_floyd::dijkstra(int src) {
    double* shortest_dist = new double[V] {};
    bool* incl_path = new bool[V] {};

    for (int i = 0; i < V; i++)
        shortest_dist[i] = INT_MAX, incl_path[i] = false;
    shortest_dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(shortest_dist, incl_path);
        incl_path[u] = true;

        for (int v = 0; v < V; v++)
            if (!incl_path[v] && graph[u][v] && shortest_dist[u] != INT_MAX
                && shortest_dist[u] + graph[u][v] < shortest_dist[v])
                shortest_dist[v] = shortest_dist[u] + graph[u][v];
    }

    return shortest_dist;
}
QVector<QVector<double>> Graph_dij_floyd::floydWarshall() {
    int inf_value = 9999;

    QVector<QVector<double>> dist;
    QVector<double> tmp;

    for (int i = 0; i < V; i++) {
        tmp.clear();
        for (int j = 0; j < V; j++)
            tmp.push_back(graph[i][j]);
        dist.push_back(tmp);
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != inf_value && dist[i][k] != inf_value))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    return dist;
}
void Graph_dij_floyd::convert() {
//    cout << " Write speed limit: ";
//    int speed; cin >> speed;
//    for (int i = 0; i < V; i++)
//        for (int j = 0; j < V; j++)
//            if (graph[i][j] != 9999 && graph[i][j] != 0)
//                graph[i][j] /= speed;
}


void GraphBellman::inputGraph(QVector<Edge> edg, int v, int e) {
    edge = edg;
    V = v;
    E = e;
}
QVector<int> GraphBellman::BellmanFord(int u) {
    int v = this->V;
    int e = this->E;

    QVector<int> dist;

    for (int i = 0; i < v; i++)
        dist.push_back(INT_MAX);
    dist[u] = 0;
    for (int i = 1; i <= v - 1; i++) {
        for (int j = 0; j < e; j++) {
            int u = edge[j].u;
            int v = edge[j].v;
            int w = edge[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
    return dist;
}
void GraphBellman::discount(QVector<QPair<int, int>> discounts) {
    for (int i = 0; i < E; i++)
        for (int j = 0; j < discounts.size(); j++)
            if (edge[i].u == discounts[j].first)
                edge[i].w -= discounts[j].second;
}



void shortest_path::on_Task1Button_clicked() {
    QString file_name;
    file_name = ui->FileNameEditT_1->text();
    QFile file(file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    int V, E;
    fin >> V >> E;
    Edge tmp_edge;
    int tmp_int; int e = 0;
    QVector<Edge> edge;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            fin >> tmp_int;
            if (tmp_int != 0)
            {
                tmp_edge.u = i;
                tmp_edge.v = j;
                tmp_edge.w = tmp_int;
                edge.push_back(tmp_edge);
                e++;
            }
        }
    file.close();

    int start_vertex = ui->StartVertexEditT_1->text().toInt();
    QVector<int> result;

    int numb_disc;
    fin >> numb_disc;
    QVector<QPair<int, int>> discounts;
    QPair<int, int> tmp;
    for (int i = 0; i < numb_disc; i++) {
        fin >> tmp.first >> tmp.second;
        discounts.push_back(tmp);
    }

    GraphBellman g;
    g.inputGraph(edge, V, E);
    g.discount(discounts);
    result = g.BellmanFord(start_vertex);
    ui->AnswearEditT_1->clear();
    for (int i = 0; i < V; i++)
        ui->AnswearEditT_1->append("[" + QString::number(i) + "]: " + QString::number(result[i]));
}
void shortest_path::on_Task2Button_clicked() {
    QString file_name;
    file_name = ui->FileNameEditT_2->text();
    QFile file(file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    int V, garbage;
    fin >> V >> garbage;
    QVector<QVector<double>> graph;
    QVector<double> tmp_vec; double tmp_double;
    for (int i = 0; i < V; i++) {
        tmp_vec.clear();
        for (int j = 0; j < V; j++) {
            fin >> tmp_double;
            tmp_vec.push_back(tmp_double);
        }
        graph.push_back(tmp_vec);
    } file.close();

    int start_vertex = ui->StartVertexEditT_2->text().toInt();
    double* result;

    Graph_dij_floyd g;
    g.input_graph(graph, V);
    //g.convert();
    result = g.dijkstra(start_vertex);
    ui->AnswearEditT_2->clear();
    for (int i = 0; i < V; i++)
        ui->AnswearEditT_2->append("[" + QString::number(i) + "]: " + QString::number(result[i]));
}
void shortest_path::on_Task3Button_clicked() {
    QString file_name;
    file_name = ui->FileNameEditT_3->text();
    QFile file(file_name);
    if(!file.exists()){
        qCritical() << "File not found";
        return;
    }
    if(!file.open(QIODevice::ReadWrite)){
        qCritical() << file.errorString();
        return;
    }
    QTextStream fin(&file);

    int V, garbage;
    fin >> V >> garbage;
    QVector<QVector<double>> graph;
    QVector<double> tmp_vec; double tmp_double;
    for (int i = 0; i < V; i++) {
        tmp_vec.clear();
        for (int j = 0; j < V; j++) {
            fin >> tmp_double;
            tmp_vec.push_back(tmp_double);
        }
        graph.push_back(tmp_vec);
    } file.close();

    QVector<QVector<double>> result;

    Graph_dij_floyd g;
    g.input_graph(graph, V);
    //g.convert();
    result = g.floydWarshall();
    int inf_value = 9999;
    ui->AnswearEditT_3->clear();
    for (int i = 0; i < V; i++) {
        QString tmp_str;
        for (int j = 0; j < V; j++) {
            if (result[i][j] == inf_value)
                tmp_str.append("INF ");
            else
                tmp_str.append(QString::number(result[i][j]) + ' ');
        }
        ui->AnswearEditT_3->append(tmp_str);
    }

}








































