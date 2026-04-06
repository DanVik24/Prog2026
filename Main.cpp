#define NOMINMAX  // запрещает определение макросов min/max в windows.h
#include <iostream>
#include <windows.h>
#include "DoubleList.h" //подрубаем список

using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	DoubleList One; //объявление списка
	One.menu();
return 0;
}
