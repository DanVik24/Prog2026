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

    void input_random() {
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned>(time(nullptr)));
            seeded = true;
        }
        shifr = rand() % 9999 + 1;          // 1..9999
        price = rand() % 101;               // 0..100
        ves = rand() % 10000;               // 0..9999
        const string names[] = { "Винт","Гайка","Шайба","Болт","Шпилька",
                                "Гровер","Шплинт","Заклёпка","Штифт","Пружина" };
        name = names[rand() % 10] + "_" + to_string(rand() % 1000);
        cout << "\n\tСлучайная деталь: шифр=" << shifr << " цена=" << price
            << " вес=" << ves << " название=" << name << "\n";
    }

    void input() {
        cout << "\n\tВвод данных детали (только целые числа):\n";
        do {
            cout << "\tЦена (0..100): ";
            if (!(cin >> price)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка. Повторите.\n";
                continue;
            }
            if (price < 0 || price > 100)
                cout << "\tЦена должна быть от 0 до 100.\n";
        } while (price < 0 || price > 100);

        cout << "\tШифр (целое): ";
        while (!(cin >> shifr)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tОшибка. Повторите: ";
        }

        cout << "\tВес (целое): ";
        while (!(cin >> ves)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tОшибка. Повторите: ";
        }

        cout << "\tНаименование: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        if (name.empty()) name = "Без названия";
    }

    void FileToList(string& path) {
        ifstream file(path);
        if (!file) {
            cout << "\tНе удалось открыть файл\n";
            return;
        }
        file >> shifr >> price >> ves;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, name);
        if (file.fail()) {
            cout << "\tОшибка чтения, установлены значения по умолчанию\n";
            shifr = 0; price = 0; ves = 0; name = "";
        }
        else {
            if (price < 0) price = 0;
            if (price > 100) {
                cout << "\tЦена в файле >100, установлено 100\n";
                price = 100;
            }
        }
        file.close();
    }

    void ListToFile(string& path) const {
        ofstream file(path, ios::app);
        if (!file) {
            cout << "\tНе удалось открыть файл для записи\n";
            return;
        }
        file << shifr << '\n' << price << '\n' << ves << '\n' << name << "\n\n";
        file.close();
    }

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
                cout << "\tНовая цена (0..100): ";
                if (!(cin >> price)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tОшибка.\n";
                    continue;
                }
                if (price < 0 || price > 100)
                    cout << "\tЦена должна быть от 0 до 100.\n";
            } while (price < 0 || price > 100);
            break;
        case 2:
            cout << "\tНовый шифр: ";
            while (!(cin >> shifr)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка: ";
            }
            break;
        case 3:
            cout << "\tНовый вес: ";
            while (!(cin >> ves)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tОшибка: ";
            }
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

Date::Date() : shifr(0), price(0), ves(0), name("") {}
Date::~Date() {}

#endif