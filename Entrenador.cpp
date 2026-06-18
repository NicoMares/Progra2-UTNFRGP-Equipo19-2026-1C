#include <iostream>
#include <cstdio>
#include "Entrenador.h"
#include "EntrenadorArchivo.h"

Entrenador::Entrenador() {
    _IdClub = -1;
    _IdEntrenador = 0;
}
// LEE Y ASIGNA ID AUTOINCREMENTAL  EN LA CARGA
void Entrenador::cargar() {
    int idclub;
    EntrenadorArchivo archivo;
    set_idEntrenador(archivo.obtenerProximoID());
    std::cout << "ID ENTRENADOR ASIGNADO: " << _IdEntrenador << std::endl;

    Persona::cargar();
    // DEBERIA  CHEQUEAR QUE EL ID DEL CLUB EXISTE ANTES DE ESCRIBIR
    std::cout << "INGRESE ID DEL CLUB: ";
    std::cin >> idclub;
    set_idclub(idclub);
}

void Entrenador::mostrar() {
    Persona::mostrar();

    std::cout << "ID ENTRENADOR: " << _IdEntrenador << std::endl;
    std::cout << "ID CLUB: " << _IdClub << std::endl;
}



int Entrenador::get_IdClub ()  {
    return _IdClub;
}

int Entrenador::get_IdEntrenador() {
    return _IdEntrenador;
}

void Entrenador::set_idclub(int idClub) {
    _IdClub = idClub;
}

void Entrenador::set_idEntrenador(int idEntrenador) {
  _IdEntrenador = idEntrenador;
}
