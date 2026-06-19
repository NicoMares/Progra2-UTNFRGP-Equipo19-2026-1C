#pragma once

#include "Archivo.h"
#include "Accion.h"

class AccionArchivo : public Archivo
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
    const char* getNombreArchivo() const;
    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    int calcularPuntaje(const char tipoAccion[], const char posicionJugador[]);
};
