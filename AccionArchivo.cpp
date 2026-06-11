#include "AccionArchivo.h"
#include "Accion.h"
#include <iostream>
#include "Jugador.h"
#include "JugadorArchivo.h"
#include <cstring>

AccionArchivo::AccionArchivo()
{

}

    bool AccionArchivo::grabarEnDisco() {
    FILE *pFile;
    bool result;

    pFile = fopen("acciones.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(this, sizeof(Accion), 1, pFile);

    fclose(pFile);

    return result;
}

bool AccionArchivo::leerDeDisco(int posicion) {

    FILE *pFile;
    bool result;

    pFile = fopen("acciones.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Accion), SEEK_SET);
    result = fread(this, sizeof(Accion), 1, pFile);

    fclose(pFile);

    return result;
}

void AccionArchivo::listarTodas() {
    
    Accion accionTemp;
    AccionArchivo archivo;

    int pos = 0;

    while (archivo.leerDeDisco(pos)) {
        accionTemp.mostrar();
        std::cout << "-----------------------------" << std::endl;
        pos++;
    }
}

void AccionArchivo::consultarPorJugador() {
    int dniBuscado;

    std::cout << "Ingrese DNI del jugador: ";
    std::cin >> dniBuscado;

    Accion accionTemp;
    AccionArchivo archivo;
    int pos = 0;
    bool encontrado = false;

    while (archivo.leerDeDisco(pos)) {
        if (accionTemp.get_dnijugador() == dniBuscado) {
            accionTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }

        pos++;
    }

    if (encontrado == false) {
        std::cout << "No se encontraron acciones para ese jugador." << std::endl;
    }
}



void AccionArchivo::consultarPorPartido() {
    int idPartidoBuscado;

    std::cout << "Ingrese ID del partido: ";
    std::cin >> idPartidoBuscado;

    Accion accionTemp;
    AccionArchivo archivo;
    int pos = 0;
    bool encontrado = false;

    while (archivo.leerDeDisco(pos)) {
        if (accionTemp.get_idpartido() == idPartidoBuscado) {
            accionTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }

        pos++;
    }

    if (encontrado == false) {
        std::cout << "No se encontraron acciones para ese partido." << std::endl;
    }
}

bool AccionArchivo::obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador) {
    Jugador jugadorTemp;
    JugadorArchivo archivo;

    int pos = 0;

    while (archivo.leerDeDisco(pos)) {
        if (jugadorTemp.get_dni() == dniJugador) {
            strcpy(posicionJugador, jugadorTemp.get_posicion());
            idClubJugador = jugadorTemp.get_idclub();
            return true;
        }

        pos++;
    }

    return false;
}