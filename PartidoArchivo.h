#pragma once
#include "Partido.h"
#include "PosicionTabla.h"

class PartidoArchivo {
public:
    bool grabarEnDisco(Partido partido);
    Partido leerDeDisco(int posicion);
    bool modificarEnDisco(Partido partido, int posicion);
    int contarRegistros();

    int buscarPorID(int idPartido);
    void mostrarPorID();
    void listarPorJornada(int jornadaBuscada);
    void generarFixtureTorneo();
    void VerJornada();
    void VerPartidos();
    void simularSiguienteJornada();
    void simularTorneoCompleto();
    void listarTablaPosiciones();
    void listarRachasClubesOrdenadas();
    void SuspenderPartido();
    void CargarPartido();
    void mostrarPorID();
    int obtenerSiguienteJornadaAJugarse();

    int calcularGolesFavor(int idClub);
    int calcularGolesContra(int idClub);
    int calcularDiferenciaGol(int idClub);
    int buscarPorID(int idPartido);
    
private:
    void aplicarResultadosFinales();
    int cargarTabla(PosicionTabla filas[]);
    bool existeClub(int idsClubes[], int cantidad, int idClub);
};
