#pragma once
#include "Entrenador.h"

class EntrenadorArchivo
{
public:
    EntrenadorArchivo();
    void mostrarDTPorID();
    void listarActivos();
    void listar();
    void EliminarEntrenador();
     bool grabarEnDisco (Entrenador entrenador);
     Entrenador leerDisco (int posicion);
     bool modificarEnDisco(Entrenador entrenador, int posicion);
     int buscarPorID(int idEntrenador);
     int contarRegistros();
     int obtenerProximoID();
private:

};

