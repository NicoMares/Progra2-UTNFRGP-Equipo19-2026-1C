#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "AccionArchivo.h"
#include "JugadorArchivo.h"

/* IDS DE TIPO DE ACCION
   Antes se comparaba por texto con strcmp("Gol", "Roja", etc.).
   Ahora el numero identifica el tipo de accion y el texto queda solo para mostrar. */
const int ACCION_GOL = 1;
const int ACCION_ASISTENCIA = 2;
const int ACCION_AMARILLA = 3;
const int ACCION_ROJA = 4;
const int ACCION_FALTA = 5;
const int ACCION_ATAJADA = 6;
const int ACCION_LESION = 7;

struct RegistroJugadorRendimiento
{
    Jugador jugador;
    int puntaje;
};

bool AccionArchivo::grabarEnDisco(Accion accion)
{
    FILE *pFile;
    bool result;

    pFile = fopen("acciones.dat", "ab");

    if (pFile == NULL)
    {
        return false;
    }

    result = fwrite(&accion, sizeof(Accion), 1, pFile);

    fclose(pFile);

    return result;
}

Accion AccionArchivo::leerDeDisco(int posicion)
{
    Accion accion;
    FILE *pFile;

    pFile = fopen("acciones.dat", "rb");

    if (pFile == NULL)
    {
        return accion;
    }

    fseek(pFile, posicion * sizeof(Accion), SEEK_SET);
    fread(&accion, sizeof(Accion), 1, pFile);

    fclose(pFile);

    return accion;
}

int AccionArchivo::contarRegistros()
{
    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile == NULL)
    {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Accion);
}

/* VACIA ACCIONES CUANDO SE GENERA UN FIXTURE NUEVO
   Si se crea otro fixture, las acciones anteriores ya no pertenecen a esos partidos. */
void AccionArchivo::vaciarArchivo()
{
    FILE *pFile = fopen("acciones.dat", "wb");
    if (pFile != NULL)
    {
        fclose(pFile);
    }
}

bool AccionArchivo::completarDatosAccion(Accion &accion)
{
    char posicionJugador[50];
    int idClubJugador;
    int puntaje;

    if (obtenerDatosJugador(accion.get_dnijugador(), posicionJugador, idClubJugador) == false)
    {
        return false;
    }

    accion.set_idclub(idClubJugador);

    /* El puntaje se calcula aca para que todas las acciones usen la misma regla.
       Depende del tipo de accion y de la posicion del jugador. */
    puntaje = calcularPuntaje(accion.get_idaccion(), posicionJugador);
    accion.set_puntaje(puntaje);

    accion.set_activo(true);

    return true;
}

bool AccionArchivo::obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador)
{
    JugadorArchivo archivo;
    int posicion = archivo.buscarPorDNI(dniJugador);
    if (posicion == -1)
    {
        return false;
    }

    Jugador jugador = archivo.leerDeDisco(posicion);
    if (!jugador.get_activo())
    {
        return false;
    }

    strcpy(posicionJugador, jugador.get_posicion());
    idClubJugador = jugador.get_idclub();

    return true;
}

int AccionArchivo::calcularPuntaje(int idAccion, const char posicionJugador[])
{
    /* Reglas de puntaje:
       - Gol y asistencia valen distinto segun la posicion.
       - Amarilla, roja, falta y lesion restan siempre.
       - Atajada suma si es arquero y resta -1 si la hace otro jugador. */
    if (idAccion == ACCION_GOL)
    {
        if (strcmp(posicionJugador, "Arquero") == 0)
        {
            return 10;
        }

        if (strcmp(posicionJugador, "Defensor") == 0)
        {
            return 8;
        }

        if (strcmp(posicionJugador, "Mediocampo") == 0)
        {
            return 6;
        }

        if (strcmp(posicionJugador, "Delantero") == 0)
        {
            return 5;
        }
    }

    if (idAccion == ACCION_ASISTENCIA)
    {
        if (strcmp(posicionJugador, "Arquero") == 0)
        {
            return 6;
        }

        if (strcmp(posicionJugador, "Defensor") == 0)
        {
            return 5;
        }

        if (strcmp(posicionJugador, "Mediocampo") == 0)
        {
            return 4;
        }

        if (strcmp(posicionJugador, "Delantero") == 0)
        {
            return 3;
        }
    }

    if (idAccion == ACCION_AMARILLA)
    {
        return -2;
    }

    if (idAccion == ACCION_ROJA)
    {
        return -6;
    }

    if (idAccion == ACCION_FALTA)
    {
        return -1;
    }

    if (idAccion == ACCION_ATAJADA)
    {
        if (strcmp(posicionJugador, "Arquero") == 0)
        {
            return 4;
        }

        return -1;
    }

    if (idAccion == ACCION_LESION)
    {
        return -3;
    }

    return 0;
}

