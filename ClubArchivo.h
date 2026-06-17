#pragma once
#include "Club.h"
class ClubArchivo
{
public:


    ClubArchivo();
    bool grabarEnDisco();
    bool leerDeDisco(int posicion);
    bool modificarEnDisco(int posicion);
    void eliminarDeDisco();
    void mostrarPorID();
    void mostrarClubes();
    void mostrarCout();

private:



};

