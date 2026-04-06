#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>
#include <string>
#include <limits>
#include "Date.h"

using namespace std;

class DoubleList
{
public:
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoubleList() { clear(); }

    void menu() {
        int temp;
        do {
            cout << "\n\n\tВыберите действие:\n";
            cout << "\t1. Добавить\n";
            cout << "\t2. Удалить (предшествующий второму с конца)\n";
            cout << "\t3. Вывести все детали на экран\n";
            cout << "\t4. Сохранить список в файл\n";
            cout << "\t0. Выход\n";
            cout << "\tВаш выбор: ";
            cin >> temp;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                temp = -1;
            }
            switch (temp) {
            case 1: add_sorted(); break;
            case 2: remove_before_second_last(); break;
            case 3: print(); break;
            case 4: save_to_file(); break;
            case 0: cout << "\tВыход.\n"; break;
            default: cout << "\tошибка выбора.\n"; break;
            }
        } while (temp != 0);
    }

private:
    struct Node {
        Date date;
        Node* pNext;
        Node* pPrev;
        Node() : pNext(nullptr), pPrev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    Node* createNode() {
        Node* newNode = new Node();
        newNode->date.input_menu();
        return newNode;
    }

    void add_sorted() {
        Node* newNode = createNode();
        int key = newNode->date.get_shifr();

        if (head == nullptr) {
            head = tail = newNode;
            ++size;
            return;
        }

        if (key <= head->date.get_shifr()) {
            newNode->pNext = head;
            head->pPrev = newNode;
            head = newNode;
            ++size;
            return;
        }

        if (key >= tail->date.get_shifr()) {
            newNode->pPrev = tail;
            tail->pNext = newNode;
            tail = newNode;
            ++size;
            return;
        }

        Node* cur = head;
        while (cur->pNext != nullptr && cur->pNext->date.get_shifr() < key)
            cur = cur->pNext;

        Node* nextNode = cur->pNext;
        newNode->pNext = nextNode;
        newNode->pPrev = cur;
        nextNode->pPrev = newNode;
        cur->pNext = newNode;
        ++size;
    }

    void remove_before_second_last() {
        if (size < 3) {
            cout << "\tНевозможно удалить: в списке меньше 3 деталей.\n";
            return;
        }
        Node* to_delete = tail->pPrev->pPrev;

        if (to_delete == head) {
            head = head->pNext;
            if (head) head->pPrev = nullptr;
            else tail = nullptr;
            delete to_delete;
        }
        else {
            to_delete->pPrev->pNext = to_delete->pNext;
            to_delete->pNext->pPrev = to_delete->pPrev;
            delete to_delete;
        }
        --size;
        cout << "\tЭлемент, предшествующий второму с конца, удалён.\n";
    }

    void save_to_file() {
        if (head == nullptr) {
            cout << "\tСписок пуст, нечего сохранять.\n";
            return;
        }
        string path;
        cout << "\tВведите путь к файлу для сохранения: ";
        cin >> path;
        ofstream out(path, ios::trunc);
        if (!out) {
            cout << "\tОшибка открытия файла.\n";
            return;
        }
        Node* cur = head;
        while (cur) {
            out << cur->date.get_shifr() << '\n'
                << cur->date.get_price() << '\n'
                << cur->date.get_ves() << '\n'
                << cur->date.get_name() << "\n\n";
            cur = cur->pNext;
        }
        out.close();
        cout << "\tСписок сохранён в файл: " << path << "\n";
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->pNext;
            delete tmp;
        }
        tail = nullptr;
        size = 0;
    }

    void print() const {
        if (head == nullptr) {
            cout << "\tСписок пуст.\n";
            return;
        }
        cout << "\n\t===== СПИСОК ДЕТАЛЕЙ =====\n";
        Node* cur = head;
        int idx = 1;
        while (cur) {
            cout << "\n\t--- Деталь №" << idx++ << " ---";
            cur->date.print();
            cur = cur->pNext;
        }
        cout << "\n\t==========================\n";
    }
};

#endif