#pragma once
#include "Archivo.h"
#include "Entrenador.h"

class EntrenadorArchivo : public Archivo
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
     const char* getNombreArchivo() const;

};

