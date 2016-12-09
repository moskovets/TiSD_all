#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
void printer(int n, int m, int** arr) {
    FILE *graph = fopen("/tmp/graph.gv", "w");
    fprintf(graph, "digraph G{\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(arr[i][j] != 0) {
                fprintf(graph, "%d->%d\n", i, j);//,//head->value);
            }
        }
    }
    fprintf(graph, "}");
    fclose(graph);

}

/*template <typename T>
void BT<T>::printer(element<T>*tmp, element<T>*parent, FILE *graph) {

    if (tmp) {
        if (parent != NULL)
            fprintf(graph, "%d->%d\n",parent->value, tmp->value);
        printer(tmp->left, tmp, graph);
        printer(tmp->right, tmp, graph);
    }
}
*/
int ** new_arr(int n) {
    int **arr = new int* [n+1];
    for(int i = 0; i <= n; i++) {
        arr[i] = new int [n+1];
        for(int j = 0; j <= n; j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}
void free_arr(int ***arr, int n) {
    for(int i = 0; i <= n; i++) {
        delete []*arr[i];
    }
    delete *arr;
}
int ** from_file_to_graph(int &n) {
    ifstream inp;
    inp.open("/home/moskov/ClionProjects/TiSD/laba8/data.txt");
    inp >> n;
    int **arr = new_arr(n);
    int x, y;
    while(inp >> x) {
        inp >> y;
        arr[x][y] = 1;
    }
    inp.close();
    return arr;
}
void dfs(int **arr, int n, int** used, int tmp) {
    for(int i = 1; i <= n; i++) {
        if(arr[tmp][i] && !(*used)[i]) {
            (*used)[i] = 1;
            dfs(arr, n, used, i);
        }
    }
}
int main() {
    char a, ch;
    int n = 0;
    int x, y;
    int **arr = NULL;
    int *used = NULL;
    while(true) {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "0: Загрузить граф из файла" << endl;
        cout << "1: Задать граф" << endl;
        cout << "2: Вывод вершин, недостижимых из исходной" << endl;
        cout << "3: Визуализация графа" << endl;
        cout << "4: Закончить работу" << endl;
        cin >> a;
        switch (a) {
            case '0':
                if(arr)
                    free_arr(&arr, n);
                arr =  from_file_to_graph(n);
                break;
            case '1':
                cout << "Введите кол-во вершин: ";
                if(!(scanf("%d", &n)) || (n <= 0) || (n >= 5000))
                    cout << "Error" << endl;
                else {
                    if(arr)
                        free_arr(&arr, n);
                    arr = new_arr(n);
                    cout << "Введите список ребер (отрацательное число - конец ввода)\n";
                    x = y = 0;
                    while(x >= 0 && y >= 0) {
                        cin >> x;
                        if(x <= 0 || x > n)
                            break;
                        cin >> y;
                        if(y <= 0 || y > n)
                            break;
                        arr[x][y] = 1;
                    }
                }
                break;
            case '2':
                if(!(scanf("%d", &x)) || (x <= 0) || (x > n))
                    cout << "Error" << endl;
                else {
                    used = new int[n + 1];
                    for (int i = 0; i <= n; i++)
                        used[i] = 0;
                    used[x] = 1;
                    dfs(arr, n, &used, x);
                    for(int i = 1; i <= n; i++) {
                        if(used[i] == 0) {
                            cout << i << " ";
                        }
                    }
                    cout << endl;
                }
                //work_with_tree(avl_tree);
                break;
            case '3':
                //printer();
                break;
            case '4':
                cout << "До свиданья)" << endl;
                return 0;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
}