#pragma once
#include "Partido.h"

class PartidoArchivo {
public:
    bool grabarEnDisco(Partido partido);
    Partido leerDeDisco(int posicion);
    bool modificarEnDisco(Partido partido, int posicion);
    int contarRegistros();

    void listarPorJornada(int jornadaBuscada);
    void generarFixtureTorneo();
    void VerJornada();
    void VerPartidos();
};
