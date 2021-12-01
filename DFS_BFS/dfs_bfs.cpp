#include "dfs_bfs.h"
#include "ui_dfs_bfs.h"

dfs_bfs::dfs_bfs(QWidget *parent) : QDialog(parent), ui(new Ui::dfs_bfs) {
    ui->setupUi(this);
}
dfs_bfs::~dfs_bfs() {
    delete ui;
}

Graph::Graph() {
    V = 0;
}
void Graph::enter_graph(QList<int>* adj_list, int n) {
    adj = adj_list;
    V = n;
    visited = new bool[V];
    distance_BFS.fill(0, V);
    time_entry_DFS.fill(0, V);
    time_exit_DFS.fill(0, V);
    parent.fill(0, V);
}
void Graph::BFS(int s) {
    QList<int>::iterator i;
    QQueue<int> to_explore;

    visited[s] = true;
    to_explore.push_back(s);

    while (!to_explore.empty()) {
        s = to_explore.front();
        BFS_list.push_back(s);
        to_explore.pop_front();
        for (i = adj[s].begin(); i != adj[s].end(); ++i){
            if (!visited[*i]) {
                visited[*i] = true;
                to_explore.push_back(*i);
                distance_BFS[*i] = distance_BFS[s]+1;
//                qCritical() << *i;
//                qCritical() << distance_BFS[*i];
//                qCritical() << ' ';
            }
        }
    }
}
void Graph::DFS_stack(int s) {
    QList<int>::iterator i;
    QStack<int> to_explore;

    to_explore.push(s);

    while (!to_explore.empty()) {
        s = to_explore.top();
        to_explore.pop();

        if (!visited[s]) {
            DFS_list.push_back(s);
            visited[s] = true;
        }

        for (i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i]) {
                to_explore.push(*i);
            }
    }
}
void Graph::DFS_with_time(int s) {
    static int time = 1;

    time_entry_DFS[s] = time++;
    DFS_list.push_back(s);
    visited[s] = true;

    QList<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visited[*i]) {
            parent[*i] = s;
            DFS_with_time(*i);
        }
    time_exit_DFS[s] = time++;
}

void Task_3_Graph::enter_graph(QList<int>* adj_list, QVector<QString> words_vec, int n) {
    adj = adj_list;
    V = n;
    visited = new bool[V];
    words = words_vec;
}
bool Task_3_Graph::DFS_search_word(int s, QString str) {
    result_path.push_back(words[s]);
    visited[s] = true;
    if (words[s] == str)
        return true;
    QList<int>::iterator i;
    for (i = adj[s].begin(); i != adj[s].end(); ++i)
        if (!visited[*i])
            if (DFS_search_word(*i, str))
                return true;
    result_path.pop_back();
    return false;
}

void dfs_bfs::on_Task1Button_clicked() {
    QString file_name;
    file_name = ui->Task1FileEdit->text();
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

    int n, tmp;
    fin >> n;
    QList<int>* adj = new QList<int>[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> tmp;
            if (tmp == 1)
                adj[i].push_back(j);
        }
    } file.close();

    Graph g;
    g.enter_graph(adj, n);
    int start_vertex = ui->Task1InputEdit->text().toInt();
    g.BFS(start_vertex);

    int distance = ui->Task1InputDistanceEdit->text().toInt();
    QString answear_string;

    ui->AnswearLabel->clear();
    for (int i = 0; i < g.V; i++) {
        if (g.distance_BFS[g.BFS_list[i]] > distance)
            break;
        ui->AnswearLabel->append(QString::number(g.BFS_list[i]) + "[" + QString::number(g.distance_BFS[g.BFS_list[i]]) + "] ");
    }
}
void dfs_bfs::on_Task2Button_clicked() {
    QString file_name;
    file_name = ui->Task2FileEdit->text();
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

    int n, tmp;
    fin >> n;
    QList<int>* adj = new QList<int>[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> tmp;
            if (tmp == 1)
                adj[i].push_back(j);
        }
    } file.close();

    Graph g;
    g.enter_graph(adj, n);
    int start_vertex = ui->Task2InputEdit->text().toInt();
    g.DFS_with_time(start_vertex);
    g.DFS_stack(start_vertex);

    //ui->Task2AnswearTextEdit->append();
    ui->Task2AnswearTextEdit->clear();
    ui->Task2AnswearTextEdit->append("Edge classification\n");
    QList<int>::iterator j;
        for (int i = 0; i < g.V; i++)
            for (j = g.adj[i].begin(); j != g.adj[i].end(); ++j)
                if (i == g.parent[*j]) {
                     ui->Task2AnswearTextEdit->append("Tree edge: ["  + QString::number(i) + "; " + QString::number(*j) + "]");
                }
                else if (g.time_entry_DFS[i] > g.time_entry_DFS[*j] && g.time_exit_DFS[i] < g.time_exit_DFS[*j]) {
                     ui->Task2AnswearTextEdit->append("Back Edge: ["   + QString::number(i) + "; " + QString::number(*j) + "]");
                }
                else if (g.time_entry_DFS[i] < g.time_entry_DFS[*j] && g.time_exit_DFS[i] > g.time_exit_DFS[*j]) {
                     ui->Task2AnswearTextEdit->append("Forward Edge: ["   + QString::number(i) + "; " + QString::number(*j) + "]");
                }
                else if (g.time_entry_DFS[i] > g.time_entry_DFS[*j] && g.time_exit_DFS[i] > g.time_exit_DFS[*j]) {
                     ui->Task2AnswearTextEdit->append("Cross Edge: ["   + QString::number(i) + "; " + QString::number(*j) + "]");
                }
}
void dfs_bfs::on_Task3Button_clicked() {
    QString file_name;
    file_name = ui->Task3FileEdit->text();
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

    int n, tmp;
    QString tmp_word;
    fin >> n;

    QVector<QString> words;
    for (int i = 0; i < n; i++) {
        fin >> tmp_word;
        words.push_back(tmp_word);
    }

    QList<int>* adj = new QList<int>[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> tmp;
            if (tmp == 1)
                adj[i].push_back(j);
        }
    } file.close();

    QString search_word;
    search_word = ui->Task3SearchWordEdit->text();

    Task_3_Graph g;
    g.enter_graph(adj, words, n);
    int start_vertex = ui->Task3InputEdit->text().toInt();
    g.DFS_search_word(start_vertex, search_word);

    ui->Task3AnswearTextEdit->clear();
    if (g.result_path.size() == 0)
        ui->Task3AnswearTextEdit->append(" Cannot find the word(");
    for (int i = 0; i < g.result_path.size() - 1; i++)
        ui->Task3AnswearTextEdit->append(g.result_path[i] + " ---> ");
    ui->Task3AnswearTextEdit->append(g.result_path[g.result_path.size() - 1]);
}
//    for (int j = 0; j < V; j++) {
//        qCritical() << distance_BFS[BFS_list[j]];
//    } qCritical() << ' ';



