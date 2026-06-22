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
    int idclub, dni;
    char nombre[30], apellido[30];

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
    if (!clubAsociado.get_activo()) {
        std::cout << "ERROR: Club INACTIVO. No se puede contratar entrenador." << std::endl;
        return;
    }
    set_idclub(idclub);

    std::cout << "Cargando Datos del Tecnico:" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    bool nombreValido = false;
    do {
        std::cout << "Ingrese nombre: ";
        std::cin >> nombre;
        if (!soloLetras(nombre)) {
            std::cout << "ERROR: Solo se permiten letras." << std::endl;
        } else {
            nombreValido = true;
        }
    } while (!nombreValido);
    set_nombre(nombre);

    bool apellidoValido = false;
    do {
        std::cout << "Ingrese apellido: ";
        std::cin >> apellido;
        if (!soloLetras(apellido)) {
            std::cout << "ERROR: Solo se permiten letras." << std::endl;
        } else {
            apellidoValido = true;
        }
    } while (!apellidoValido);
    set_apellido(apellido);

    //VALIDACI�N DNI �NICO
    JugadorArchivo archJ;
    EntrenadorArchivo archE;
    bool dniValido = false;
    do {
        std::cout << "Ingrese DNI: ";
        std::cin >> dni;

        if (archJ.buscarDNI(dni) != -1 || archE.buscarDNI(dni) != -1) {
            std::cout << "ERROR: El DNI ya est� registrado en el sistema. Intente de nuevo." << std::endl;
        } else {
            set_dni(dni);
            dniValido = true;
        }
    } while (!dniValido);

    //VALIDACI�N DE FECHA (18-80 A�OS)
    Fecha f;
    bool edadValida = false;
    do {
        std::cout << "Ingrese fecha de nacimiento: " << std::endl;
        f.cargar();

        int edad = 2026 - f.get_Anio();
        if (edad >= 18 && edad <= 80) {
            edadValida = true;
        } else {
            std::cout << "ERROR: El entrenador debe tener entre 18 y 80 a�os. Intente de nuevo.\n" << std::endl;
        }
    } while (!edadValida);
    set_fechanacimiento(f);
    set_activo(true);
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
