#define NOMINMAX
#include <iostream>
#include <windows.h>
#include "DoubleList.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    DoubleList list;
    list.menu();
    return 0;
}