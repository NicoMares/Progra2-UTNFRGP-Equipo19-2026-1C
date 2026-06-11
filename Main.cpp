#include <iostream>
#include "Menu.h"
#include <locale.h>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
   setlocale(LC_ALL, " ");
    system("cls");

    Menu menu;
    menu.run();



    return 0;
}
