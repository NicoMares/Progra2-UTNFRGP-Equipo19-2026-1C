#include <iostream>
#include <cstdio>
#include "Entrenador.h"
#include "EntrenadorArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"

Entrenador::Entrenador() {
    _IdClub = -1;
    _IdEntrenador = 0;
}

void Entrenador::cargar(int idClub) {
    int idclub;
    EntrenadorArchivo archivo;
    set_idEntrenador(archivo.obtenerProximoID());
    std::cout << "ID ENTRENADOR ASIGNADO: " << _IdEntrenador << std::endl;

    if (idClub != -1) {
        idclub = idClub;
    } else {
        std::cout << "Ingrese el ID del club al que pertenece: ";
        std::cin >> idclub;
    }

    ClubArchivo archClub;
    int pos = archClub.buscarPorID(idclub);

    if (pos == -1) {
        std::cout << "ERROR: No existe un club con ese ID." << std::endl;
        return;
    }

    Club clubAsociado = archClub.leerDeDisco(pos);

    if (clubAsociado.get_activo() == false) {
        std::cout << "ERROR: El club se encuentra INACTIVO. No se puede contratar entrenador." << std::endl;
        return;
    }

    set_idclub(idclub);

    std::cout << "Cargando Datos del Tecnico:" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    Persona::cargar();
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
