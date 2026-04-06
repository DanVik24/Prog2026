#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;
class Date
{
public:
	Date();
	~Date();
	int get_shifr() { return shifr; }
	void input_menu() {
		cout << "\n\n\tВыберите способ записи данных в элемент списка:"
			<< "\n\t1 - через консоль\n\t2 - из файла\n\tдругое - случайный ввод"
			<< "\n\tВаш выбор: ";
		int temp; cin >> temp;
		if (temp == 1) { input(); }
		else if (temp == 2) {
			cout << "\tВ файле должна содержаться запись вида: "
				<<"\n\tВведите путь к файлу вида: С:\\foulder\\text.txt \n\t";
			string file; cin >> file;
			FileToList(file);
		}
		else {
			input_random();
		}
	}
	void input_random() {
		
	}
	void input() {
		cout << "\n\tВведите данные детали:\n";
		cout << "\tЦена:\t\t";cin >> this->price;
		cout << "\tШифр:\t\t"; cin >> this->shifr;
		cout << "\tВес:\t\t"; cin >> this->ves;
		cout << "\tНаименование:\t"; cin >> this->name;
	}

	void FileToList(string& filePath) { /*из файла в список!*/
		ifstream file(filePath); // Открытие файла для чтения
		if (!file.is_open()) {
			cout << "Не удалось открыть файл для чтения: " << filePath << endl;
			return;
		}

		// Предполагаем, что строки в файле идут в порядке объявленных полей для простоты
		file >> shifr;
		file >> price;
		file >> ves;
		file.ignore(); // Игнорируем символ новой строки перед чтением имени
		getline(file, name);
		file.close();
	}
	void ListToFile(string& filePath) { /*из списка в файл*/
		ofstream file(filePath, ios::app);// Режим добавления данных
		if (!file.is_open()) {
			cout << "Не удалось открыть файл для записи: " << filePath << endl;
			return;
		}

		file << shifr << endl;
		file << price << endl;
		file << ves << endl;
		file << name << endl << endl;

		file.close();
	}		//ввод из файла
	

	bool correction() {
		cout << "\n\tВыберите параметр детали для изменения: "
			<< "\n\t1 - Цена\n\t2 -Шифр"
			<< "\n\t3 - Вес\n\t4 - Наименование"
			<<"\n\tДругое - назад";
		int temp; cin >> temp;
		if (temp > 0 && temp < 5) {
			cout << "\n\tВведите данные детали:\n";
		}
		switch (temp)
		{
		case 1:
			cout << "\tЦена:\t\t"; cin >> this->price;
			break;
		case 2:
			cout << "\tШифр:\t\t"; cin >> this->shifr;
			break;
		case 3:
			cout << "\tВес:\t\t"; cin >> this->ves;
			break;
		case 4:
			cout << "\tНаименование:\t"; cin >> this->name;
			break;
		default:
			return false; //данные не изменены
			break;
		}
		return true; //данные изменены
	}
	void print() {
		cout << "\n\n\tДанные детали:";
		cout << "\n\tЦена\t\t" << this->price;
		cout << "\n\tШифр\t\t"<<this->shifr; 
		cout << "\n\tВес\t\t"<<this->ves;
		cout << "\n\tНазвание\t"<<this->name;
	}
	

private:
	//Шифр детали, наименование, расценка, вес
	int shifr = 0;
	double price;
	double ves;
	string name;
};

Date::Date()
{
	this->shifr = 0;
	input_menu();
}

Date::~Date()
{
}
