#pragma once
#include "Club.h"
class ClubArchivo
{
public:
    ClubArchivo();
    bool grabarEnDisco(Club equipo);
    Club leerDeDisco(int posicion);
    bool modificarEnDisco(Club equipo, int posicion);
    int buscarPorID(int idClub);
    int contarRegistros();
    int obtenerProximoID();
    void eliminarDeDisco();
    void mostrarPorID();
    void listarActivos();
    void listar();
    void mostrarCout();

private:

};

