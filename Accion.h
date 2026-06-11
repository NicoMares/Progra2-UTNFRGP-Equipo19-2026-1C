#pragma once

class Accion {

private:
    int _IdAccion;
    int _IdPartido;
    int _DniJugador;
    int _IdClub;
    int _Minuto;
    char _TipoAccion[50];
    int _Puntaje;
    bool _Positiva;
    bool _Activo;

    bool obtenerDatosJugador(int dniJugador, char posicionJugador[], int &idClubJugador);
    void seleccionarTipoAccion(char tipoAccion[]);
    int calcularPuntaje(const char tipoAccion[], const char posicionJugador[]);

public:
    Accion();

    void cargar();
    void mostrar();

   

    

    int get_idaccion();
    int get_idpartido();
    int get_dnijugador();
    int get_idclub();
    int get_minuto();
    const char* get_tipoaccion();
    int get_puntaje();
    bool get_positiva();
    bool get_activo();

    void set_idaccion(int idAccion);
    void set_idpartido(int idPartido);
    void set_dnijugador(int dniJugador);
    void set_idclub(int idClub);
    void set_minuto(int minuto);
    void set_tipoaccion(const char tipoAccion[]);
    void set_puntaje(int puntaje);
    void set_positiva(bool positiva);
    void set_activo(bool activo);
};
