#pragma once

#include "Accion.h"

class AccionArchivo
{
public:
    bool grabarEnDisco(Accion accion);
    bool leerDeDisco(int posicion, Accion &accion);

    bool completarDatosAccion(Accion &accion);

    void listarTodas();
    void consultarPorJugador();
    void consultarPorPartido();

private:
    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    int calcularPuntaje(const char tipoAccion[], const char posicionJugador[]);
};
