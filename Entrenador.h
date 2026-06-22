#pragma once

#include "Persona.h"


class Entrenador : public Persona {

private :
     int _IdClub;
     int _IdEntrenador;
public :

     Entrenador ();

     void cargar (int idClub = -1);
     void mostrar ();
     




     int get_IdClub ();
     int get_IdEntrenador ();

     void set_idclub(int idclub);
     void set_idEntrenador(int idEntrenador);


};
