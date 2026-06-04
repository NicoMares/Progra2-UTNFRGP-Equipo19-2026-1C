#pragma once

class Fecha {
private :
    int _Dia;
    int _Mes;
    int _Anio;


public :

    Fecha();
    void cargar ();
    void mostrar ();

    int get_Dia ();
    int get_Mes ();
    int get_Anio ();

    void set_Dia (int dia);
    void set_Anio (int anio);
    void set_Mes  (int mes);




};

