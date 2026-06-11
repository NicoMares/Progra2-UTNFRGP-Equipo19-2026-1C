#pragma once
#include "Jugador.h"


class JugadorArchivo
{
public:

    JugadorArchivo();
    bool grabarEnDisco();
    bool leerDeDisco(int posicion); 
    void ConsultarPorDNI();
    void consultarPorPosicion();
    void TodosJugadores();
    void listarPorClub();
    void ListarDni();
    void EliminarJugador();
    bool modificarEnDisco(int posicion);

private:

};

