#include "Menu.h"
#include <iostream>

#include "Club.h"
#include "Jugador.h"
#include "Entrenador.h"
#include "Accion.h"
#include "ClubArchivo.h"
#include "JugadorArchivo.h"
#include "EntrenadorArchivo.h"
#include "AccionArchivo.h"
#include "PartidoArchivo.h"
#include "Partido.h"


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
         /// menuTabla();
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
    setlocale(LC_ALL, " ");



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
        cout << "| 4. Eliminar Club                    |" << endl;
        cout << "| 5. Modificar Club                   |" << endl;
        cout << "| 0. Volver al Men Principal          |" << endl;
        cout << "=======================================" << endl;
        cout << "Ingresá una opción: " << endl;
        cin >> op;

        switch (op)
        {
        case 1:
{
    Club equipo;
    ClubArchivo archivo;

    equipo.cargar();
    archivo.grabarEnDisco(equipo);
    system("pause");
}
break;
        case 2:
        {
            cout << "\n[Accion] Consulta por ID de Club... \n" << endl;


           ClubArchivo archivo;

            archivo.mostrarPorID();


            system("pause");
             }
             break;

        case 3:
        {
    ClubArchivo archivo;
    archivo.mostrarClubes(); // Tu función de listar

    // --- ESTA LÍNEA ES LA QUE TE FALTA ---
    std::cout << "\nPresione cualquier tecla para volver al menu...";
    std::cin.ignore(); // Limpia el buffer
    std::cin.get();    // Espera a que el usuario presione Enter
    // -------------------------------------
}
break;
        case 4:
        {
            cout << "\n[Accion] Eliminando Equipo... \n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            ClubArchivo archivo;
            archivo.eliminarDeDisco();

            system("pause");
        }
            break;

        case 5:
        {
            cout << "\n[Accion] Modificando Equipo... \n" << endl;

            ClubArchivo archivo;
            archivo.modificarEnDisco(0);
        }
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
        cout << "| 6. Mostrar Todos Los Jugadores De La Liga              |" << endl;
        cout << "| 7. Eliminar Jugador                                    |" << endl;
        cout << "| 8. Modificar Jugador                                   |" << endl;
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
            JugadorArchivo archivo;

            jugador.cargar();
            archivo.grabarEnDisco();

            system("pause");
        }
        break;

        case 2:
        {
            cout << "\n[Accion] Consulta por DNI...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            Jugador jugador;
            JugadorArchivo archivo;
            archivo.ConsultarPorDNI();

            system("pause");

            break;
            }
        case 3:
        {
            cout << "\n[Accion] Consulta por Posición...\n" << endl;
             cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.consultarPorPosicion();

            system("pause");
            }
            break;
        case 4:
        {

            cout << "\n[Accion] Listar Jugadores ordenados por DNI...)\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

              JugadorArchivo archivo;
            archivo.ListarDni();



            system("pause");
        }
            break;
        case 5:
        {
            cout << "\n[Accion] Listar Jugadores agrupados por Club...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.listarPorClub();


            system("pause");
            }
            break;
        case 6:
        {
            cout << "\n[Accion] Mostrar Todos Los Jugadores De La Liga...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.TodosJugadores();

            system("pause");
        }
            break;

        case 7:
        {

         cout << "\n[Accion] Eliminar Jugador... \n" << endl;
         cout<< "-------------------------------------------------------------"<<endl;


        JugadorArchivo Archivo;

        Archivo.EliminarJugador();



         system("pause");


        }
        case 8:
        {
        cout << "\n[Accion] Modificar Jugador... \n" << endl;
         cout<< "-------------------------------------------------------------"<<endl;

         int posicion=0;

          JugadorArchivo Archivo;

          Archivo.modificarEnDisco(posicion);

            system("pause");

        }

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
        cout << "| 4. Eliminar Entrenador                                 |" << endl;
        cout << "| 5. Modificar Entrenador                                |" << endl;
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
            EntrenadorArchivo archivo;


            entrenador.cargar();
            archivo.grabarEnDisco();
            system("pause");
        }
        break;
        case 2:
            {
            cout << "\n[Accion] Consulta por ID de Entrenador...\n" << endl;
               cout<< "-------------------------------------------------------------"<<endl;

               Entrenador entrenador;
            EntrenadorArchivo archivo;
            archivo.mostrarDTPorID();

            system("pause");
            }
            break;
        case 3:
        {
            cout << "\n[Accion] Listar todos los Entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            EntrenadorArchivo archivo;

                archivo.MostrarTodos();

            system("pause");
        }

        case 4:
        {
            cout << "\n[Accion] Eliminar Club... \n" << endl;

            system("pause");
        }
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

void Menu::menuPartidos() {
    int op;
    PartidoArchivo archivoPartidos;

    do {
        system("cls");
        cout << "==== MENU PARTIDOS ====" << endl;
        cout << "1 - Generar Fixture Completo (15 Jornadas)" << endl;
        cout << "2 - Ver partidos de una Jornada Especifica" << endl;
        cout << "0 - Volver al Menu Principal" << endl;
        cout << "Ingrese opcion: ";
        cin >> op;

        switch(op) {
            case 1:
                cout << "\nGenerando fixture del campeonato..." << endl;
                archivoPartidos.generarFixtureTorneo();
                system("pause");
                break;

            case 2: {
                int nroJornada;
                cout << "\nIngrese el numero de Jornada que desea ver (1 a 15): ";
                cin >> nroJornada;

                if (nroJornada >= 1 && nroJornada <= 15) {
                    archivoPartidos.listarPorJornada(nroJornada);
                } else {
                    cout << "Número de jornada invalido." << endl;
                }
                system("pause");
                break;
            }
        }

    } while(op != 0);
}

void Menu::menuAcciones()
{
    int op;

    do
    {
        system("cls");

        cout << "==========================================================" << endl;
        cout << "|                    GESTION DE ACCIONES                 |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Cargar Accion                                       |" << endl;
        cout << "| 2. Consultar Acciones por Jugador                      |" << endl;
        cout << "| 3. Consultar Acciones por Partido                      |" << endl;
        cout << "| 4. Listar Todas las Acciones                           |" << endl;
        cout << "|                                                        |" << endl;
        cout << "| 0. Volver al Menu Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch (op)
        {
            case 1:
            {
                cout << endl;
                cout << "[Accion] Cargar Accion..." << endl;
                cout << endl;

                Accion accion;
                AccionArchivo archivo;

                accion.cargar();

                if (archivo.completarDatosAccion(accion))
                {
                    if (archivo.grabarEnDisco(accion))
                    {
                        cout << "Accion guardada correctamente." << endl;
                    }
                    else
                    {
                        cout << "No se pudo guardar la accion." << endl;
                    }
                }
                else
                {
                    cout << "No se pudo completar la accion." << endl;
                    cout << "Verifique que el DNI del jugador exista." << endl;
                }

                system("pause");
            }
            break;

            case 2:
            {
                cout << endl;
                cout << "[Accion] Consultar Acciones por Jugador..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.consultarPorJugador();

                system("pause");
            }
            break;

            case 3:
            {
                cout << endl;
                cout << "[Accion] Consultar Acciones por Partido..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.consultarPorPartido();

                system("pause");
            }
            break;

            case 4:
            {
                cout << endl;
                cout << "[Accion] Listar Todas las Acciones..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.listarTodas();

                system("pause");
            }
            break;

            case 0:
                break;

            default:
                cout << endl;
                cout << "Opcion incorrecta. Intente de nuevo." << endl;
                system("pause");
                break;
        }

    } while (op != 0);
}

