/*
 * В этой лабе сюрприз - дружественные функции для печати деревьев
 * и специально для Леши - все шаблонное
 */
/*
 *remove bool + вхождения
 */
#include "CAVL.cpp"
#include "CBST.cpp"
#include "CHashTableClose.cpp"
#include "CHashTableOpen.cpp"

int compare_count;
void log(const char *str) { cout << "log: " << str << endl;}
void probel(int n) {
    for(int i = 0; i < n; i++) {
        cout << " ";
    }
}

unsigned int hash_function(Data<char> const & obj) {
    return (unsigned int) (obj.value);
}
template <typename T>
void print(T *tmp, int deep, bool flag) {
    if(tmp) {
        for (int i = 0; i < deep - 1; i++) {
            cout << "|    ";
        }
        if (deep >= 1)
            cout << "|----";
        cout << tmp->key << endl;
        flag = false;
        if(tmp->left || tmp->right) { flag = true; }
        print(tmp->left, deep + 1, flag);
        print(tmp->right, deep + 1, flag);
    }
    else if(flag) {
        for (int i = 0; i < deep - 1; i++) {
            cout << "|    ";
        }
        if (deep >= 1)
            cout << "|----";
        cout << "-----" << endl;
    }
}
template <typename T>
void show_as_tree(T* tree) {
    print(tree->head, 0, true);
}
template <typename T>
void print_tree(T *h) {
    queue<T *> A;
    A.push(h);
    T *tmp = NULL;
    int level = 0;
    int flag = 1;
    //probel(5);
    while(!A.empty() && flag && level < 5) {
        flag = 0;
        int step = CONSOL_SIZE / pow(2, level + 1);
        //cout << step << endl;
        //int index = step;
        for(int i = 0; i < pow(2, level); i++) {
            tmp = A.front();
            A.pop();
            probel(step - 3);
            //index += 2 * step;
            if (tmp == NULL) {
                A.push(NULL);
                A.push(NULL);
                probel(6);
            }
            else {
                cout << tmp->key;
                probel(6 - tmp->key.print_width());
                A.push(tmp->left);
                A.push(tmp->right);
                flag = 1;
            }
            probel(step - 4);
            cout << " ";
        }
        cout << endl;
        cout << endl;
        level++;
    }
}
template <typename T>
void show(T* tree) {
    print_tree(tree->head);
}
template <typename T>
void from_file_to_struct(T* obj) {
    ifstream inp;
    inp.open("/home/moskov/ClionProjects/TiSD/laba6/data.txt");
    char ch;
    while(cin >> ch) {
        if(isalpha(ch)) {
            obj->Insert(Data<char>(ch));
        }
    }
    inp.close();
}
template <typename T>
void from_string_to_struct(string str, T* obj) {
    for(int i = 0; i < str.size(); i++) {
        if(isalpha(str[i])) {
            obj->Insert(Data<char>(str[i]));
        }
    }
}
template <typename T>
void work_with_tree(T* tree) {
    char a, ch;
    while(true)
    {

        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "1: Отобразить дерево (1 способ)" << endl;
        cout << "2: Отобразить дерево (2 способ)" << endl;
        cout << "3: Добавить букву в дерево" << endl;
        cout << "4: Удалить букву из дерева" << endl;
        cout << "5: Удалить все вхождения буквы в дереве" << endl;
        cout << "6: Поиск буквы" << endl;
        cout << "7: Закончить работу" << endl;
        cin >> a;
        switch(a) {
            case '1':
                show(tree);
                break;
            case '2':
                show_as_tree(tree);
                break;
            case '3':
                cout << "Введите символ: " << endl;
                cin >> ch;
                tree->Insert(Data<char>(ch));
                break;
            case '4':
                cout << "Введите символ: " << endl;
                cin >> ch;
                if(tree->Remove(Data<char>(ch))) {
                    cout << "Буква успешно удалено" << endl;
                }
                else {
                    cout << "Дерево не содержит указанную слово" << endl;
                }
                break;
            case '5':
                cout << "Введите символ: " << endl;
                cin >> ch;
                while(tree->Remove(Data<char>(ch))) {;}
                cout << "Буква успешно удалено" << endl;
                break;
            case '6':
                cout << "Введите символ: " << endl;
                cin >> ch;
                cout << (tree->Search(Data<char>(ch)) ? "Буква есть в дереве" : "Буквы нет в дереве") << endl;
                break;
            case '7':
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }

}
template <typename T>
void work_with_table(T *table) {
    char a, ch;
    while(true)
    {

        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "1: Отобразить таблицу" << endl;
        cout << "2: Добавить букву в таблицу" << endl;
        cout << "3: Удалить букву из таблицы" << endl;
        cout << "4: Удалить все вхождения буквы в таблице" << endl;
        cout << "5: Поиск буквы" << endl;
        cout << "6: Закончить работу" << endl;
        cin >> a;
        switch(a) {
            case '1':
                table->Show();
                break;
            case '2':
                cout << "Введите символ: " << endl;
                cin >> ch;
                table->Insert(Data<char>(ch));
                break;
            case '3':
                cout << "Введите символ: " << endl;
                cin >> ch;
                if(table->Delete_element(Data<char>(ch))) {
                    cout << "Буква успешно удалено" << endl;
                }
                else {
                    cout << "Таблица не содержит указанную слово" << endl;
                }
                break;
            case '4':
                cout << "Введите символ: " << endl;
                cin >> ch;
                while(table->Delete_element(Data<char>(ch))) {;}
                cout << "Буква успешно удалено" << endl;
                break;
            case '5':
                cout << "Введите символ: " << endl;
                cin >> ch;
                cout << (table->Search_element(Data<char>(ch)) ? "Буква есть в таблице" : "Буквы нет в таблице") << endl;
                break;
            case '6':
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }

}
template <typename T>
bool find(char ch, T* obj) {
    compare_count = 0;
    time_t t1 = clock();
    Data<char> tmp(ch);
    bool res = obj->Search(tmp);
    time_t t2 = clock();
    cout << "Время работы:" << t2 - t1 << endl;
    cout << "Кол-во сравнений: " << compare_count << endl;
    //TODO подсчет памяти
    return res;
}
void interface() {
    char a, ch;

    CBST<Data<char>> * binary_tree = new CBST<Data<char>>();
    CAVL<Data<char>> * avl_tree = new CAVL<Data<char>>();
    CHashTableClose<Data<char>> *close_table = new CHashTableClose<Data<char>>(4);
    cout << "ok" << endl;
    CHashTableOpen<Data<char>> *open_table = new CHashTableOpen<Data<char>>(4);
    string str;
    while(true)
    {

        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "0: Загрузить строку из файла" << endl; //TODO проверка на пустоту
        cout << "1: Работа с bst деревом" << endl;
        cout << "2: Работа с avl деревом" << endl;
        cout << "3: Работа с хэш таблицей с открытой адресацией" << endl;
        cout << "4: Работа с хэш таблицей с закрытой адресацией" << endl;
        cout << "5: Сравнение времени поиска" << endl;
        cout << "6: Изменить исходную строку" << endl;
        cout << "7: Закончить работу" << endl;
        cin >> a;
        switch(a) {
            case '0':
                from_file_to_struct(binary_tree);
                from_file_to_struct(avl_tree);
                from_file_to_struct(close_table);
                from_file_to_struct(open_table);
                cout << "Элементы добавлены в структуры\n" << endl;
                break;
            case '1':
                work_with_tree(binary_tree);
                break;
            case '2':
                work_with_tree(avl_tree);
                break;
            case '3':
                work_with_table(open_table);
                break;
            case '4':
                work_with_table(close_table);
                break;
            case '5':
                cout << "Введите символ: " << endl;
                cin >> ch;
                cout << "Время поиска"<< endl;
                cout << "Бинарное дерево: "; find(ch, binary_tree);
                cout << "Avl дерево: "; find(ch, avl_tree);
                //
                break;
            case '6':
                cout << "Введите строку: ";
                cin >> str;
                delete binary_tree;
                delete avl_tree;
                delete close_table;
                delete open_table;
                //open_table.~CHashTableOpen(); //TODO current
                binary_tree = new CBST<Data<char>>();
                avl_tree = new CAVL<Data<char>>();
                //binary_tree = CBST<Data<char>>();
                //avl_tree = CAVL<Data<char>>();
                close_table = new CHashTableClose<Data<char>>(4);
                open_table = new CHashTableOpen<Data<char>>(4);
                //open_table = CHashTableOpen<Data<char>>(4);

                from_string_to_struct(str, binary_tree);
                from_string_to_struct(str, avl_tree);
                from_string_to_struct(str, close_table);
                from_string_to_struct(str, open_table);
                break;
            case '7':
                cout << "До свиданья)" << endl;
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
}
int main()
{
interface();
//    int i, N, x, k;
//    cin >> N;
//    CAVL<int> tree;
/*
    for(i = 0; i < N; i++)
    {
        cin >> x >> k;
        if(x > 0)
        {
            tree.Add(x);
            //cout << tree.Value(k + 1) << endl;
        }
        else
        {
            //cout << y << " ";
            tree.Remove(-x);
            //cout << tree.Value(k + 1) << endl;
        }
    }*/
//cout << root_avl->h << endl;
//inp.close();
//out.close();
    return 0;
}
