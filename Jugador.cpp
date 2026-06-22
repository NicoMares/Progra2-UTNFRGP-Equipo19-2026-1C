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
    int idClub, numeroCamiseta, dni;
    char posicion[30], nombre[30], apellido[30];
    float valorMercado;

    JugadorArchivo archivo;
    set_idjugador(archivo.obtenerProximoID());
    std::cout << "ID JUGADOR ASIGNADO: " << _IdJugador << std::endl;

    //VALIDACIÓN DE CLUB
    std::cout << "Ingrese ID del club: ";
    std::cin >> idClub;
    ClubArchivo archClub;
    int pos = archClub.buscarPorID(idClub);
    if (pos == -1) {
        std::cout << "ERROR: El club no existe." << std::endl;
        return;
    }
    Club clubAsociado = archClub.leerDeDisco(pos);
    if (!clubAsociado.get_activo()) {
        std::cout << "ERROR: El club está INACTIVO." << std::endl;
        return;
    }
    set_idclub(idClub);

    std::cout << "Ingrese nombre: "; std::cin >> nombre; set_nombre(nombre);
    std::cout << "Ingrese apellido: "; std::cin >> apellido; set_apellido(apellido);

    //VALIDACIÓN DNI ÚNICO
    JugadorArchivo archJ;
    EntrenadorArchivo archE;
    bool dniValido = false;
    do {
        std::cout << "Ingrese DNI: ";
        std::cin >> dni;

        if (archJ.buscarDNI(dni) != -1 || archE.buscarDNI(dni) != -1) {
            std::cout << "ERROR: El DNI ya está registrado en el sistema. Intente de nuevo." << std::endl;
        } else {
            set_dni(dni);
            dniValido = true;
        }
    } while (!dniValido);

    // VALIDACIÓN DE FECHA (15-45 AÑOS)
    Fecha f;
    bool edadValida = false;
    do {
        std::cout << "Ingrese fecha de nacimiento: " << std::endl;
        f.cargar();

        int edad = 2026 - f.get_Anio();
        if (edad >= 15 && edad <= 45) {
            edadValida = true;
        } else {
            std::cout << "ERROR: El jugador debe tener entre 15 y 45 años. Intente de nuevo.\n" << std::endl;
        }
    } while (!edadValida);
    set_fechanacimiento(f);
    set_activo(true);

    std::cout << "Ingrese número de camiseta: "; std::cin >> numeroCamiseta; set_numerocamiseta(numeroCamiseta);
    std::cout << "Ingrese posición: "; std::cin >> posicion; set_posicion(posicion);
    std::cout << "Ingrese valor de mercado: "; std::cin >> valorMercado; set_valormercado(valorMercado);
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
