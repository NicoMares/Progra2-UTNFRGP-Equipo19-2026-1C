#pragma once
#include "Club.h"

class PosicionTabla {
private:
    Club _club;
    int _golesFavor;
    int _golesContra;
    int _diferenciaGol;
    int _puntos;

public:
    PosicionTabla();

    Club getClub();
    int getGolesFavor();
    int getGolesContra();
    int getDiferenciaGol();
    int getPuntos();

    void setClub(Club club);
    void setGolesFavor(int golesFavor);
    void setGolesContra(int golesContra);
    void setDiferenciaGol(int diferenciaGol);
    void setPuntos(int puntos);

    bool superaA(PosicionTabla otra);
};
