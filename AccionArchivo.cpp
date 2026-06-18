#include <iostream>
#include <cstdio>
#include <cstring>

#include "AccionArchivo.h"
#include "JugadorArchivo.h"

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

    puntaje = calcularPuntaje(accion.get_tipoaccion(), posicionJugador);
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

int AccionArchivo::calcularPuntaje(const char tipoAccion[], const char posicionJugador[])
{
    if (strcmp(tipoAccion, "Gol") == 0)
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

    if (strcmp(tipoAccion, "Asistencia") == 0)
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

    if (strcmp(tipoAccion, "Amarilla") == 0)
    {
        return -2;
    }

    if (strcmp(tipoAccion, "Roja") == 0)
    {
        return -6;
    }

    if (strcmp(tipoAccion, "Falta") == 0)
    {
        return -1;
    }

    if (strcmp(tipoAccion, "Atajada") == 0)
    {
        if (strcmp(posicionJugador, "Arquero") == 0)
        {
            return 4;
        }

        return 0;
    }

    if (strcmp(tipoAccion, "Lesion") == 0)
    {
        return -3;
    }

    return 0;
}

void AccionArchivo::listarActivos()
{
    Accion accion;
    bool encontro = false;

    for (int pos = 0; pos < contarRegistros(); pos++)
    {
        accion = leerDeDisco(pos);
        if (accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "--------------------------------" << std::endl;
            encontro = true;
        }
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

    for (int pos = 0; pos < contarRegistros(); pos++)
    {
        accion = leerDeDisco(pos);
        accion.mostrar();
        std::cout << "--------------------------------" << std::endl;
        encontro = true;
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

    for (int pos = 0; pos < contarRegistros(); pos++)
    {
        accion = leerDeDisco(pos);
        if (accion.get_dnijugador() == dniBuscado && accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }
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

    for (int pos = 0; pos < contarRegistros(); pos++)
    {
        accion = leerDeDisco(pos);
        if (accion.get_idpartido() == idPartidoBuscado && accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }
    }

    if (encontrado == false)
    {
        std::cout << "No se encontraron acciones para ese partido." << std::endl;
    }
}
