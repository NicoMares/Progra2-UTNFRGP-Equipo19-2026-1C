#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"
#include "JugadorArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include "EntrenadorArchivo.h"

Jugador::Jugador() {
    _IdJugador = 0;
    _IdClub = 0;
    _NumeroCamiseta = 0;
    strcpy(_Posicion, "");
    _ValorMercado = 0;
}

void Jugador::cargar() {
    Persona::cargar();


    JugadorArchivo archivo;
    set_idjugador(archivo.obtenerProximoID());
    std::cout << "ID JUGADOR ASIGNADO: " << _IdJugador << std::endl;

    // Validación de Club
    int idClub;
    std::cout << "Ingrese ID del club: ";
    std::cin >> idClub;

    ClubArchivo archClub;
    int pos = archClub.buscarPorID(idClub);


    if (pos == -1 || !archClub.leerDeDisco(pos).get_activo()) {
        std::cout << "ERROR: El club no es válido o no existe." << std::endl;
        return;
    }
    set_idclub(idClub);


    int numeroCamiseta;
    char posicion[30];
    float valorMercado;

    std::cout << "Ingrese número de camiseta: ";
    std::cin >> numeroCamiseta;
    set_numerocamiseta(numeroCamiseta);

    std::cout << "Ingrese posición: ";
    std::cin >> posicion;
    set_posicion(posicion);

    std::cout << "Ingrese valor de mercado: ";
    std::cin >> valorMercado;
    set_valormercado(valorMercado);

    set_activo(true);
}

void Jugador::mostrar() {
    Persona::mostrar();

    std::cout << "ID Jugador: " << _IdJugador << std::endl;

    ClubArchivo archClub;
    int posClub = archClub.buscarPorID(_IdClub);
    if (posClub != -1) {
        std::cout << "Club: " << archClub.leerDeDisco(posClub).get_nombre() << std::endl;
    } else {
        std::cout << "Club: (desconocido)" << std::endl;
    }
    std::cout << "Número de camiseta: " << _NumeroCamiseta << std::endl;
    std::cout << "Posición: " << _Posicion << std::endl;
    std::cout << "Valor de mercado: $" << (int)_ValorMercado << std::endl;
}

int Jugador::get_idjugador() {
    return _IdJugador;
}

int Jugador::get_idclub() {
    return _IdClub;
}

int Jugador::get_numerocamiseta() {
    return _NumeroCamiseta;
}

const char* Jugador::get_posicion() {
    return _Posicion;
}

float Jugador::get_valormercado() {
    return _ValorMercado;
}
/*cpnexion club*/
void Jugador::set_idjugador(int idJugador) {
    _IdJugador = idJugador;
}

void Jugador::set_idclub(int idClub) {
    _IdClub = idClub;
}
/*SIRVE O NO SIRVE ? */
void Jugador::set_numerocamiseta(int numeroCamiseta) {
    _NumeroCamiseta = numeroCamiseta;
}

void Jugador::set_posicion(const char posicion[]) {
    strcpy(_Posicion, posicion);
}
/*SIRVE O NO SIRVE ? */
void Jugador::set_valormercado(float valorMercado) {
    _ValorMercado = valorMercado;
}
