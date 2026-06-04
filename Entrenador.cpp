#include <iostream>
#include "Entrenador.h"

Entrenador::Entrenador() {
    _IdClub = -1;
}

void Entrenador::cargar() {
    int idclub;

    Persona::cargar();

    std::cout << "INGRESE ID DEL CLUB " << std::endl;
    std::cin >> idclub;
    set_idclub(idclub);
}

void Entrenador::mostrar() {
    Persona::mostrar();

    std::cout << "ID CLUB: " << _IdClub << std::endl;
}

/* HACER METODOS PARA INTERACTUAR CON EL DISCO */
bool Entrenador::grabarEnDisco() {
    return false;
}

bool Entrenador::leerDisco(int posicion) {
    return false;
}

int Entrenador::get_IdClub ()  {
    return _IdClub;
}

void Entrenador::set_idclub(int idClub) {
    _IdClub = idClub;
}
