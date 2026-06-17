#include "Partido.h"
#include <iostream>

Partido::Partido() {
    _idPartido = 0;
    _idClubLocal = 0;
    _idClubVisitante = 0;
    _jornada = 0;
    _golesLocal = 0;
    _golesVisitante = 0;
    _jugado = false;
    _activo = true;
}

// Getters
int Partido::get_idpartido() { return _idPartido; }
int Partido::get_idclublocal() { return _idClubLocal; }
int Partido::get_idclubvisitante() { return _idClubVisitante; }
int Partido::get_jornada() { return _jornada; }
int Partido::get_goleslocal() { return _golesLocal; }
int Partido::get_golesvisitante() { return _golesVisitante; }
bool Partido::get_jugado() { return _jugado; }
bool Partido::get_activo() { return _activo; }

// Setters
void Partido::set_idpartido(int id) { _idPartido = id; }
void Partido::set_idclublocal(int idLocal) { _idClubLocal = idLocal; }
void Partido::set_idclubvisitante(int idVisitante) { _idClubVisitante = idVisitante; }
void Partido::set_jornada(int jornada) { _jornada = jornada; }
void Partido::set_goleslocal(int golesL) { _golesLocal = golesL; }
void Partido::set_golesvisitante(int golesV) { _golesVisitante = golesV; }
void Partido::set_jugado(bool jugado) { _jugado = jugado; }
void Partido::set_activo(bool activo) { _activo = activo; }

void Partido::mostrar() {
    std::cout << " Partido ID: " << _idPartido << " | ";
    std::cout << "Club " << _idClubLocal << " vs. Club " << _idClubVisitante;
    if (_jugado) {
        std::cout << " [Resultado: " << _golesLocal << " - " << _golesVisitante << "]" << std::endl;
    } else {
        std::cout << " [PENDIENTE]" << std::endl;
    }
}
