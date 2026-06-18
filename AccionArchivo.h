#pragma once

#include "Accion.h"

class AccionArchivo
{
public:
    bool grabarEnDisco(Accion accion);
    Accion leerDeDisco(int posicion);
    int contarRegistros();

    bool completarDatosAccion(Accion &accion);

    void listarActivos();
    void listar();
    void consultarPorJugador();
    void consultarPorPartido();

private:
    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    int calcularPuntaje(const char tipoAccion[], const char posicionJugador[]);
};
