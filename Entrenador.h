#pragma once

#include "Persona.h"


class Entrenador : public Persona {

private :
     int _IdClub;
     int _IdEntrenador;
public :

     Entrenador ();

     void cargar ();
     void mostrar ();
     void mostrarDTPorID();


     bool grabarEnDisco ();
     bool leerDisco (int posicion);

     int get_IdClub ();
     int get_IdEntrenador ();

     void set_idclub(int idclub);
     void set_idEntrenador(int idEntrenador);


};
