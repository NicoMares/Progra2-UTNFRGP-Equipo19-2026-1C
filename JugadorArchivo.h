#pragma once
#include "Archivo.h"
#include "Jugador.h"


class JugadorArchivo : public Archivo
{
public:
    JugadorArchivo();
    bool grabarEnDisco(Jugador jugador);
    Jugador leerDeDisco(int posicion);
    int buscarPorID(int idJugador);
    int buscarPorDNI(int dni);
    int contarRegistros();
    int obtenerProximoID();
    void ConsultarPorDNI();
    void consultarPorPosicion();
    void listarActivos();
    void listar();
    void listarPorClub();
    void listarPorDNI();
    void EliminarJugador();
    bool modificarEnDisco(Jugador jugador, int posicion);
private:
    const char* getNombreArchivo() const;

};

