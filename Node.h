#ifndef NODE_H
#define NODE_H

#include "Date.h"

class DoubleList; // предварительное объявление для friend

class Node
{
    friend class DoubleList; // разрешаем DoubleList доступ к приватным полям

public:
    // Конструкторы
    Node() : pNext(nullptr), pPrev(nullptr) {}
    Node(Node* next, Node* prev) : pNext(next), pPrev(prev) {}
    ~Node() {}

    // Геттеры (опционально, для безопасного чтения полей)
    Node* getNext() const { return pNext; }
    Node* getPrev() const { return pPrev; }
    Date& getDate() { return date; }
    const Date& getDate() const { return date; }

private:
    Node* pNext;   // указатель на следующий узел
    Node* pPrev;   // указатель на предыдущий узел
    Date date;     // данные (объект класса Date)
};

#endif // NODE_H