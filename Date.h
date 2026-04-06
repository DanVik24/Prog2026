#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>   // для numeric_limits

using namespace std;

class Date
{
public:
    // Конструктор: инициализация всех полей значениями по умолчанию
    Date();
    ~Date();

    int get_shifr() const { return shifr; }

    // Метод выбора способа ввода (теперь не вызывается из конструктора)
    void input_menu() {
        cout << "\n\n\tВыберите способ записи данных в элемент списка:"
            << "\n\t1 - через консоль\n\t2 - из файла\n\tдругое - случайный ввод"
            << "\n\tВаш выбор: ";
        int temp;
        cin >> temp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            temp = 0;
        }
        if (temp == 1) {
            input();
        }
        else if (temp == 2) {
            cout << "\tВ файле должна содержаться запись вида: "
                << "\n\tВведите путь к файлу вида: С:\\folder\\text.txt \n\t";
            string file;
            cin >> file;
            FileToList(file);
        }
        else {
            input_random();
        }
    }

    void input_random() {
        // Можно реализовать генерацию случайных значений
        // Пока оставим заглушкой
        cout << "\tСлучайный ввод не реализован.\n";
    }

    void input() {
        cout << "\n\tВведите данные детали:\n";

        cout << "\tЦена:\t\t";
        if (!(cin >> price)) {
            cout << "\tОшибка ввода цены. Установлено значение 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            price = 0.0;
        }

        cout << "\tШифр:\t\t";
        if (!(cin >> shifr)) {
            cout << "\tОшибка ввода шифра. Установлено значение 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            shifr = 0;
        }

        cout << "\tВес:\t\t";
        if (!(cin >> ves)) {
            cout << "\tОшибка ввода веса. Установлено значение 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ves = 0.0;
        }

        cout << "\tНаименование:\t";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        if (name.empty()) name = "Без названия";
    }

    void FileToList(string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для чтения: " << filePath << endl;
            return;
        }

        // Чтение полей: шифр, цена, вес, затем строка наименования
        file >> shifr >> price >> ves;
        // Пропускаем все оставшиеся символы до конца строки перед чтением названия
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, name);

        // Проверка, что чтение прошло успешно
        if (file.fail()) {
            cout << "Ошибка чтения данных из файла. Установлены значения по умолчанию.\n";
            shifr = 0;
            price = 0.0;
            ves = 0.0;
            name = "";
        }

        file.close();
    }

    void ListToFile(string& filePath) const {
        ofstream file(filePath, ios::app);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для записи: " << filePath << endl;
            return;
        }

        file << shifr << endl;
        file << price << endl;
        file << ves << endl;
        file << name << endl << endl;

        file.close();
    }

    bool correction() {
        cout << "\n\tВыберите параметр детали для изменения: "
            << "\n\t1 - Цена\n\t2 - Шифр"
            << "\n\t3 - Вес\n\t4 - Наименование"
            << "\n\tДругое - назад";
        int temp;
        cin >> temp;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        if (temp > 0 && temp < 5) {
            cout << "\n\tВведите новые данные:\n";
        }

        switch (temp) {
        case 1:
            cout << "\tЦена:\t\t";
            if (!(cin >> price)) {
                cout << "\tОшибка, цена не изменена.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 2:
            cout << "\tШифр:\t\t";
            if (!(cin >> shifr)) {
                cout << "\tОшибка, шифр не изменён.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 3:
            cout << "\tВес:\t\t";
            if (!(cin >> ves)) {
                cout << "\tОшибка, вес не изменён.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        case 4:
            cout << "\tНаименование:\t";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            break;
        default:
            return false;
        }
        return true;
    }

    void print() const {
        cout << "\n\n\tДанные детали:";
        cout << "\n\tЦена\t\t" << price;
        cout << "\n\tШифр\t\t" << shifr;
        cout << "\n\tВес\t\t" << ves;
        cout << "\n\tНазвание\t" << name;
    }

private:
    int shifr;
    double price;
    double ves;
    string name;
};

// Реализация конструктора и деструктора
Date::Date()
    : shifr(0), price(0.0), ves(0.0), name("")
{
    // Конструктор только инициализирует поля, не вызывает ввод
}

Date::~Date()
{
    // Ничего не требуется
}

#endif // DATE_H