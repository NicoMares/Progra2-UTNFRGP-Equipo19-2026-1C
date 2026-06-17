#pragma once
#include "Partido.h"

class PartidoArchivo {
public:
    bool grabarEnDisco(Partido partido);
    bool leerDeDisco(int posicion, Partido &partido);
    bool modificarEnDisco(int posicion, Partido partido);
    int contarRegistros();

    void listarPorJornada(int jornadaBuscada);

    void generarFixtureTorneo();
};
