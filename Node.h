#include "Date.h" //подрубаем данные узла

// Конкретный элемент кот содержит в себе ссылку на пред элемент списка, на следующий
class Node
{
public:
	Node();
	Node(Node* pNext, Node* pPrev);
	~Node();

	Node* pNext;	//следующий
	Node* pPrev;	//предыдущий
	Date date;

private:
	/*т.к класс Node используется исключительно 
	внутри класса DoubleList, модификатор доступа опустим
	а вообще можно было использовать геттеры и сеттеры*/
};

Node::Node() //создание первого узла
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
}
Node::Node(Node* pNext, Node* pPrev) //создание последующих узлов
{
	this->pNext = pNext;
	this->pPrev = pPrev;
}

Node::~Node()
{
}
