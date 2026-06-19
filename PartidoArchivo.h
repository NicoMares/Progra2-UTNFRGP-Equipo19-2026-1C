#pragma once
#include "Archivo.h"
#include "Partido.h"

class PartidoArchivo : public Archivo {
public:
    bool grabarEnDisco(Partido partido);
    Partido leerDeDisco(int posicion);
    bool modificarEnDisco(Partido partido, int posicion);
    int contarRegistros();

    void listarPorJornada(int jornadaBuscada);
    void generarFixtureTorneo();
private:
    const char* getNombreArchivo() const;
};
