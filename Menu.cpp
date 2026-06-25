#include "Menu.h"
#include <iostream>
#include <cstdio>

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
void cargarDatosDePrueba();

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
            menuTabla();
            break;
        case 7:
            cargarDatosDePrueba();
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
    cout <<"|     7. Cargar Datos de Prueba      |"<<endl;
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

    cout << endl;
    cout << "DATOS DEL DIRECTOR TECNICO: " << endl;
    cout << "--------------------------------" << endl;
    Entrenador dt;
    EntrenadorArchivo archDT;
    dt.cargar(equipo.get_idclub());
    archDT.grabarEnDisco(dt);

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
    std::cin.ignore();
    std::cin.get();
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

            ClubArchivo archivo;

           archivo.ModificarClub();

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
            if (jugador.get_idclub() != 0) {
                archivo.grabarEnDisco(jugador);
                cout << "Jugador guardado con exito." << endl;
            } else {
                cout << "Carga cancelada. No se guardo en el archivo." << endl;
            }

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

         JugadorArchivo archivo;
         archivo.ModificarJugador();
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
        cout << "| 1. Consulta por ID de Entrenador                       |" << endl;
        cout << "| 2. Listar Entrenadores Activos                         |" << endl;
        cout << "| 3. Listar Todos los Entrenadores                       |" << endl;
        cout << "| 4. Modificar Entrenador                                |" << endl;
        cout << "| 5. Eliminar Entrenador                                 |" << endl;
        cout << "| 0. Volver al Menú Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << " Seleccioná una opción: ";
        cin >> op;

        switch (op)
        {

        case 1:
            {
            cout << "\n[Acción] Consulta por ID de Entrenador...\n" << endl;
               cout<< "-------------------------------------------------------------"<<endl;

               Entrenador entrenador;
            EntrenadorArchivo archivo;
            archivo.mostrarDTPorID();

            system("pause");

            }
            break;
        case 2:
        {
            cout << "\n[Acción] Listar todos los entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            EntrenadorArchivo archivo;

                archivo.listarActivos();

            system("pause");
        }
        break;

        case 3:
        {
            cout << "\n[Acción] Listar todos los entrenadores...\n" << endl;
            cout<< "-------------------------------------------------------------"<<endl;

            EntrenadorArchivo archivo;
            archivo.listar();
            system("pause");
        }
        break;

        case 4:
        {
            cout << "\n[Acción] Modificar Entrenador... \n" << endl;

            EntrenadorArchivo Archivo;
            Archivo.modificarEntrenador();
            system("pause");
        }
        break;

        case 5:
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
    PartidoArchivo archivoPartidos;
    int opcion;

    do {
        system("cls");

        int proximaFecha = archivoPartidos.obtenerSiguienteJornadaAJugarse();

        cout << "========================================" << endl;
        cout << "            MENU DE PARTIDOS            " << endl;
        cout << "========================================" << endl;
        cout << "1. Generar Fixture del Torneo" << endl;
        cout << "2. Ver Partidos de una Jornada" << endl;
        cout << "3. Ver Todos los Partidos" << endl;

        if (proximaFecha != -1) {
            cout << "4. Simular Jornada " << proximaFecha << endl;
        } else {
            cout << "4. Simular Jornada (Torneo Finalizado)" << endl;
        }
        cout << "5. Simular Todo el Torneo" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "========================================" << endl;
        cout << "Ingresá una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                archivoPartidos.generarFixtureTorneo();
                break;
            case 2:
                archivoPartidos.VerJornada();
                break;
            case 3:
                archivoPartidos.VerPartidos();
                break;
            case 4:
                archivoPartidos.simularSiguienteJornada();
                break;
            case 5:
                archivoPartidos.simularTorneoCompleto();
                break;
            case 0:
                break;
            default:
                cout << "Opción inválida." << endl;
        }

        if (opcion != 0) {
            cout << endl;
            system("pause");
        }

    } while (opcion != 0);
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
        cout << "| 1. Consultar Acciones por Jugador                      |" << endl;
        cout << "| 2. Consultar Acciones por Partido                      |" << endl;
        cout << "| 3. Listar Acciones Activas                             |" << endl;
        cout << "| 4. Listar Todas las Acciones                           |" << endl;
        cout << "| 0. Volver al Menu Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch (op)
        {
            case 1:
            {
                cout << endl;
                cout << "[Accion] Consultar Acciones por Jugador..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.consultarPorJugador();

                system("pause");
            }
            break;

            case 2:
            {
                cout << endl;
                cout << "[Accion] Consultar Acciones por Partido..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.consultarPorPartido();

                system("pause");
            }
            break;

            case 3:
            {
                cout << endl;
                cout << "[Accion] Listar Acciones Activas..." << endl;
                cout << endl;

                AccionArchivo archivo;
                archivo.listarActivos();

                system("pause");
            }
            break;

            case 4:
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

void Menu::menuTabla()
{
    int op;

    do
    {
        system("cls");

        cout << "==========================================================" << endl;
        cout << "|                    MENU DE TABLAS                      |" << endl;
        cout << "==========================================================" << endl;
        cout << "| 1. Tabla de posiciones de clubes                       |" << endl;
        cout << "| 2. Rendimiento de jugadores                            |" << endl;
        cout << "| 3. Rachas de clubes                                    |" << endl;
        cout << "| 0. Volver al Menu Principal                            |" << endl;
        cout << "==========================================================" << endl;
        cout << "Selecciona una opcion: ";
        cin >> op;

        switch (op)
        {
            case 1:
            {
                PartidoArchivo archivo;
                archivo.listarTablaPosiciones();
                system("pause");
            }
            break;

            case 2:
            {
                /* El rendimiento no se carga a mano.
                   Sale de sumar los puntajes de acciones.dat por jugador.
                   Si no se simulo ninguna jornada, todavia no hay acciones. */
                AccionArchivo archivo;
                archivo.listarRendimientoJugadores();
                system("pause");
            }
            break;

            case 3:
            {
                PartidoArchivo archivo;
                archivo.listarRachasClubesOrdenadas();
                system("pause");
            }
            break;

            case 0:
                break;

            default:
                cout << "Opcion incorrecta. Intente de nuevo." << endl;
                system("pause");
                break;
        }

    } while (op != 0);
}

/* DATOS DE PRUEBA PARA SIMULAR
   Carga clubes y jugadores para no tener que ingresarlos a mano.
   Tambien genera el fixture, asi la tabla ya tiene partidos.
   Despues hay que simular jornadas para que existan resultados y acciones. */
void cargarDatosDePrueba()
{
    FILE *p;

    p = fopen("clubes.dat", "wb");
    if (p != NULL) fclose(p);

    p = fopen("jugadores.dat", "wb");
    if (p != NULL) fclose(p);

    p = fopen("partidos.dat", "wb");
    if (p != NULL) fclose(p);

    p = fopen("acciones.dat", "wb");
    if (p != NULL) fclose(p);

    p = fopen("entrenadores.dat", "wb");
    if (p != NULL) fclose(p);

    ClubArchivo archivoClubes;
    JugadorArchivo archivoJugadores;
    EntrenadorArchivo archivoEntrenadores;

    const char *clubes[20] = {
        "Boca Juniors",
        "River Plate",
        "Racing Club",
        "Independiente",
        "San Lorenzo",
        "Velez Sarsfield",
        "Estudiantes LP",
        "Gimnasia LP",
        "Rosario Central",
        "Newells Old Boys",
        "Lanus",
        "Banfield",
        "Huracan",
        "Argentinos Juniors",
        "Talleres",
        "Belgrano",
        "Defensa y Justicia",
        "Tigre",
        "Platense",
        "Godoy Cruz"
    };

    const char *presidentes[20] = {
        "Presidente Boca",
        "Presidente River",
        "Presidente Racing",
        "Presidente Independiente",
        "Presidente San Lorenzo",
        "Presidente Velez",
        "Presidente Estudiantes",
        "Presidente Gimnasia",
        "Presidente Rosario",
        "Presidente Newells",
        "Presidente Lanus",
        "Presidente Banfield",
        "Presidente Huracan",
        "Presidente Argentinos",
        "Presidente Talleres",
        "Presidente Belgrano",
        "Presidente Defensa",
        "Presidente Tigre",
        "Presidente Platense",
        "Presidente Godoy Cruz"
    };

    int aniosFundacion[20] = {
        1905, 1901, 1903, 1905, 1908, 1910, 1905, 1887,
        1889, 1903, 1915, 1896, 1908, 1904, 1913, 1905,
        1935, 1902, 1905, 1921
    };

    const char *nombres[12] = {
        "Juan", "Pedro", "Lucas", "Mateo", "Tomas", "Nicolas",
        "Diego", "Martin", "Santiago", "Facundo", "Bruno", "Ezequiel"
    };

    const char *apellidos[12] = {
        "Garcia", "Lopez", "Martinez", "Rodriguez", "Gonzalez", "Perez",
        "Sanchez", "Romero", "Diaz", "Fernandez", "Acosta", "Silva"
    };

    const char *posiciones[12] = {
        "Arquero",
        "Defensor", "Defensor", "Defensor", "Defensor",
        "Mediocampo", "Mediocampo", "Mediocampo", "Mediocampo",
        "Delantero", "Delantero", "Delantero"
    };

    int idJugador = 1;

    for (int i = 0; i < 20; i++)
    {
        Fecha fechaClub;
        fechaClub.set_Dia(1);
        fechaClub.set_Mes(1);
        fechaClub.set_Anio(aniosFundacion[i]);

        Club club;
        club.set_idclub(i + 1);
        club.set_nombre(clubes[i]);
        Persona pres;
        pres.set_nombre(presidentes[i]);
        pres.set_apellido(apellidos[i % 12]);
        pres.set_dni(10000000 + i);
        Fecha fechaPres;
        fechaPres.set_Dia(1 + (i % 28));
        fechaPres.set_Mes(1 + (i % 12));
        fechaPres.set_Anio(1950 + (i % 20));
        pres.set_fechanacimiento(fechaPres);
        pres.set_activo(true);
        club.set_presidente(pres);
        club.set_fechafundacion(fechaClub);
        club.set_cantidadtrofeos(0);
        club.set_cantidaddescensos(0);
        club.set_activo(true);

        for (int j = 0; j < 16; j++)
        {
            club.set_racha(j, 0);
        }

        if (i < 16) {
            club.set_division(1); // 1 = Primera Division
        } else {
            club.set_division(2); // 2 = Segunda Division
        }

        archivoClubes.grabarEnDisco(club);

        Entrenador dt;
        dt.set_idEntrenador(i + 1);
        dt.set_nombre(nombres[i % 12]);
        dt.set_apellido(apellidos[i % 12]);
        dt.set_dni(20000000 + i);

        Fecha fechaDT;
        fechaDT.set_Dia(1 + (i % 28));
        fechaDT.set_Mes(1 + (i % 12));
        fechaDT.set_Anio(1960 + (i % 15));
        dt.set_fechanacimiento(fechaDT);

        dt.set_idclub(i + 1);
        dt.set_activo(true);
        archivoEntrenadores.grabarEnDisco(dt);

        for (int j = 0; j < 12; j++)
        {
            Fecha fechaJugador;
            fechaJugador.set_Dia(1 + (j % 28));
            fechaJugador.set_Mes(1 + (j % 12));
            fechaJugador.set_Anio(1990 + (j % 10));

            Jugador jugador;
            jugador.set_idjugador(idJugador);
            jugador.set_nombre(nombres[j]);
            jugador.set_apellido(apellidos[j]);
            jugador.set_dni(30000000 + (i * 100) + j);
            jugador.set_fechanacimiento(fechaJugador);
            jugador.set_activo(true);
            jugador.set_idclub(i + 1);
            jugador.set_numerocamiseta(j + 1);
            jugador.set_posicion(posiciones[j]);
            jugador.set_valormercado(1000000 + (j * 100000));

            archivoJugadores.grabarEnDisco(jugador);
            idJugador++;
        }
    }

    /* SE GENERA EL FIXTURE PARA QUE LA TABLA YA TENGA PARTIDOS */
    PartidoArchivo archivoPartidos;
    archivoPartidos.generarFixtureTorneo();

    cout << "Datos de prueba cargados correctamente." << endl;
    cout << "Clubes cargados: 20 (16 de Primera, 4 de Segunda)" << endl;
    cout << "Jugadores cargados: 240" << endl;
    cout << "Fixture generado: 120 partidos" << endl;
    cout << "Ahora podes simular jornadas." << endl;
}




