#pragma once
#include "Archivo.h"
#include "Club.h"
class ClubArchivo : public Archivo
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

private:
    const char* getNombreArchivo() const;

};

