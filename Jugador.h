#pragma once
#include "Persona.h"

class Jugador : public Persona {
private:
    int _IdJugador;
    int _IdClub;
    int _NumeroCamiseta;
    char _Posicion[50];
    float _ValorMercado;

public:
    Jugador();

    void cargar();
    void mostrar();


    

    int get_idclub();
    int get_numerocamiseta();
    const char* get_posicion();
    float get_valormercado();
    int get_idjugador();


    void set_idclub(int idClub);
    void set_numerocamiseta(int numeroCamiseta);
    void set_posicion(const char posicion[]);
    void set_valormercado(float valorMercado);
    void set_idjugador(int idJugador);
};
