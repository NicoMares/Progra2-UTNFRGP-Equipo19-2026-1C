#include <iostream>
#include <cstdio>
#include "Entrenador.h"
#include "utils.h"
#include "EntrenadorArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include "JugadorArchivo.h"

Entrenador::Entrenador() {
    _IdClub = -1;
    _IdEntrenador = 0;
}

void Entrenador::cargar(int idClub) {

    Persona::cargar();


    EntrenadorArchivo archivo;
    set_idEntrenador(archivo.obtenerProximoID());
    std::cout << "ID ENTRENADOR ASIGNADO: " << _IdEntrenador << std::endl;


    int idclub;
    if (idClub != -1) {
        idclub = idClub;
    } else {
        std::cout << "Ingrese el ID del club al que pertenece: ";
        std::cin >> idclub;
    }

    ClubArchivo archClub;
    int pos = archClub.buscarPorID(idclub);

    if (pos == -1 || !archClub.leerDeDisco(pos).get_activo()) {
        std::cout << "ERROR: El club no existe o está inactivo." << std::endl;
        return;
    }
    set_idclub(idclub);


    set_activo(true);
}

void Entrenador::mostrar() {
    Persona::mostrar();

    std::cout << "ID ENTRENADOR: " << _IdEntrenador << std::endl;

    ClubArchivo archivoClub;
    int pos = archivoClub.buscarPorID(_IdClub);
    if (pos != -1) {
        Club club = archivoClub.leerDeDisco(pos);
        std::cout << "CLUB: " << club.get_nombre() << std::endl;
    } else {
        std::cout << "CLUB: (no encontrado)" << std::endl;
    }
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
