#pragma once
#include "Fecha.h"

class Persona{
protected :
    char _Nombre [30];
    char _Apellido [30];
    int _Dni;
    Fecha _FechaNacimiento;
    bool _Activo;

public:

    Persona ();

    void cargar ();
    void mostrar ();


    const char * get_nombre();
    const char * get_apellido ();
    int get_dni ();
    bool get_activo ();
    Fecha get_fechanacimiento ();


    void set_nombre  (const char nombre []);
    void set_apellido (const char apellido []);
    void set_dni (int dni );
    void set_fechanacimiento (Fecha fecha_nacimiento);
    void set_activo(bool activo);




};