/* PROBABILIDADES DEL RANDOMIZADOR
   No todas las acciones tienen la misma chance:
   falta 30%, amarilla 18%, atajada 12%, lesion 10%,
   asistencia 10%, gol 17%, roja 3%. */
int AccionArchivo::obtenerTipoAccionRandom()
{
    int numero = rand() % 100;

    if (numero < 30) return ACCION_FALTA;
    if (numero < 48) return ACCION_AMARILLA;
    if (numero < 60) return ACCION_ATAJADA;
    if (numero < 70) return ACCION_LESION;
    if (numero < 80) return ACCION_ASISTENCIA;
    if (numero < 97) return ACCION_GOL;
    return ACCION_ROJA;
}

/* EL ID DEFINE EL TIPO DE ACCION, EL TEXTO SOLO SE USA PARA MOSTRAR */
void AccionArchivo::configurarTipoAccion(Accion &accion, int idAccion)
{
    accion.set_idaccion(idAccion);

    if (idAccion == ACCION_GOL)
    {
        accion.set_tipoaccion("Gol");
    }
    else if (idAccion == ACCION_ASISTENCIA)
    {
        accion.set_tipoaccion("Asistencia");
    }
    else if (idAccion == ACCION_AMARILLA)
    {
        accion.set_tipoaccion("Amarilla");
    }
    else if (idAccion == ACCION_ROJA)
    {
        accion.set_tipoaccion("Roja");
    }
    else if (idAccion == ACCION_FALTA)
    {
        accion.set_tipoaccion("Falta");
    }
    else if (idAccion == ACCION_ATAJADA)
    {
        accion.set_tipoaccion("Atajada");
    }
    else if (idAccion == ACCION_LESION)
    {
        accion.set_tipoaccion("Lesion");
    }
}

/* SIMULA LAS ACCIONES DE UN PARTIDO
   Antes el resultado salia directo de rand() en PartidoArchivo.
   Ahora primero se generan acciones de jugadores reales y despues los goles
   del partido salen de contar las acciones de tipo Gol. */
void AccionArchivo::simularAccionesDePartido(Partido partido)
{
    JugadorArchivo archivoJugadores;
    int cantidadAcciones = 8 + rand() % 13;

    for (int i = 0; i < cantidadAcciones; i++)
    {
        int idClub = partido.get_idclublocal();
        if (rand() % 2 == 1)
        {
            idClub = partido.get_idclubvisitante();
        }

        Jugador jugador = archivoJugadores.obtenerJugadorRandomPorClub(idClub);
        if (jugador.get_dni() == 0)
        {
            continue;
        }

        Accion accion;
        accion.set_idpartido(partido.get_idpartido());
        accion.set_dnijugador(jugador.get_dni());
        accion.set_minuto(1 + rand() % 90);
        configurarTipoAccion(accion, obtenerTipoAccionRandom());

        if (completarDatosAccion(accion))
        {
            grabarEnDisco(accion);
        }
    }
}

/* CUENTA GOLES DESDE ACCIONES.DAT
   Opcion A: acciones.dat es la fuente que genera el resultado,
   y partidos.dat guarda una copia/resumen de esos goles. */
int AccionArchivo::contarGolesPorPartidoYClub(int idPartido, int idClub)
{
    int goles = 0;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile == NULL) return 0;

    Accion accion;
    while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
    {
        if (accion.get_activo() &&
            accion.get_idpartido() == idPartido &&
            accion.get_idclub() == idClub &&
            accion.get_idaccion() == ACCION_GOL)
        {
            goles++;
        }
    }

    fclose(pFile);
    return goles;
}

/* SUMA EL PUNTAJE DE TODAS LAS ACCIONES DE UN JUGADOR
   El jugador no guarda puntaje acumulado en su registro.
   La tabla de rendimiento suma los puntos de sus acciones guardadas. */
int AccionArchivo::calcularPuntajeTotalJugador(int dniJugador)
{
    int total = 0;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile == NULL) return 0;

    Accion accion;
    while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
    {
        if (accion.get_activo() && accion.get_dnijugador() == dniJugador)
        {
            total += accion.get_puntaje();
        }
    }

    fclose(pFile);
    return total;
}

