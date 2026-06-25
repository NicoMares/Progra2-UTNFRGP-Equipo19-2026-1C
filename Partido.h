#pragma once

class Partido {
private:
    int _idPartido;
    int _idClubLocal;
    int _idClubVisitante;
    int _jornada;
    int _golesLocal;
    int _golesVisitante;
    bool _jugado;
    bool _activo;
    bool _suspendido;

public:
    Partido();

    // Getters
    int get_idpartido();
    int get_idclublocal();
    int get_idclubvisitante();
    int get_jornada();
    int get_goleslocal();
    int get_golesvisitante();
    bool get_jugado();
    bool get_activo();
    bool get_suspendido();

    // Setters
    void set_idpartido(int id);
    void set_idclublocal(int idLocal);
    void set_idclubvisitante(int idVisitante);
    void set_jornada(int jornada);
    void set_goleslocal(int golesL);
    void set_golesvisitante(int golesV);
    void set_jugado(bool jugado);
    void set_activo(bool activo);
    void set_suspendido(bool suspendido);

    // Métodos de interfaz corta
    void mostrar();
};
