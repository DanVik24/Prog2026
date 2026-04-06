#include "Node.h" //подрубаем узел списка
using namespace std;

class DoubleList
{
public:
	DoubleList(); // конструктор
	~DoubleList(); // деструктор

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
			cout << temp;
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
	Node* head;	//указатель на голову
	Node* tail;	//указатель на хвост
	int size;	//кол-во элементов

	void add_front() {	/*добавление в начало*/
		if (this->head == nullptr) 
		{
			this->head = new Node();
			this->tail = head;			
		}
		else
		{
			Node* current = this->head;
			this->head = new Node(current,nullptr);
			current->pPrev = head;
		}
		this->size++;
	}

	void add_back() {		/*добавление в конец*/
		if (this->head == nullptr) 
		{
			this->add_front();
		}
		else 
		{
			Node* current = this->tail;
			current->pNext = new Node(nullptr, current);
			this->tail = current->pNext;
			this->size++;
		}
	};

	Node* find_key(int key) {
		/*если шифр детали больше половины кол-ва элементов значит
		начинаем поиск с конца иначе с начала*/
		if (this->size == 0) { return nullptr; }
		Node* current;
		if (key > this->size / 2) {
			current = this->tail;
			while (current->date.get_shifr() != key && current != head) {
				current = current->pPrev;
			}
		}
		else {
			current = this->head;
			while (current->date.get_shifr() != key && current != tail) {
				current = current->pNext;
			}
		}
		return current;
	}
	void add_key() {		/*добавление по ключу*/
		/*если узел в таким ключём существует то на выбор: 
		изменяем существующий/вставляем перед/вставляем после
		по заданию ключ-поле это шифр детали*/
		int key; cout << "\n\tВведите ключ-поле (шифр детали): "; cin >> key;
		Node* current = find_key(key);

		bool tr_key = false; //проверка равны ли ключи
		if (current != nullptr) { //если элемент найден
			if (current->date.get_shifr() == key) { //если ключи равны
				cout << "\n\tДеталь с таким шифром существует!"
					<< "\n\tВыберите действия:\n\t1 - изменить данные"
					<< "\n\t2 - вставить перед \n\t3 - вставить после ";
				tr_key = true;
			}
		}
		if (current == nullptr || tr_key == false) //если элемент не найден или ключи не совпали
		{
			cout << "\n\tДеталь с таким шифром не существует!"
				<< "\n\tВыберите действия:"
				<< "\n\t2 - вставить в начало \n\t3 - вставить в конец";
		}
		cout << "\n\tдругое - назад\n\tВаш выбор: ";
		
		int temp; cin >> temp;
		switch (temp)
		{case 1:
			if (tr_key) { current->date.correction(); }
			break;
		case 2:
			if (tr_key) { add_after(current); } else {add_front(); }//перед либо в начало
			break;
		case 3:
			if (tr_key) { add_before(current); } else {add_back(); } //после либо в конец
			break;
		default:
			cout << "\tЭлемент не добавлен!";
			return;
			break;
		}
	};
	void add_before(Node* current) {
		if (current == nullptr) return; // Ничего не делаем, если указатель невалиден
		if (current->pNext != nullptr) {
			Node* newNode = new Node(current->pNext, current);
			current->pNext->pPrev = newNode;
			current->pNext = newNode;
			size++;
		}
		else {
			add_back(); // если после current ничего нет, обновляем хвост
		}
	}
	void add_after(Node* current) {
		if (current == nullptr) return; // Ничего не делаем, если указатель невалиден
		if (current->pPrev != nullptr) {
			Node* newNode = new Node(current, current->pPrev);
			current->pPrev->pNext = newNode;
			current->pPrev = newNode;
			size++;
		}
		else {
			add_front(); // если перед current ничего нет, обновляем голову
		}
	}

	void remove_front() {	/*удаление первого*/
		if (this->head == nullptr) {
			cout << "\n\tСписок пуст. Нет элементов для удаления.\n";
			return;
		}

		Node* current = this->head;

		if (current->pNext != nullptr) {
			this->head = current->pNext;
			this->head->pPrev = nullptr;
		}
		else {
			// Единственный элемент в списке
			this->head = nullptr;
			this->tail = nullptr;
		}
		delete current;
		this->size--;
		cout << "\n\tПервый элемент успешно удален.\n";
	};
	void remove_back() {	/*удаление последнего*/
		if (this->tail == nullptr) {
			cout << "\n\tСписок пуст. Нет элементов для удаления.\n";
			return;
		}
		Node* current = this->tail;
		if (current->pPrev != nullptr) {
			this->tail = current->pPrev;
			this->tail->pNext = nullptr;
		}
		else {
			// Единственный элемент в списке
			this->head = nullptr;
			this->tail = nullptr;
		}
		delete current;
		this->size--;
		cout << "\n\tПоследний элемент успешно удален.\n";
	};
	void remove_key() {	/*удаление по ключу*/
		int key; cout << "\n\tВведите ключ-поле (шифр детали): "; cin >> key;
		Node* current = find_key(key);
		if (current == nullptr) { 
			cout << "\n\tЭлемент с ключом " << key << " не найден.\n"; return;}
		//теперь нужно удалить текущий элемент из списка
		if (current->pPrev == nullptr) { remove_front(); }
		else if (current->pNext == nullptr) { remove_back(); }
		else {
			current->pPrev->pNext = current->pNext;
			current->pNext->pPrev = current->pPrev;
			delete current;
			size--;
		}
		cout << "\n\tЭлемент с ключом " << key << " успешно удален.\n";
	};
	void clear() { /*чистка всех*/
		while (this->size != 0) {
			remove_back();
		}
	};			
	
	void print() {		/*вывод на консоль*/
		cout << "\n\tВыберите: \n\t0 - Вывод данных об элементах в файл"
			<< "\n\t другое - вывод всех элементов списка\n\tВаш ответ: ";
		int temp; cin >> temp;
		if (!temp) {
			cout << "\tВведите путь к файлу вида: С:\\foulder\\text.txt \n\t";
			string file; cin >> file;
			Node* current = this->head;
			while (current != nullptr) {
				current->date.ListToFile(file);
				current = current->pNext;
			}
		}
		else if (this->head == nullptr) {
			cout << "\n\tСписок пуст!";
		}
		else {
			Node* current = this->head;
			while (current != nullptr) {
				current->date.print();
				current = current->pNext;
			}
		}
	}
	int get_size() { return this->size; }
};

DoubleList::DoubleList() //определяет где находится объект
{
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}
DoubleList::~DoubleList()
{
	this->clear();
}
