#include <iostream>
#include <cstdio>
#include <cstring>

#include "AccionArchivo.h"
#include "Jugador.h"

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

bool AccionArchivo::leerDeDisco(int posicion, Accion &accion)
{
    FILE *pFile;
    bool result;

    pFile = fopen("acciones.dat", "rb");

    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * sizeof(Accion), SEEK_SET);
    result = fread(&accion, sizeof(Accion), 1, pFile);

    fclose(pFile);

    return result;
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
    FILE *pFile;
    Jugador jugador;
    bool encontrado = false;

    pFile = fopen("jugadores.dat", "rb");

    if (pFile == NULL)
    {
        return false;
    }

    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1)
    {
        if (jugador.get_dni() == dniJugador && jugador.get_activo() == true)
        {
            strcpy(posicionJugador, jugador.get_posicion());
            idClubJugador = jugador.get_idclub();
            encontrado = true;
            break;
        }
    }

    fclose(pFile);

    return encontrado;
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

void AccionArchivo::listarTodas()
{
    Accion accion;
    int pos = 0;
    bool encontro = false;

    while (leerDeDisco(pos, accion))
    {
        if (accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontro = true;
        }

        pos++;
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
    int pos = 0;
    bool encontrado = false;

    std::cout << "INGRESE DNI DEL JUGADOR: ";
    std::cin >> dniBuscado;

    while (leerDeDisco(pos, accion))
    {
        if (accion.get_dnijugador() == dniBuscado && accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }

        pos++;
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
    int pos = 0;
    bool encontrado = false;

    std::cout << "INGRESE ID DEL PARTIDO: ";
    std::cin >> idPartidoBuscado;

    while (leerDeDisco(pos, accion))
    {
        if (accion.get_idpartido() == idPartidoBuscado && accion.get_activo() == true)
        {
            accion.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }

        pos++;
    }

    if (encontrado == false)
    {
        std::cout << "No se encontraron acciones para ese partido." << std::endl;
    }
}
