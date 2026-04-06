#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

class Date
{
public:
    Date();
    ~Date();

    int get_shifr() const { return shifr; }
    int get_price() const { return price; }
    int get_ves() const { return ves; }
    string get_name() const { return name; }

    void input_menu() {
        cout << "\n\n\tВыберите способ записи данных:\n"
            << "\t1 - через консоль\n\t2 - из файла\n\t3 - случайный ввод\n"
            << "\tВаш выбор: ";
        int temp;
        cin >> temp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            temp = 0;
        }
        if (temp == 1)
            input();
        else if (temp == 2) {
            string file;
            cout << "\tПуть к файлу: ";
            cin >> file;
            FileToList(file);
        }
        else
            input_random();
    }

    // Генерация случайных положительных значений
    void input_random() {
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned>(time(nullptr)));
            seeded = true;
        }
        shifr = rand() % 9999 + 1;           // 1..9999
        price = rand() % 100 + 1;            // 1..100
        ves = rand() % 9999 + 1;             // 1..9999
        const string names[] = { "Винт","Гайка","Шайба","Болт","Шпилька",
                                "Гровер","Шплинт","Заклёпка","Штифт","Пружина" };
        name = names[rand() % 10] + "_" + to_string(rand() % 1000);
        cout << "\n\tСлучайная деталь: шифр=" << shifr << " цена=" << price
            << " вес=" << ves << " название=" << name << "\n";
    }

    // Ручной ввод с проверками >0 и цена ≤100
    void input() {
        cout << "\n\tВвод данных детали (целые положительные числа):\n";
        // Цена: 1..100
        do {
            cout << "\tЦена (1..100): ";
            if (!(cin >> price)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка. Повторите.\n";
                continue;
            }
            if (price < 1 || price > 100)
                cout << "\tЦена должна быть от 1 до 100.\n";
        } while (price < 1 || price > 100);

        // Шифр > 0
        do {
            cout << "\tШифр (>0): ";
            if (!(cin >> shifr)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка. Повторите.\n";
                continue;
            }
            if (shifr <= 0)
                cout << "\tШифр должен быть положительным.\n";
        } while (shifr <= 0);

        // Вес > 0
        do {
            cout << "\tВес (>0): ";
            if (!(cin >> ves)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка. Повторите.\n";
                continue;
            }
            if (ves <= 0)
                cout << "\tВес должен быть положительным.\n";
        } while (ves <= 0);

        cout << "\tНаименование: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        if (name.empty()) name = "Без названия";
    }

    // Чтение из файла: если значение ≤0, заменяем на 1
    void FileToList(string& path) {
        ifstream file(path);
        if (!file) {
            cout << "\tНе удалось открыть файл\n";
            return;
        }
        file >> shifr >> price >> ves;
        // Проверка и коррекция
        if (shifr <= 0) shifr = 1;
        if (price <= 0) price = 1;
        else if (price > 100) price = 100;
        if (ves <= 0) ves = 1;

        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, name);
        if (file.fail()) {
            cout << "\tОшибка чтения, установлены значения по умолчанию\n";
            shifr = 1; price = 1; ves = 1; name = "Без названия";
        }
        file.close();
        cout << "\tДеталь загружена из файла.\n";
    }

    // Запись в файл (простой формат, без меток)
    void ListToFile(string& path) const {
        ofstream file(path, ios::app);
        if (!file) {
            cout << "\tНе удалось открыть файл для записи\n";
            return;
        }
        file << shifr << '\n' << price << '\n' << ves << '\n' << name << "\n\n";
        file.close();
    }

    // Редактирование с проверками
    bool correction() {
        cout << "\n\tЧто изменить?\n\t1-Цена 2-Шифр 3-Вес 4-Наименование (5-назад)\n\t";
        int ch;
        cin >> ch;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        switch (ch) {
        case 1:
            do {
                cout << "\tНовая цена (1..100): ";
                if (!(cin >> price)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tОшибка.\n";
                    continue;
                }
                if (price < 1 || price > 100)
                    cout << "\tЦена должна быть от 1 до 100.\n";
            } while (price < 1 || price > 100);
            break;
        case 2:
            do {
                cout << "\tНовый шифр (>0): ";
                if (!(cin >> shifr)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tОшибка.\n";
                    continue;
                }
                if (shifr <= 0)
                    cout << "\tШифр должен быть положительным.\n";
            } while (shifr <= 0);
            break;
        case 3:
            do {
                cout << "\tНовый вес (>0): ";
                if (!(cin >> ves)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tОшибка.\n";
                    continue;
                }
                if (ves <= 0)
                    cout << "\tВес должен быть положительным.\n";
            } while (ves <= 0);
            break;
        case 4:
            cout << "\tНовое наименование: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            if (name.empty()) name = "Без названия";
            break;
        default:
            return false;
        }
        return true;
    }

    void print() const {
        cout << "\n\tШифр: " << shifr << "\n\tЦена: " << price
            << "\n\tВес: " << ves << "\n\tНаименование: " << name;
    }

private:
    int shifr;
    int price;
    int ves;
    string name;
};

Date::Date() : shifr(1), price(1), ves(1), name("") {}
Date::~Date() {}

#endif