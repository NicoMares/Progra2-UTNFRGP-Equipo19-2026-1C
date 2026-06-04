#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"

Jugador::Jugador() {
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

    Persona::cargar();

    std::cout << "Ingrese ID del club: ";
    std::cin >> idClub;
    set_idclub(idClub);

    std::cout << "Ingrese numero de camiseta: ";
    std::cin >> numeroCamiseta;
    set_numerocamiseta(numeroCamiseta);

    std::cout << "Ingrese posicion: ";
    std::cin >> posicion;
    set_posicion(posicion);

    std::cout << "Ingrese valor de mercado: ";
    std::cin >> valorMercado;
    set_valormercado(valorMercado);
}

void Jugador::mostrar() {
    Persona::mostrar();

    std::cout << "ID Club: " << _IdClub << std::endl;
    std::cout << "Numero de camiseta: " << _NumeroCamiseta << std::endl;
    std::cout << "Posicion: " << _Posicion << std::endl;
    std::cout << "Valor de mercado: " << _ValorMercado << std::endl;
}

bool Jugador::grabarEnDisco() {
    FILE *pFile;
    bool result;

    pFile = fopen("jugadores.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(this, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return result;
}

bool Jugador::leerDeDisco(int posicion) {
    FILE *pFile;
    bool result;

    pFile = fopen("jugadores.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    result = fread(this, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return result;
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
