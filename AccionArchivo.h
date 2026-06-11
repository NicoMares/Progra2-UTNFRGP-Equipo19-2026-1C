#pragma once
#include "Accion.h"
class AccionArchivo
{
public:
    bool grabarEnDisco();
    bool leerDeDisco(int posicion);
    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    void listarTodas();
    void consultarPorJugador();
    void consultarPorPartido();
    void eliminarDeDisco();
    void CoutGuardar();




private:

};