/* LISTA JUGADORES ORDENADOS DEL MEJOR AL PEOR RENDIMIENTO
   El puntaje sale de acciones.dat:
   cada accion tiene un puntaje positivo o negativo, y se suman por DNI. */
void AccionArchivo::listarRendimientoJugadores()
{
    JugadorArchivo archivoJugadores;
    int cantidadJugadores = archivoJugadores.contarRegistros();
    int cantidadAcciones = contarRegistros();

    if (cantidadJugadores == 0)
    {
        std::cout << "No hay jugadores cargados." << std::endl;
        return;
    }

    if (cantidadAcciones == 0)
    {
        std::cout << "Todavia no hay acciones generadas." << std::endl;
        std::cout << "Primero simula una jornada desde Gestion de Partidos." << std::endl;
        return;
    }

    RegistroJugadorRendimiento *tabla = new RegistroJugadorRendimiento[cantidadJugadores];
    int cantidadTabla = 0;

    for (int i = 0; i < cantidadJugadores; i++)
    {
        Jugador jugador = archivoJugadores.leerDeDisco(i);
        if (jugador.get_activo())
        {
            tabla[cantidadTabla].jugador = jugador;
            tabla[cantidadTabla].puntaje = calcularPuntajeTotalJugador(jugador.get_dni());
            cantidadTabla++;
        }
    }

    for (int i = 0; i < cantidadTabla - 1; i++)
    {
        for (int j = 0; j < cantidadTabla - 1 - i; j++)
        {
            if (tabla[j].puntaje < tabla[j + 1].puntaje)
            {
                RegistroJugadorRendimiento aux = tabla[j];
                tabla[j] = tabla[j + 1];
                tabla[j + 1] = aux;
            }
        }
    }

    std::cout << "==========================================================" << std::endl;
    std::cout << "          RENDIMIENTO DE JUGADORES" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "POS\tDNI\t\tJUGADOR\t\tPUNTOS" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    for (int i = 0; i < cantidadTabla; i++)
    {
        std::cout << i + 1 << "\t"
                  << tabla[i].jugador.get_dni() << "\t"
                  << tabla[i].jugador.get_nombre() << " "
                  << tabla[i].jugador.get_apellido() << "\t\t"
                  << tabla[i].puntaje << std::endl;
    }

    delete [] tabla;
}

void AccionArchivo::listarActivos()
{
    Accion accion;
    bool encontro = false;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile != NULL)
    {
        while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
        {
            if (accion.get_activo() == true)
            {
                accion.mostrar();
                std::cout << "--------------------------------" << std::endl;
                encontro = true;
            }
        }
        fclose(pFile);
    }

    if (encontro == false)
    {
        std::cout << "No hay acciones activas cargadas." << std::endl;
    }
}

void AccionArchivo::listar()
{
    Accion accion;
    bool encontro = false;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile != NULL)
    {
        while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
        {
            accion.mostrar();
            std::cout << "--------------------------------" << std::endl;
            encontro = true;
        }
        fclose(pFile);
    }

    if (encontro == false)
    {
        std::cout << "No hay acciones cargadas." << std::endl;
    }
}

void AccionArchivo::consultarPorJugador()
{
    int dniBuscado;
    Accion accion;
    bool encontrado = false;

    std::cout << "INGRESE DNI DEL JUGADOR: ";
    std::cin >> dniBuscado;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile != NULL)
    {
        while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
        {
            if (accion.get_dnijugador() == dniBuscado && accion.get_activo() == true)
            {
                accion.mostrar();
                std::cout << "-----------------------------" << std::endl;
                encontrado = true;
            }
        }
        fclose(pFile);
    }

    if (encontrado == false)
    {
        std::cout << "No se encontraron acciones para ese jugador." << std::endl;
    }
}

void AccionArchivo::consultarPorPartido()
{
    int idPartidoBuscado;
    Accion accion;
    bool encontrado = false;

    std::cout << "INGRESE ID DEL PARTIDO: ";
    std::cin >> idPartidoBuscado;

    FILE *pFile = fopen("acciones.dat", "rb");
    if (pFile != NULL)
    {
        while (fread(&accion, sizeof(Accion), 1, pFile) == 1)
        {
            if (accion.get_idpartido() == idPartidoBuscado && accion.get_activo() == true)
            {
                accion.mostrar();
                std::cout << "-----------------------------" << std::endl;
                encontrado = true;
            }
        }
        fclose(pFile);
    }

    if (encontrado == false)
    {
        std::cout << "No se encontraron acciones para ese partido." << std::endl;
    }
}
