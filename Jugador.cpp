#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"
#include "JugadorArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"


Jugador::Jugador() {
    _IdJugador = 0;
    _IdClub = 0;
    _NumeroCamiseta = 0;
    strcpy(_Posicion, "");
    _ValorMercado = 0;
}

void Jugador::cargar() {
    int idClub;
    int numeroCamiseta;
    char posicion[30];
    float valorMercado;

    JugadorArchivo archivo;
    set_idjugador(archivo.obtenerProximoID());
    std::cout << "ID JUGADOR ASIGNADO: " << _IdJugador << std::endl;

    // VALIDACIÓN DEL CLUB
    std::cout << "Ingrese ID del club: ";
    std::cin >> idClub;

    ClubArchivo archClub;

    int pos = archClub.buscarPorID(idClub);

    if (pos == -1) {
        std::cout << "ERROR: El club con ID " << idClub << " no existe en el sistema." << std::endl;
        return;
    }

    Club clubAsociado = archClub.leerDeDisco(pos);

    if (clubAsociado.get_activo() == false) {
        std::cout << "ERROR: El club se encuentra INACTIVO. No se pueden fichar jugadores." << std::endl;
        return;
    }

    set_idclub(idClub);


    Persona::cargar();

    std::cout << "Ingrese número de camiseta: ";
    std::cin >> numeroCamiseta;
    set_numerocamiseta(numeroCamiseta);

    std::cout << "Ingrese posición: ";
    std::cin >> posicion;
    set_posicion(posicion);

    std::cout << "Ingrese valor de mercado: ";
    std::cin >> valorMercado;
    set_valormercado(valorMercado);
}

void Jugador::mostrar() {
    Persona::mostrar();

    std::cout << "ID Jugador: " << _IdJugador << std::endl;
    std::cout << "ID Club: " << _IdClub << std::endl;
    std::cout << "Número de camiseta: " << _NumeroCamiseta << std::endl;
    std::cout << "Posición: " << _Posicion << std::endl;
    std::cout << "Valor de mercado: $" << _ValorMercado << std::endl;
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
