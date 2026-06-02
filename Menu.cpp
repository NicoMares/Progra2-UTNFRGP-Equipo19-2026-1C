#include "Menu.h"
#include <iostream>
#include <locale> 

using namespace std;

Menu::Menu()
{
    
}

void  Menu :: run()
{
   int opcion;

   do
   {
      Mostrar();
      cout<<"Ingresá una opcion: "<<endl;
      cin>>opcion;

      switch (opcion)
      {
         case 1:
            // Lógica para gestionar equipos
            break;
         case 2:
            // Lógica para gestionar jugadores
            break;
         case 3:
            // Lógica para gestionar entrenadores
            break;
         case 4:
            // Lógica para gestionar partidos
            break;
         case 5:
            // Lógica para gestionar acciones
            break;
         case 6:
            // Lógica para mostrar tabla
            break;
         case 0:
            cout<<"Saliendo del programa..."<<endl;
            break;
         default:
            cout<<"Opción no válida. Por favor, ingrese una opción válida."<<endl;
      }

      system("pause");
      system("cls");

   } while (opcion != 0);
}


void  Menu :: Mostrar()
{
setlocale(LC_ALL, "spanish");



cout<<"======================================"<<endl;

cout<<"|    SISTEMA DE LIGA DE FUTBOL  |"<<endl;

cout<<"======================================"<<endl;

cout<<"Menu Principal "<<endl;

cout<<"--------------------------------"<<endl;

cout <<"|     1. Gestion de Equipos        |"<<endl;
cout <<"|     2. Gestion de Jugadores      |"<<endl;
cout <<"|     3. Gestion de Entrenadores   |"<<endl;
cout <<"|     4. Gestion de Partidos       |"<<endl;
cout <<"|     5. Gestion de Acciones       |"<<endl;
cout <<"|     6. Mostrar Tabla             |"<<endl;
cout <<"|     0. Salir                     |"<<endl;

cout<<"--------------------------------"<<endl;

}


