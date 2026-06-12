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

void AccionArchivo::seleccionarTipoAccion(char tipoAccion[]) {
    int opcion;

    std::cout << "Seleccione tipo de accion: " << std::endl;
    std::cout << "1 - Gol" << std::endl;
    std::cout << "2 - Asistencia" << std::endl;
    std::cout << "3 - Tarjeta amarilla" << std::endl;
    std::cout << "4 - Tarjeta roja" << std::endl;
    std::cout << "5 - Falta cometida" << std::endl;
    std::cout << "6 - Atajada" << std::endl;
    std::cout << "7 - Lesion" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            strcpy(tipoAccion, "Gol");
            break;
        case 2:
            strcpy(tipoAccion, "Asistencia");
            break;
        case 3:
            strcpy(tipoAccion, "Amarilla");
            break;
        case 4:
            strcpy(tipoAccion, "Roja");
            break;
        case 5:
            strcpy(tipoAccion, "Falta");
            break;
        case 6:
            strcpy(tipoAccion, "Atajada");
            break;
        case 7:
            strcpy(tipoAccion, "Lesion");
            break;
        default:
            strcpy(tipoAccion, "Sin definir");
            break;
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

int AccionArchivo::calcularPuntaje(const char tipoAccion[], const char posicionJugador[]) {

    bool esArquero =
        strcmp(posicionJugador, "Arquero") == 0 ||
        strcmp(posicionJugador, "arquero") == 0;

    bool esDefensor =
        strcmp(posicionJugador, "Defensor") == 0 ||
        strcmp(posicionJugador, "defensor") == 0;

    bool esMediocampo =
        strcmp(posicionJugador, "Mediocampo") == 0 ||
        strcmp(posicionJugador, "mediocampo") == 0 ||
        strcmp(posicionJugador, "Mediocampista") == 0 ||
        strcmp(posicionJugador, "mediocampista") == 0;

    bool esDelantero =
        strcmp(posicionJugador, "Delantero") == 0 ||
        strcmp(posicionJugador, "delantero") == 0;

    if (strcmp(tipoAccion, "Gol") == 0) {
        if (esArquero) {
            return 10;
        }
        if (esDefensor) {
            return 8;
        }
        if (esMediocampo) {
            return 6;
        }
        if (esDelantero) {
            return 5;
        }

        return 5;
    }

    if (strcmp(tipoAccion, "Asistencia") == 0) {
        if (esArquero) {
            return 6;
        }
        if (esDefensor) {
            return 5;
        }
        if (esMediocampo) {
            return 4;
        }
        if (esDelantero) {
            return 3;
        }

        return 3;
    }

    if (strcmp(tipoAccion, "Amarilla") == 0) {
        return -2;
    }

    if (strcmp(tipoAccion, "Roja") == 0) {
        return -6;
    }

    if (strcmp(tipoAccion, "Falta") == 0) {
        return -1;
    }

    if (strcmp(tipoAccion, "Atajada") == 0) {
        if (esArquero) {
            return 4;
        }

        return 0;
    }

    if (strcmp(tipoAccion, "Lesion") == 0) {
        return -3;
    }

    return 0;
}