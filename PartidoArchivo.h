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
    void simularSiguienteJornada();
    void listarTablaPosiciones();
    int obtenerSiguienteJornadaAJugarse();

    int calcularGolesFavor(int idClub);
    int calcularGolesContra(int idClub);
    int calcularDiferenciaGol(int idClub);

private:
    void aplicarResultadosFinales();
};
