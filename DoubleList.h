#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>
#include <string>
#include <limits>
#include "Node.h"   // предполагается, что Node.h корректен

using namespace std; // для краткости, но лучше избегать в заголовках

class DoubleList
{
public:
    DoubleList();
    ~DoubleList();

    void menu() {
        int temp;
        do {
            cout << "\n\n\tВыберите действие:\n";
            cout << "\t1. Добавить в начало\n";
            cout << "\t2. Добавить в конец\n";
            cout << "\t3. Добавить по ключу\n";
            cout << "\t4. Удалить первый элемент\n";
            cout << "\t5. Удалить последний элемент\n";
            cout << "\t6. Удалить по ключу\n";
            cout << "\t7. Очистить\n";
            cout << "\t8. Вывести на консоль\n";
            cout << "\t9. Получить количество элементов\n";
            cout << "\t0. Выход\n";
            cout << "\tВаш выбор: ";
            cin >> temp;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                temp = -1;
            }
            switch (temp) {
            case 1: add_front(); break;
            case 2: add_back(); break;
            case 3: add_key(); break;
            case 4: remove_front(); break;
            case 5: remove_back(); break;
            case 6: remove_key(); break;
            case 7: clear(); break;
            case 8: print(); break;
            case 9: cout << "\tКоличество элементов: " << get_size() << "\n"; break;
            case 0: cout << "\tВыход из программы.\n"; break;
            default: cout << "\tНеверный выбор. Пожалуйста, попробуйте снова.\n"; break;
            }
        } while (temp != 0);
    }

private:
    Node* head;
    Node* tail;
    int size;

    // Добавление в начало
    void add_front() {
        Node* newNode = new Node();
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->pNext = head;
            head->pPrev = newNode;
            head = newNode;
        }
        ++size;
    }

    // Добавление в конец
    void add_back() {
        if (head == nullptr) {
            add_front();
            return;
        }
        Node* newNode = new Node();
        newNode->pPrev = tail;
        tail->pNext = newNode;
        tail = newNode;
        ++size;
    }

    // Поиск узла по шифру (линейный поиск)
    Node* find_key(int key) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->date.get_shifr() == key)
                return current;
            current = current->pNext;
        }
        return nullptr;
    }

    // Вставка узла ПЕРЕД заданным узлом current
    void add_before(Node* current) {
        if (current == nullptr) return;
        Node* newNode = new Node();
        newNode->pPrev = current->pPrev;
        newNode->pNext = current;
        if (current->pPrev != nullptr)
            current->pPrev->pNext = newNode;
        else
            head = newNode;   // вставка перед головой
        current->pPrev = newNode;
        ++size;
    }

    // Вставка узла ПОСЛЕ заданного узла current
    void add_after(Node* current) {
        if (current == nullptr) return;
        Node* newNode = new Node();
        newNode->pNext = current->pNext;
        newNode->pPrev = current;
        if (current->pNext != nullptr)
            current->pNext->pPrev = newNode;
        else
            tail = newNode;   // вставка после хвоста
        current->pNext = newNode;
        ++size;
    }

    // Добавление по ключу (шифру)
    void add_key() {
        int key;
        cout << "\n\tВведите ключ-поле (шифр детали): ";
        cin >> key;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tОшибка ввода ключа.\n";
            return;
        }

        Node* current = find_key(key);
        bool found = (current != nullptr);

        if (found) {
            cout << "\n\tДеталь с таким шифром существует!"
                << "\n\tВыберите действия:\n\t1 - изменить данные"
                << "\n\t2 - вставить перед \n\t3 - вставить после ";
        }
        else {
            cout << "\n\tДеталь с таким шифром не существует!"
                << "\n\tВыберите действия:"
                << "\n\t2 - вставить в начало \n\t3 - вставить в конец";
        }
        cout << "\n\tдругое - назад\n\tВаш выбор: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        switch (choice) {
        case 1:
            if (found)
                current->date.correction();
            break;
        case 2:
            if (found)
                add_before(current);   // вставить перед существующим
            else
                add_front();           // вставить в начало
            break;
        case 3:
            if (found)
                add_after(current);    // вставить после существующего
            else
                add_back();            // вставить в конец
            break;
        default:
            cout << "\tЭлемент не добавлен!\n";
            break;
        }
    }

    // Удаление первого элемента
    void remove_front() {
        if (head == nullptr) {
            cout << "\n\tСписок пуст. Нет элементов для удаления.\n";
            return;
        }
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->pNext;
            head->pPrev = nullptr;
        }
        delete temp;
        --size;
        cout << "\n\tПервый элемент успешно удален.\n";
    }

    // Удаление последнего элемента
    void remove_back() {
        if (tail == nullptr) {
            cout << "\n\tСписок пуст. Нет элементов для удаления.\n";
            return;
        }
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->pPrev;
            tail->pNext = nullptr;
        }
        delete temp;
        --size;
        cout << "\n\tПоследний элемент успешно удален.\n";
    }

    // Удаление по ключу (шифру)
    void remove_key() {
        int key;
        cout << "\n\tВведите ключ-поле (шифр детали): ";
        cin >> key;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tОшибка ввода ключа.\n";
            return;
        }

        Node* current = find_key(key);
        if (current == nullptr) {
            cout << "\n\tЭлемент с ключом " << key << " не найден.\n";
            return;
        }

        // Если элемент единственный
        if (head == tail) {
            delete current;
            head = tail = nullptr;
            --size;
            cout << "\n\tЭлемент с ключом " << key << " успешно удален.\n";
            return;
        }

        // Удаление головы
        if (current == head) {
            remove_front();
            return;
        }
        // Удаление хвоста
        if (current == tail) {
            remove_back();
            return;
        }

        // Удаление из середины
        current->pPrev->pNext = current->pNext;
        current->pNext->pPrev = current->pPrev;
        delete current;
        --size;
        cout << "\n\tЭлемент с ключом " << key << " успешно удален.\n";
    }

    // Очистка всего списка
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->pNext;
            delete temp;
        }
        tail = nullptr;
        size = 0;
        cout << "\n\tСписок очищен.\n";
    }

    // Вывод на консоль или в файл
    void print() const {
        cout << "\n\tВыберите: \n\t0 - Вывод данных об элементах в файл"
            << "\n\tдругое - вывод всех элементов списка\n\tВаш ответ: ";
        int temp;
        cin >> temp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            temp = 1;
        }

        if (temp == 0) {
            cout << "\tВведите путь к файлу вида: С:\\folder\\text.txt \n\t";
            string file;
            cin >> file;
            Node* current = head;
            while (current != nullptr) {
                current->date.ListToFile(file);
                current = current->pNext;
            }
            cout << "\tДанные записаны в файл.\n";
        }
        else {
            if (head == nullptr) {
                cout << "\n\tСписок пуст!\n";
            }
            else {
                Node* current = head;
                while (current != nullptr) {
                    current->date.print();
                    current = current->pNext;
                }
            }
        }
    }

    int get_size() const { return size; }
};

// Реализация конструктора и деструктора
DoubleList::DoubleList()
    : head(nullptr), tail(nullptr), size(0)
{
}

DoubleList::~DoubleList()
{
    clear();
}

#endif // DOUBLELIST_H