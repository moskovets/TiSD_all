#include <iostream>
#include "BST.h"

void tree_from_file(BST &tree)
{
    ifstream inp;
    inp.open("/home/moskov/ClionProjects/TiSD/laba6/data.txt");
    if(!inp.is_open()) { cout << "Cannot open file" << endl; return; }
    char str[LEN_WORD];
    while(inp >> str) {
        tree.insert(str);
    }
    inp.close();
}
void time_compare() {
    ifstream inp;
    BST tree;
    inp.open("/home/moskov/ClionProjects/TiSD/laba6/bigdata.txt");
    if(!inp.is_open()) { cout << "Cannot open file" << endl; return; }
    char str[LEN_WORD];
    while(inp >> str) {
        tree.insert(str);
    }
    inp.close();

    char word[LEN_WORD] = "some";
    bool res1 = 0, res2 = 0;
    time_t t1 = clock();
    res1 = tree.find(word);
    time_t t2 = clock();
    cout << "Время поиска в дереве: " << t2 - t1 << endl;

    inp.open("/home/moskov/ClionProjects/TiSD/laba6/bigdata.txt");
    if(!inp.is_open()) { cout << "Cannot open file" << endl; return; }
    time_t t3 = clock();
    while(inp >> str) {
        if(strcmp(str, word) == 0) {
            res2 = 1;
            break;
        }
    }
    time_t t4 = clock();
    cout << "Время поиска в файле " << t4 - t3 << endl;

    log(res1 == res2 ? "ok" : "fail");

    inp.close();

}
int main(int argc, char* argv[]) {
    int a;
    char str[LEN_WORD];
    int b;
    BST tree;
    char c;
    while(true)
    {

        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Добавление в дерево слов из файла" << endl;
        cout << "1: Отобразить дерево (1 способ)" << endl;
        cout << "2: Отобразить дерево (2 способ)" << endl;
        cout << "3: Добавить слово в дерево" << endl;
        cout << "4: Удалить слово из дерева" << endl; //TODO
        cout << "5: Поиск слова" << endl;
        cout << "6: Найти кол-во слов, начинающихся на одну букву, выделить их" << endl;
        cout << "7: Сравнить время поиска слов из файла и в дереве" << endl; //TODO
        cout << "8: Очистить дерево" << endl;
        cout << "9: Обход дерева" << endl;
        cout << "10: Закончить работу" << endl;
        cin >> a;
        switch(a) {
            case 0:
                tree_from_file(tree);
                cout << "Элементы добавлены в дерево\n" << endl;
                break;
            case 1:
                tree.show();
                break;
            case 2:
                tree.show_as_tree();
                break;
            case 3:
                cout << "Введите слово: " << endl;
                cin >> str;
                tree.insert(str);
                break;
            case 4:
                cout << "Введите слово: " << endl;
                cin >> str;
                if(tree.remove(str)) {
                    cout << "Слово успешно удалено" << endl;
                }
                else {
                    cout << "Дерево не содержит указанное слово" << endl;
                }
                break;
            case 5:
                cout << "Введите слово: " << endl;
                cin >> str;
                if(tree.find(str)) {
                    cout << "Слово есть в дереве" << endl;
                }
                else {
                    cout << "Дерево не содержит указанное слово" << endl;
                }
                break;
            case 6:
                cin >> c;
                tree.find_letter(c);
                break;
            case 7:
                time_compare();
                break;
            case 8:
                tree.~BST();
                tree = BST();
                break;
            case 9:
                cout << "1: Сверху вниз (корень, левый, правый) - префиксный обход" << endl;
                cout << "2: Слева направо (левый, корень, правый) - инфиксный обход" << endl;
                cout << "3: Сверху вниз (левый, правый, корень) - постфиксный обход" << endl;
                cin >> b;
                switch(b) {
                    case 1: tree.RootLeftRight(); break;
                    case 2: tree.LeftRootRight(); break;
                    case 3: tree.LeftRightRoot(); break;
                    default: cout << "Error command" << endl; break;
                }
                break;
            case 10:
                cout << "До свиданья)" << endl;
                return 0;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
    return 0;
}