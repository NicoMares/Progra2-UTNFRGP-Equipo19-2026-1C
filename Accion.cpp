#include <iostream>
#include <cstring>
#include <cstdio>
#include "Accion.h"
#include "Jugador.h"
#include "JugadorArchivo.h"
#include "AccionArchivo.h"

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
        AccionArchivo archivo;


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
