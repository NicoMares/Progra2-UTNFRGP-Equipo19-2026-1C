#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"
#include "JugadorArchivo.h"

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
    Persona::cargar();

    // DEBERIA CHEQUEAR SI EXISTE ANTES DE CARGARLO
    std::cout << "Ingrese ID del club: ";
    std::cin >> idClub;
    set_idclub(idClub);

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
