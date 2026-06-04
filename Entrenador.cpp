#include <iostream>
#include <cstdio>
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

bool Entrenador::grabarEnDisco() {
    FILE *pFile;
    bool result;

    pFile = fopen("entrenadores.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(this, sizeof(Entrenador), 1, pFile);

    fclose(pFile);

    return result;
}

bool Entrenador::leerDisco(int posicion) {
    FILE *pFile;
    bool result;

    pFile = fopen("entrenadores.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Entrenador), SEEK_SET);
    result = fread(this, sizeof(Entrenador), 1, pFile);

    fclose(pFile);

    return result;
}

int Entrenador::get_IdClub ()  {
    return _IdClub;
}

void Entrenador::set_idclub(int idClub) {
    _IdClub = idClub;
}
