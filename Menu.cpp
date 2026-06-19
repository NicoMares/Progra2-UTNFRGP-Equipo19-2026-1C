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

void modificarClub();
void modificarJugador();
void modificarEntrenador();

Menu::Menu()
{

}

void  Menu :: run()
{
    int opcion;

    do
    {
        Mostrar();
        cout<<"Ingresá una opción: "<<endl;
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
            cout<<"Opción no válida. Por favor, ingresá una opción válida."<<endl;
        }

        system("pause");
        system("cls");

    }
    while (opcion != 0);
}


void  Menu :: Mostrar()
{
    cout<<"======================================"<<endl;

    cout<<"|     SISTEMA DE LIGA DE FÚTBOL      |"<<endl;

    cout<<"======================================"<<endl;

    cout<<"Menú Principal "<<endl;

    cout<<"--------------------------------------"<<endl;

    cout <<"|     1. Gestión de Equipos          |"<<endl;
    cout <<"|     2. Gestión de Jugadores        |"<<endl;
    cout <<"|     3. Gestión de Entrenadores     |"<<endl;
    cout <<"|     4. Gestión de Partidos         |"<<endl;
    cout <<"|     5. Gestión de Acciones         |"<<endl;
    cout <<"|     6. Mostrar Tabla               |"<<endl;
    cout <<"|     0. Salir                       |"<<endl;

    cout<<"--------------------------------------"<<endl;

}

