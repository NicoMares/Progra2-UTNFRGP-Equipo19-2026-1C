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
    void modificarEntrenador();
     bool grabarEnDisco (Entrenador entrenador);
     Entrenador leerDisco (int posicion);
     bool modificarEnDisco(Entrenador entrenador, int posicion);
     int buscarPorID(int idEntrenador);
     int buscarPorIdClub(int idClub);
     int contarRegistros();
     int obtenerProximoID();
     int buscarDNI(int dni);
private:

};

