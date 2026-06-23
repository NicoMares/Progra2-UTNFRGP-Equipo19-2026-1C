#pragma once
#include "Fecha.h"
#include "Persona.h"

class Club {

private:
    int _IdClub;
    char _Nombre[50];
    Persona _Presidente;
    Fecha _FechaFundacion;
    int _CantidadTrofeos;
    int _CantidadDescensos;
    int _Racha[16];
    bool _Activo;
    int _Division;

public:
    Club();

    void mostrar();
    void cargar();
    void mostrarRacha();
    int calcularPuntos();

    int get_idclub();
    const char* get_nombre();
    Persona get_presidente();
    Fecha get_fechafundacion();
    int get_cantidadtrofeos();
    int get_cantidaddescensos();
    int get_racha(int jornada);
    bool get_activo();

    void set_idclub(int idClub);
    void set_nombre(const char nombre[]);
    void set_presidente(Persona presidente);
    void set_fechafundacion(Fecha fechaFundacion);
    void set_cantidadtrofeos(int cantidadTrofeos);
    void set_cantidaddescensos(int cantidadDescensos);
    void set_racha(int jornada, int resultado);
    void set_activo(bool activo);
    int get_division();
    void set_division(int division);
};