void Menu::menuEquipos()
{
    int op;

    do
    {
        system("cls");

        cout << "=======================================" << endl;
        cout << "|          GESTIÓN DE EQUIPOS         |" << endl;
        cout << "=======================================" << endl;
        cout << "| 1. Cargar Equipo                    |" << endl;
        cout << "| 2. Consulta por ID de Club          |" << endl;
        cout << "| 3. Listado de Clubes Activos        |" << endl;
        cout << "| 4. Listado de Clubes                |" << endl;
        cout << "| 5. Modificar Club                   |" << endl;
        cout << "| 6. Eliminar Club                    |" << endl;
        cout << "| 0. Volver al Menú Principal         |" << endl;
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
            cout << "\n[Acción] Consulta por ID de Club... \n" << endl;


           ClubArchivo archivo;

            archivo.mostrarPorID();


            system("pause");
             }
             break;

        case 3:
        {
    ClubArchivo archivo;
    archivo.listarActivos();

    std::cout << "\nPresioná Enter para volver al menú...";
    std::cin.ignore(); // Limpia el buffer
    std::cin.get();    // Espera a que el usuario presione Enter
}
break;
        case 4:
        {
            ClubArchivo archivo;
            archivo.listar();

            std::cout << "\nPresioná Enter para volver al menú...";
            std::cin.ignore();
            std::cin.get();
        }
            break;

        case 5:
        {
            cout << "\n[Acción] Modificando Equipo... \n" << endl;
            modificarClub();
            system("pause");
        }
            break;
        case 6:
        {
            cout << "\n[Acción] Eliminando Equipo... \n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            ClubArchivo archivo;
            archivo.eliminarDeDisco();

            system("pause");
        }
            break;
            case 0:

            break;
        default:
            cout << "\nOpción no válida. Por favor, intentá de nuevo.\n" << endl;
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
        cout << "|                    GESTIÓN DE JUGADORES                |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Cargar Jugador                                      |" << endl;
        cout << "| 2. Consulta por DNI                                    |" << endl;
        cout << "| 3. Consulta por Posición                               |" << endl;
        cout << "| 4. Listar Jugadores ordenados por DNI                  |" << endl;
        cout << "| 5. Listar Jugadores agrupados por Club                 |" << endl;
        cout << "| 6. Mostrar Jugadores Activos De La Liga                |" << endl;
        cout << "| 7. Mostrar Todos Los Jugadores De La Liga              |" << endl;
        cout << "| 8. Modificar Jugador                                   |" << endl;
        cout << "| 9. Eliminar Jugador                                    |" << endl;
        cout << "| 0. Volver al Menú Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << " Seleccioná una opción: ";
        cin >> op;

        switch (op)
        {
        case 1:
        {
            cout << "\n[Acción] Cargar Jugador...\n" << endl;

            Jugador jugador;
            JugadorArchivo archivo;

            jugador.cargar();
            archivo.grabarEnDisco(jugador);

            system("pause");
        }
        break;

        case 2:
        {
            cout << "\n[Acción] Consulta por DNI...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            Jugador jugador;
            JugadorArchivo archivo;
            archivo.ConsultarPorDNI();

            system("pause");

            break;
            }
        case 3:
        {
            cout << "\n[Acción] Consulta por Posición...\n" << endl;
             cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.consultarPorPosicion();

            system("pause");
            }
            break;
        case 4:
        {

            cout << "\n[Acción] Listar Jugadores ordenados por DNI...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.listarPorDNI();



            system("pause");
        }
            break;
        case 5:
        {
            cout << "\n[Acción] Listar Jugadores agrupados por Club...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.listarPorClub();


            system("pause");
            }
            break;
        case 6:
        {
            cout << "\n[Acción] Mostrar todos los jugadores de la liga...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.listarActivos();

            system("pause");
        }
            break;

        case 7:
        {
            cout << "\n[Acción] Mostrar todos los jugadores de la liga...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            JugadorArchivo archivo;
            archivo.listar();

            system("pause");
        }
        break;
        case 8:
        {
        cout << "\n[Acción] Modificar Jugador... \n" << endl;
         cout<< "-------------------------------------------------------------"<<endl;
         modificarJugador();
         system("pause");

        }
        break;
        case 9:
        {
         cout << "\n[Acción] Eliminar Jugador... \n" << endl;
         cout<< "-------------------------------------------------------------"<<endl;

         JugadorArchivo archivo;
         archivo.EliminarJugador();

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
        cout << "|                  GESTIÓN DE ENTRENADORES               |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Cargar Entrenador                                   |" << endl;
        cout << "| 2. Consulta por ID de Entrenador                       |" << endl;
        cout << "| 3. Listar Entrenadores Activos                         |" << endl;
        cout << "| 4. Listar Todos los Entrenadores                       |" << endl;
        cout << "| 5. Modificar Entrenador                                |" << endl;
        cout << "| 6. Eliminar Entrenador                                 |" << endl;
        cout << "| 0. Volver al Menú Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << " Seleccioná una opción: ";
        cin >> op;

        switch (op)
        {
        case 1:
        {
            cout << "\n[Acción] Cargar Entrenador...\n" << endl;

            Entrenador entrenador;
            EntrenadorArchivo archivo;


            entrenador.cargar();
            archivo.grabarEnDisco(entrenador);
            system("pause");
        }
        break;
        case 2:
            {
            cout << "\n[Acción] Consulta por ID de Entrenador...\n" << endl;
               cout<< "-------------------------------------------------------------"<<endl;

               Entrenador entrenador;
            EntrenadorArchivo archivo;
            archivo.mostrarDTPorID();

            system("pause");
            }
            break;
        case 3:
        {
            cout << "\n[Acción] Listar todos los entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            EntrenadorArchivo archivo;

                archivo.listarActivos();

            system("pause");
        }
        break;

        case 4:
        {
            cout << "\n[Acción] Listar todos los entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            EntrenadorArchivo archivo;
            archivo.listar();
            system("pause");
        }
        break;

        case 5:
        {
            cout << "\n[Acción] Modificar Entrenador... \n" << endl;
            modificarEntrenador();
            system("pause");
        }
        break;

        case 6:
        {
            cout << "\n[Acción] Eliminar Entrenador... \n" << endl;

            EntrenadorArchivo archivo;
            archivo.EliminarEntrenador();
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
        cout << "---------------------------------------------"<< endl;
        cout << "1 - Generar Fixture Completo (15 Jornadas)" << endl;
        cout << "2 - Ver partidos de una Jornada Especifica" << endl;
        cout << "0 - Volver al Menu Principal" << endl;
        cout << "---------------------------------------------"<< endl;
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
        cout << "| 4. Listar Acciones Activas                             |" << endl;
        cout << "| 5. Listar Todas las Acciones                           |" << endl;
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
                cout << "[Accion] Listar Acciones Activas..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.listarActivos();

                system("pause");
            }
            break;

            case 5:
            {
                cout << endl;
                cout << "[Accion] Listar Todas las Acciones..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.listar();

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

void modificarClub()
{
    ClubArchivo archivo;
    int idClub;
    cout << "Ingrese el ID del club a modificar: ";
    cin >> idClub;

    int pos = archivo.buscarPorID(idClub);
    if (pos == -1)
    {
        cout << "No existe un club con ese ID." << endl;
        return;
    }

    Club club = archivo.leerDeDisco(pos);
    if (!club.get_activo())
    {
        cout << "No se puede modificar un club inactivo." << endl;
        return;
    }
    int opcion;

    cout << "1. Nombre" << endl;
    cout << "2. Presidente" << endl;
    cout << "3. Fecha de fundación" << endl;
    cout << "4. Cantidad de trofeos" << endl;
    cout << "5. Cantidad de descensos" << endl;
    cout << "Seleccioná el campo a modificar: ";
    cin >> opcion;

    if (opcion == 1)
    {
        char nombre[50];
        cout << "Ingrese el nuevo nombre: ";
        cin >> ws;
        cin.getline(nombre, 50);
        club.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        char presidente[50];
        cout << "Ingrese el nuevo presidente: ";
        cin >> ws;
        cin.getline(presidente, 50);
        club.set_presidente(presidente);
    }
    else if (opcion == 3)
    {
        Fecha fecha;
        cout << "Ingrese la nueva fecha:" << endl;
        fecha.cargar();
        club.set_fechafundacion(fecha);
    }
    else if (opcion == 4)
    {
        int trofeos;
        cout << "Ingrese la nueva cantidad de trofeos: ";
        cin >> trofeos;
        club.set_cantidadtrofeos(trofeos);
    }
    else if (opcion == 5)
    {
        int descensos;
        cout << "Ingrese la nueva cantidad de descensos: ";
        cin >> descensos;
        club.set_cantidaddescensos(descensos);
    }
    else
    {
        cout << "Opción incorrecta." << endl;
        return;
    }

    if (archivo.modificarEnDisco(club, pos))
    {
        cout << "Club modificado correctamente." << endl;
    }
    else
    {
        cout << "No se pudo modificar el club." << endl;
    }
}

void modificarJugador()
{
    JugadorArchivo archivo;
    int idJugador;
    cout << "Ingrese el ID del jugador a modificar: ";
    cin >> idJugador;

    int pos = archivo.buscarPorID(idJugador);
    if (pos == -1)
    {
        cout << "No existe un jugador con ese ID." << endl;
        return;
    }

    Jugador jugador = archivo.leerDeDisco(pos);
    if (!jugador.get_activo())
    {
        cout << "No se puede modificar un jugador inactivo." << endl;
        return;
    }
    int opcion;

    cout << "1. Nombre" << endl;
    cout << "2. Apellido" << endl;
    cout << "3. DNI" << endl;
    cout << "4. Fecha de nacimiento" << endl;
    cout << "5. Club" << endl;
    cout << "6. Número de camiseta" << endl;
    cout << "7. Posición" << endl;
    cout << "8. Valor de mercado" << endl;
    cout << "Seleccioná el campo a modificar: ";
    cin >> opcion;

    if (opcion == 1)
    {
        char nombre[30];
        cout << "Ingrese el nuevo nombre: ";
        cin >> ws;
        cin.getline(nombre, 30);
        jugador.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        char apellido[30];
        cout << "Ingrese el nuevo apellido: ";
        cin >> ws;
        cin.getline(apellido, 30);
        jugador.set_apellido(apellido);
    }
    else if (opcion == 3)
    {
        int dni;
        cout << "Ingrese el nuevo DNI: ";
        cin >> dni;
        jugador.set_dni(dni);
    }
    else if (opcion == 4)
    {
        Fecha fecha;
        cout << "Ingrese la nueva fecha:" << endl;
        fecha.cargar();
        jugador.set_fechanacimiento(fecha);
    }
    else if (opcion == 5)
    {
        int idClub;
        cout << "Ingrese el nuevo ID de club: ";
        cin >> idClub;
        jugador.set_idclub(idClub);
    }
    else if (opcion == 6)
    {
        int camiseta;
        cout << "Ingresá el nuevo número de camiseta: ";
        cin >> camiseta;
        jugador.set_numerocamiseta(camiseta);
    }
    else if (opcion == 7)
    {
        char posicion[50];
        cout << "Ingresá la nueva posición: ";
        cin >> ws;
        cin.getline(posicion, 50);
        jugador.set_posicion(posicion);
    }
    else if (opcion == 8)
    {
        float valor;
        cout << "Ingrese el nuevo valor de mercado: ";
        cin >> valor;
        jugador.set_valormercado(valor);
    }
    else
    {
        cout << "Opción incorrecta." << endl;
        return;
    }

    if (archivo.modificarEnDisco(jugador, pos))
    {
        cout << "Jugador modificado correctamente." << endl;
    }
    else
    {
        cout << "No se pudo modificar el jugador." << endl;
    }
}

void modificarEntrenador()
{
    EntrenadorArchivo archivo;
    int idEntrenador;
    cout << "Ingrese el ID del entrenador a modificar: ";
    cin >> idEntrenador;

    int pos = archivo.buscarPorID(idEntrenador);
    if (pos == -1)
    {
        cout << "No existe un entrenador con ese ID." << endl;
        return;
    }

    Entrenador entrenador = archivo.leerDisco(pos);
    if (!entrenador.get_activo())
    {
        cout << "No se puede modificar un entrenador inactivo." << endl;
        return;
    }
    int opcion;

    cout << "1. Nombre" << endl;
    cout << "2. Apellido" << endl;
    cout << "3. DNI" << endl;
    cout << "4. Fecha de nacimiento" << endl;
    cout << "5. Club" << endl;
    cout << "Seleccioná el campo a modificar: ";
    cin >> opcion;

    if (opcion == 1)
    {
        char nombre[30];
        cout << "Ingrese el nuevo nombre: ";
        cin >> ws;
        cin.getline(nombre, 30);
        entrenador.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        char apellido[30];
        cout << "Ingrese el nuevo apellido: ";
        cin >> ws;
        cin.getline(apellido, 30);
        entrenador.set_apellido(apellido);
    }
    else if (opcion == 3)
    {
        int dni;
        cout << "Ingrese el nuevo DNI: ";
        cin >> dni;
        entrenador.set_dni(dni);
    }
    else if (opcion == 4)
    {
        Fecha fecha;
        cout << "Ingrese la nueva fecha:" << endl;
        fecha.cargar();
        entrenador.set_fechanacimiento(fecha);
    }
    else if (opcion == 5)
    {
        int idClub;
        cout << "Ingrese el nuevo ID de club: ";
        cin >> idClub;
        entrenador.set_idclub(idClub);
    }
    else
    {
        cout << "Opción incorrecta." << endl;
        return;
    }

    if (archivo.modificarEnDisco(entrenador, pos))
    {
        cout << "Entrenador modificado correctamente." << endl;
    }
    else
    {
        cout << "No se pudo modificar el entrenador." << endl;
    }
}
