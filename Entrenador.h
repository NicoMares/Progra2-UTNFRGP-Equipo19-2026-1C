#pragma once

#include "Persona.h"


class Entrenador : public Persona {

private :
     int _IdClub;
public :

     Entrenador ();

     void cargar ();
     void mostrar ();

     bool grabarEnDisco ();
     bool leerDisco (int posicion);

     int get_IdClub ();

     void set_idclub(int idclub);



};
