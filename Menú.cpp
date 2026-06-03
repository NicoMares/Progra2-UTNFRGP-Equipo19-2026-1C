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
            menuEquipos();
            break;
        case 2:
            menuJugadores();
            break;
        case 3:
            menuEntrenadores();
            break;
        case 4:
            menuPartidos();
            break;
        case 5:
            menuAcciones();
            break;
        case 6:
            menuTabla();
            break;
        case 0:
            cout<<"Saliendo del programa..."<<endl;
            break;
        default:
            cout<<"Opción no válida. Por favor, ingrese una opción válida."<<endl;
        }

        system("pause");
        system("cls");

    }
    while (opcion != 0);
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

void Menu::menuEquipos()
{
    int op;

    do
    {
        system("cls");

        cout << "=======================================" << endl;
        cout << "|          GESTION DE EQUIPOS         |" << endl;
        cout << "=======================================" << endl;
        cout << "| 1. Cargar Equipo                    |" << endl;
        cout << "| 2. Consulta por ID de Club          |" << endl;
        cout << "| 3. Listado de Clubes                |" << endl;
        cout << "| 4. Racha (Ultimos 5 Partidos.)      |" << endl;
        cout << "| 0. Volver al Menú Principal         |" << endl;
        cout << "=======================================" << endl;
        cout << "Ingresá una opción: " << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            cout << "\nAbriendo: Cargar Equipo... \n" << endl;
            system("pause");
            break;
        case 2:
            cout << "\nAbriendo: Consulta por ID de Club... \n" << endl;
            system("pause");
            break;
        case 3:
            cout << "\nAbriendo: Listado de Clubes... \n" << endl;
            system("pause");
            break;
        case 4:
            cout << "\nAbriendo: Racha... \n" << endl;
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "\nOpción no válida. Por favor, intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);
}

void Menu::menuJugadores()
{
   int op;

   do
   {
      system("cls");

      cout << "==========================================================" << endl;
      cout << "|                    GESTION DE JUGADORES                |" << endl;
      cout << "==========================================================" << endl;
      cout << "| 1. Cargar Jugador                                      |" << endl;
      cout << "| 2. Consulta por DNI                                    |" << endl;
      cout << "| 3. Consulta por Posicion                               |" << endl;
      cout << "| 4. Listar Jugadores ordenados por DNI                  |" << endl;
      cout << "| 5. Listar Jugadores agrupados por Club                 |" << endl;
      cout << "| 6. Listar Jugadores clasificados por Posicion          |" << endl;
      cout << "|                                                        |" << endl;
      cout << "| 0. Volver al Menu Principal                            |" << endl;
      cout << "==========================================================" << endl;
      cout << " Selecciona una opcion: ";
      cin >> op;

      switch (op)
      {
         case 1:
            cout << "\n[Accion] Cargar Jugador...\n" << endl;
            system("pause");
            break;
         case 2:
            cout << "\n[Accion] Consulta por DNI...\n" << endl;
            system("pause");
            break;
         case 3:
            cout << "\n[Accion] Consulta por Posicion...\n" << endl;
            system("pause");
            break;
         case 4:
            cout << "\n[Accion] Listar Jugadores ordenados por DNI...)\n" << endl;
            system("pause");
            break;
         case 5:
            cout << "\n[Accion] Listar Jugadores agrupados por Club...\n" << endl;
            system("pause");
            break;
         case 6:
            cout << "\n[Accion] Listar Jugadores clasificados por Posicion...\n" << endl;
            system("pause");
            break;
         case 0:
            break;
         default:
            cout << "\nOpcion incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
      }

   } while (op != 0);
}

void Menu::menuEntrenadores()
{
    int op;

   do
   {
      system("cls");

      cout << "==========================================================" << endl;
      cout << "|                  GESTION DE ENTRENADORES               |" << endl;
      cout << "==========================================================" << endl;
      cout << "| 1. Cargar Entrenador                                   |" << endl;
      cout << "| 2. Consulta por ID de Entrenador                       |" << endl;
      cout << "| 3. Listar todos los Entrenadores                       |" << endl;
      cout << "|                                                        |" << endl;
      cout << "| 0. Volver al Menu Principal                            |" << endl;
      cout << "==========================================================" << endl;
      cout << " Selecciona una opcion: ";
      cin >> op;

      switch (op)
      {
         case 1:
            cout << "\n[Accion] Cargar Entrenador...\n" << endl;
            system("pause");
            break;
         case 2:
            cout << "\n[Accion] Consulta por ID de Entrenador...\n" << endl;
            system("pause");
            break;
         case 3:
            cout << "\n[Accion] Listar todos los Entrenadores...\n" << endl;
            system("pause");
            break;
         case 0:
            break;
         default:
            cout << "\nOpcion incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
      }

   } while (op != 0);
}
void Menu::menuPartidos()
{
   int op;

   do
   {
      system("cls");

      cout << "==========================================================" << endl;
      cout << "|                    GESTION DE PARTIDOS                 |" << endl;
      cout << "==========================================================" << endl;
      cout << "| 1. Cargar Partido                                      |" << endl;
      cout << "| 2. Consultar Partido por ID                            |" << endl;
      cout << "| 3. Listar todos los Partidos del Torneo                |" << endl;
      cout << "|                                                        |" << endl;
      cout << "| 0. Volver al Menu Principal                            |" << endl;
      cout << "==========================================================" << endl;
      cout << " Selecciona una opcion: ";
      cin >> op;

      switch (op)
      {
         case 1:
            cout << "\n[Accion] Cargar Partido...\n" << endl;
            system("pause");
            break;
         case 2:
            cout << "\n[Accion] Consultar Partido...\n" << endl;
            system("pause");
            break;
         case 3:
            cout << "\n[Accion] Listar todos los Partidos...\n" << endl;
            system("pause");
            break;
         case 0:
            break;
         default:
            cout << "\nOpcion incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
      }

   } while (op != 0);


}

void Menu::menuAcciones(){}

void Menu::menuTabla()
{
   int op;

   do
   {
      system("cls");

      cout << "==========================================================" << endl;
      cout << "|                  TABLAS Y ESTADISTICAS                 |" << endl;
      cout << "==========================================================" << endl;
      cout << "| 1. Mostrar Tabla de Posiciones Completa                 |" << endl;
      cout << "| 2. Goleadores del Torneo (Top Scorers)                 |" << endl;
      cout << "|                                                        |" << endl;
      cout << "| 0. Volver al Menu Principal                            |" << endl;
      cout << "==========================================================" << endl;
      cout << " Selecciona una opcion: ";
      cin >> op;

      switch (op)
      {
         case 1:
            cout << "\n[Accion] Generando Tabla de Posiciones...\n" << endl;
            system("pause");
            break;
         case 2:
            cout << "\n[Accion] Buscando Goleadores...\n" << endl;
            system("pause");
            break;
         case 0:
            break;
         default:
            cout << "\nOpcion incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
      }

   } while (op != 0);
}



