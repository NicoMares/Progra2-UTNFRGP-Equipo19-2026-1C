#include "PosicionTabla.h"
#include <cstring>

PosicionTabla::PosicionTabla()
{
    _golesFavor = 0;
    _golesContra = 0;
    _diferenciaGol = 0;
    _puntos = 0;
}

Club PosicionTabla::getClub()
{
    return _club;
}

int PosicionTabla::getGolesFavor()
{
    return _golesFavor;
}

int PosicionTabla::getGolesContra()
{
    return _golesContra;
}

int PosicionTabla::getDiferenciaGol()
{
    return _diferenciaGol;
}

int PosicionTabla::getPuntos()
{
    return _puntos;
}

void PosicionTabla::setClub(Club club)
{
    _club = club;
}

void PosicionTabla::setGolesFavor(int golesFavor)
{
    _golesFavor = golesFavor;
}

void PosicionTabla::setGolesContra(int golesContra)
{
    _golesContra = golesContra;
}

void PosicionTabla::setDiferenciaGol(int diferenciaGol)
{
    _diferenciaGol = diferenciaGol;
}

void PosicionTabla::setPuntos(int puntos)
{
    _puntos = puntos;
}

bool PosicionTabla::superaA(PosicionTabla otra)
{
    if (_puntos != otra.getPuntos())
    {
        return _puntos > otra.getPuntos();
    }

    if (_diferenciaGol != otra.getDiferenciaGol())
    {
        return _diferenciaGol > otra.getDiferenciaGol();
    }

    if (_golesFavor != otra.getGolesFavor())
    {
        return _golesFavor > otra.getGolesFavor();
    }

    Club otroClub = otra.getClub();
    return strcmp(_club.get_nombre(), otroClub.get_nombre()) < 0;
}
