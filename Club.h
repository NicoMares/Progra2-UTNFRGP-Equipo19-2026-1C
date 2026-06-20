#pragma once
#include "Fecha.h"

class Club {

private:
    int _IdClub;
    char _Nombre[50];
    char _Presidente[50];
    Fecha _FechaFundacion;
    int _CantidadTrofeos;
    int _CantidadDescensos;
    int _Racha[16];
    bool _Activo;

public:
    Club();

    void mostrar();
    void cargar();
    void mostrarRacha();
    void CalcularPuntos();

    int get_idclub();
    const char* get_nombre();
    const char* get_presidente();
    Fecha get_fechafundacion();
    int get_cantidadtrofeos();
    int get_cantidaddescensos();
    int get_racha(int jornada);
    bool get_activo();

    void set_idclub(int idClub);
    void set_nombre(const char nombre[]);
    void set_presidente(const char presidente[]);
    void set_fechafundacion(Fecha fechaFundacion);
    void set_cantidadtrofeos(int cantidadTrofeos);
    void set_cantidaddescensos(int cantidadDescensos);
    void set_racha(int jornada, int resultado);
    void set_activo(bool activo);
};
