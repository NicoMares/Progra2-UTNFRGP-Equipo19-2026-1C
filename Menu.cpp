#include "Menu.h"
#include <iostream>
#include <locale>
#include "Club.h"
#include "Jugador.h"
#include "Entrenador.h"


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
        cout<<"Ingres� una opción: "<<endl;
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
            cout<<"Opci�n no v�lida. Por favor, ingrese una opci�n v�lida."<<endl;
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

    setlocale(LC_ALL, "spanish");
    do
    {
        system("cls");

        cout << "=======================================" << endl;
        cout << "|          GESTION DE EQUIPOS         |" << endl;
        cout << "=======================================" << endl;
        cout << "| 1. Cargar Equipo                    |" << endl;
        cout << "| 2. Consulta por ID de Club          |" << endl;
        cout << "| 3. Listado de Clubes                |" << endl;
        cout << "| 0. Volver al Men� Principal         |" << endl;
        cout << "=======================================" << endl;
        cout << "Ingres� una opci�n: " << endl;
        cin >> op;

        switch (op)
        {
        case 1:
        {
            cout << "\n[Accion] Cargar Equipo... \n" << endl;
            Club equipo;
            equipo.cargar();
            equipo.grabarEnDisco();
            system("pause");
        }
        break;
        case 2:
        {
            cout << "\n[Accion] Consulta por ID de Club... \n" << endl;
           Club equipo;
           equipo.mostrarPorID();
       
           
            system("pause");
             }
             break;
           
        case 3:
        {
            cout << "\n[Accion] Listado de Clubes... \n" << endl;
            Club equipo;
            int pos = 0;

            while (equipo.leerDeDisco(pos))
            {
                equipo.mostrar();
                cout << endl;
                pos++;
            }

            system("pause");
        }
            break;
        case 4:
            cout << "\n[Accion] Racha... \n" << endl;
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "\nOpci�n no v�lida. Por favor, intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);
}

void Menu::menuJugadores()
{
    int op;

    setlocale(LC_ALL, "spanish");
    do
    {
        system("cls");

        cout << "==========================================================" << endl;
        cout << "|                    GESTION DE JUGADORES                |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Cargar Jugador                                      |" << endl;
        cout << "| 2. Consulta por DNI                                    |" << endl;
        cout << "| 3. Consulta por Posición                               |" << endl;
        cout << "| 4. Listar Jugadores ordenados por DNI                  |" << endl;
        cout << "| 5. Listar Jugadores agrupados por Club                 |" << endl;
        cout << "| 6. Mostrar Todos Los Jugadores De La Liga          |" << endl;
        cout << "|                                                        |" << endl;
        cout << "| 0. Volver al Menu Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << " Selecciona una opción: ";
        cin >> op;

        switch (op)
        {
        case 1:
        {
            cout << "\n[Accion] Cargar Jugador...\n" << endl;
            Jugador jugador;
            jugador.cargar();
            jugador.grabarEnDisco();
            system("pause");
        }
        break;

        case 2:
        {
            cout << "\n[Accion] Consulta por DNI...\n" << endl;
            
            Jugador jugador;
            jugador.ConsultarPorDNI();
        
            system("pause");
            break;
            }
        case 3:
        {
            cout << "\n[Accion] Consulta por Posición...\n" << endl;
           
            Jugador jugador;
            jugador.consultarPorPosicion();
            
            system("pause");
            }
            break;
        case 4:
        {
            cout << "\n[Accion] Listar Jugadores ordenados por DNI...)\n" << endl;
            Jugador jugador;
            int pos = 0;

            while (jugador.leerDeDisco(pos))
            {
                jugador.mostrar();
                cout << endl;
                pos++;
            }

            system("pause");
        }
            break;
        case 5:
        {
            cout << "\n[Accion] Listar Jugadores agrupados por Club...\n" << endl;
            
            Jugador jugador;
            jugador.listarPorClub();
            
            
            system("pause");
            }
            break;
        case 6:
        {
            cout << "\n[Accion] Mostrar Todos Los Jugadores De La Liga...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            Jugador jugador;
            jugador.TodosJugadores();
            
            system("pause");
        }
            break;
        case 0:
            break;
        default:
            cout << "\nOpción incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);
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
        cout << " Selecciona una opción: ";
        cin >> op;

        switch (op)
        {
        case 1:
        {
            cout << "\n[Accion] Cargar Entrenador...\n" << endl;
            Entrenador entrenador;
            entrenador.cargar();
            entrenador.grabarEnDisco();
            system("pause");
        }
        break;
        case 2:
            {
            cout << "\n[Accion] Consulta por ID de Entrenador...\n" << endl;
               cout<< "-------------------------------------------------------------"<<endl;
            
               Entrenador entrenador;
            entrenador.mostrarDTPorID();
            
            system("pause");
            }
            break;
        case 3:
        {
            cout << "\n[Accion] Listar todos los Entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            Entrenador entrenador;
            int pos = 0;

            while (entrenador.leerDisco(pos))
            {
                entrenador.mostrar();
                cout << endl;
                pos++;
            }

            system("pause");
        }
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);
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
        cout << " Selecciona una opción: ";
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
            cout << "\nOpción incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);


}

void Menu::menuAcciones() {}

void Menu::menuTabla()
{
    int op;

    do
    {
        system("cls");

        cout << "==========================================================" << endl;
        cout << "|                  TABLAS Y ESTADISTICAS                 |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Mostrar Tabla de Posiciones Completa                |" << endl;
        cout << "| 2. Goleadores del Torneo (Top Scorers)                 |" << endl;
        cout << "| 3. Racha (Ultimos 5 Partidos.)      |" << endl;
        cout << "|                                                        |" << endl;
        cout << "| 0. Volver al Menu Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << " Selecciona una opción: ";
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
        case 3:
            cout << "\n[Accion] Buscando Racha (Ultimos 5 Partidos)... \n" << endl;
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "\nOpción incorrecta. Intente de nuevo.\n" << endl;
            system("pause");
            break;
        }

    }
    while (op != 0);
}



