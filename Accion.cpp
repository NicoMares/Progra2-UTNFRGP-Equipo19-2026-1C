#include <iostream>
#include <cstring>
#include <cstdio>
#include "Accion.h"
#include "Jugador.h"

Accion::Accion() {
    _IdAccion = 0;
    _IdPartido = 0;
    _DniJugador = 0;
    _IdClub = 0;
    _Minuto = 0;
    strcpy(_TipoAccion, "");
    _Puntaje = 0;
    _Positiva = true;
    _Activo = true;
}

bool Accion::obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador) {
    Jugador jugadorTemp;
    int pos = 0;

    while (jugadorTemp.leerDeDisco(pos)) {
        if (jugadorTemp.get_dni() == dniJugador) {
            strcpy(posicionJugador, jugadorTemp.get_posicion());
            idClubJugador = jugadorTemp.get_idclub();
            return true;
        }

        pos++;
    }

    return false;
}

void Accion::seleccionarTipoAccion(char tipoAccion[]) {
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

int Accion::calcularPuntaje(const char tipoAccion[], const char posicionJugador[]) {

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

void Accion::cargar() {
    int idPartido;
    int dniJugador;
    int idClubJugador;
    int minuto;
    char posicionJugador[50];
    char tipoAccion[50];

    int siguienteId = 1;
    FILE *pFile = fopen("acciones.dat", "rb");

    if (pFile != NULL) {
        Accion accionTemp;

        while (fread(&accionTemp, sizeof(Accion), 1, pFile) == 1) {
            if (accionTemp.get_idaccion() >= siguienteId) {
                siguienteId = accionTemp.get_idaccion() + 1;
            }
        }

        fclose(pFile);
    }

    set_idaccion(siguienteId);

    std::cout << "ID ACCION ASIGNADO: " << _IdAccion << std::endl;

    std::cout << "INGRESE ID DEL PARTIDO: ";
    std::cin >> idPartido;
    set_idpartido(idPartido);

    bool jugadorEncontrado = false;

    do {
        std::cout << "INGRESE DNI DEL JUGADOR: ";
        std::cin >> dniJugador;

        jugadorEncontrado = obtenerDatosJugador(dniJugador, posicionJugador, idClubJugador);

        if (jugadorEncontrado == false) {
            std::cout << "ERROR: No existe un jugador con ese DNI." << std::endl;
        }

    } while (jugadorEncontrado == false);

    set_dnijugador(dniJugador);
    set_idclub(idClubJugador);

    std::cout << "POSICION DEL JUGADOR: " << posicionJugador << std::endl;
    std::cout << "ID CLUB DEL JUGADOR: " << idClubJugador << std::endl;

    std::cout << "INGRESE MINUTO DE LA ACCION: ";
    std::cin >> minuto;
    set_minuto(minuto);

    seleccionarTipoAccion(tipoAccion);
    set_tipoaccion(tipoAccion);

    set_puntaje(calcularPuntaje(tipoAccion, posicionJugador));

    if (_Puntaje >= 0) {
        set_positiva(true);
    }
    else {
        set_positiva(false);
    }

    set_activo(true);

    std::cout << "PUNTAJE ASIGNADO: " << _Puntaje << std::endl;
}

void Accion::mostrar() {
    std::cout << "ID ACCION: " << _IdAccion << std::endl;
    std::cout << "ID PARTIDO: " << _IdPartido << std::endl;
    std::cout << "DNI JUGADOR: " << _DniJugador << std::endl;
    std::cout << "ID CLUB: " << _IdClub << std::endl;
    std::cout << "MINUTO: " << _Minuto << std::endl;
    std::cout << "TIPO DE ACCION: " << _TipoAccion << std::endl;
    std::cout << "PUNTAJE: " << _Puntaje << std::endl;

    std::cout << "POSITIVA: ";
    if (_Positiva == true) {
        std::cout << "SI" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }

    std::cout << "ACTIVA: ";
    if (_Activo == true) {
        std::cout << "SI" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
}

bool Accion::grabarEnDisco() {
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

bool Accion::leerDeDisco(int posicion) {
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

void Accion::listarTodas() {
    Accion accionTemp;
    int pos = 0;

    while (accionTemp.leerDeDisco(pos)) {
        accionTemp.mostrar();
        std::cout << "-----------------------------" << std::endl;
        pos++;
    }
}

void Accion::consultarPorJugador() {
    int dniBuscado;

    std::cout << "Ingrese DNI del jugador: ";
    std::cin >> dniBuscado;

    Accion accionTemp;
    int pos = 0;
    bool encontrado = false;

    while (accionTemp.leerDeDisco(pos)) {
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

void Accion::consultarPorPartido() {
    int idPartidoBuscado;

    std::cout << "Ingrese ID del partido: ";
    std::cin >> idPartidoBuscado;

    Accion accionTemp;
    int pos = 0;
    bool encontrado = false;

    while (accionTemp.leerDeDisco(pos)) {
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

int Accion::get_idaccion() {
    return _IdAccion;
}

int Accion::get_idpartido() {
    return _IdPartido;
}

int Accion::get_dnijugador() {
    return _DniJugador;
}

int Accion::get_idclub() {
    return _IdClub;
}

int Accion::get_minuto() {
    return _Minuto;
}

const char* Accion::get_tipoaccion() {
    return _TipoAccion;
}

int Accion::get_puntaje() {
    return _Puntaje;
}

bool Accion::get_positiva() {
    return _Positiva;
}

bool Accion::get_activo() {
    return _Activo;
}

void Accion::set_idaccion(int idAccion) {
    _IdAccion = idAccion;
}

void Accion::set_idpartido(int idPartido) {
    _IdPartido = idPartido;
}

void Accion::set_dnijugador(int dniJugador) {
    _DniJugador = dniJugador;
}

void Accion::set_idclub(int idClub) {
    _IdClub = idClub;
}

void Accion::set_minuto(int minuto) {
    _Minuto = minuto;
}

void Accion::set_tipoaccion(const char tipoAccion[]) {
    strcpy(_TipoAccion, tipoAccion);
}

void Accion::set_puntaje(int puntaje) {
    _Puntaje = puntaje;
}

void Accion::set_positiva(bool positiva) {
    _Positiva = positiva;
}

void Accion::set_activo(bool activo) {
    _Activo = activo;
}
