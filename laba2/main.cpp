//#include <iostream>
#include "Stack_array.h"
#include "Stack_list.h"
//#include <string>
void array() {
    Stack_array A;
    int a;
    char x[MAX_LEN_WORD];
    char ch;
    char* y;
    int flag;
    while(true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Показать стек" << endl;
        cout << "1: Добавить эл-ты в стек" << endl;
        cout << "2: Извлечь эл-т из стека" << endl;
        cout << "3: Распечатать слова в обратном порядке" << endl;
        cout << "4: Закончить работу" << endl;
        cin >> a;
        switch(a)
        {
            case 0:
                A.show();
                break;
            case 1:
                ch = ' ';
                while(ch != '\n'){
                    cin >> x;
                    flag = 0;
                    for(int i = 0; i < strlen(x); ++i) {
                        if(!isalpha(x[i])) {
                            cout << "Error symbol in " << x << endl;
                            flag = 1;
                            break;
                        }
                    }
                    if(strlen(x) >= MAX_LEN_WORD) {
                        cout << "Word is too long!" << endl;
                        flag = 1;
                    }
                    if(A.is_full()) {
                        cout << "Stack overflow" << endl;
                        flag = 1;
                    }
                    if(!flag) {
                        A.push(x);
                    }
                    cin.get(ch);
                }
                break;
            case 2:
                if(A.empty()) { cout << "Стек пустой!" << endl; break; }
                y = A.pop();
                cout << "Удаленный эл-т " << y << endl;
                delete []y;
                break;
            case 3:
                while(!A.empty()){
                    y = A.pop();
                    cout << y << " ";
                    delete []y;
                }
                cout << endl;
                break;
            case 4:
                cout << "До свиданья)" << endl;
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
}
void list() {
    Stack_list A;
    int a;
    char x[MAX_LEN_WORD];
    char ch;
    char* y;
    int flag;
    while(true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Показать стек" << endl;
        cout << "1: Добавить эл-ты в стек" << endl;
        cout << "2: Извлечь эл-т из стека" << endl;
        cout << "3: Распечатать слова в обратном порядке" << endl;
        cout << "4: Распечатать адреса эл-тов списка" << endl;

        cout << "5: Закончить работу" << endl;
        cin >> a;
        switch(a)
        {
            case 0:
                A.show();
                break;
            case 1:
                ch = ' ';
                while(ch != '\n'){
                    cin >> x;
                    flag = 0;
                    for(int i = 0; i < strlen(x); ++i) {
                        if(!isalpha(x[i])) {
                            cout << "Error symbol in " << x << endl;
                            flag = 1;
                            break;
                        }
                    }
                    if(strlen(x) >= MAX_LEN_WORD) {
                        cout << "Word is too long!" << endl;
                        flag = 1;
                    }
                    if(A.is_full()) {
                        cout << "Stack overflow" << endl;
                        flag = 1;
                    }
                    if(!flag) {
                        A.push(x);
                    }
                    cin.get(ch);
                }
                break;
            case 2:
                if(A.empty()) { cout << "Стек пустой!" << endl; break; }
                y = A.pop();
                cout << "Удаленный эл-т " << y << endl;
                delete []y;
                break;
            case 3:
                while(!A.empty()){
                    y = A.pop();
                    cout << y << " ";
                    delete []y;
                }
                cout << endl;
                break;
            case 4:
                A.show_adr();
                break;
            case 5:
                cout << "До свиданья)" << endl;
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
}
void compare_stack() {
    //TODO
}
int main()
{
    setlocale(LC_CTYPE, "rus");
    cout << "**************************************************************" << endl;
    cout << "Выберите одно из следующих действий:" << endl;

    cout << "0: Работа со стеком (массив)" << endl;
    cout << "1: Работа со стеком (список)" << endl;
    cout << "2: Сравнение скорости работы массива и списка" << endl;
    int ch;
    cin >> ch;
    switch(ch) {
        case 0:
            array();
        case 1:
            list();
            break;
        case 2:
            compare_stack();
            break;
        default:
            cout << "Error code" << endl;
            break;
    }
    return 0;
}
