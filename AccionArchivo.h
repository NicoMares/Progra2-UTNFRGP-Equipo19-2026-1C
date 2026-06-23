#pragma once

#include "Accion.h"
#include "Partido.h"

class AccionArchivo
{
public:
    bool grabarEnDisco(Accion accion);
    Accion leerDeDisco(int posicion);
    int contarRegistros();

    bool completarDatosAccion(Accion &accion);
    /* RANDOMIZADOR DE ACCIONES */
    void simularAccionesDePartido(Partido partido);
    int contarGolesPorPartidoYClub(int idPartido, int idClub);
    void vaciarArchivo();

    void listarActivos();
    void listar();
    void consultarPorJugador();
    void consultarPorPartido();
    /* TABLA DE RENDIMIENTO DE JUGADORES */
    int calcularPuntajeTotalJugador(int dniJugador);
    void listarRendimientoJugadores();

private:
    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    int calcularPuntaje(int idAccion, const char posicionJugador[]);
    int obtenerTipoAccionRandom();
    void configurarTipoAccion(Accion &accion, int idAccion);
    void mostrarConDetalles(Accion accion);
};
