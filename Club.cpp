#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"

Club::Club()
{
    _IdClub = -1;
    strcpy(_Nombre, "");
    strcpy(_Presidente, "");
    _CantidadTrofeos = 0;
    _CantidadDescensos = 0;
    _Activo = true;

    for (int i = 0; i < 16; i++)
    {
        _Racha[i] = 0;
    }
}

void Club::cargar()
{
    int idClub;
    char nombre[50];
    char presidente[50];
    Fecha fechaFundacion;
    int cantidadTrofeos;
    int cantidadDescensos;

    std::cout << "INGRESE ID DEL CLUB: ";
    std::cin >> idClub;
    set_idclub(idClub);

    std::cout << "INGRESE NOMBRE DEL CLUB: ";
    std::cin >> nombre;
    set_nombre(nombre);

    std::cout << "INGRESE PRESIDENTE DEL CLUB: ";
    std::cin >> presidente;
    set_presidente(presidente);

    std::cout << "INGRESE FECHA DE FUNDACION: " << std::endl;
    fechaFundacion.cargar();
    set_fechafundacion(fechaFundacion);

    std::cout << "INGRESE CANTIDAD DE TROFEOS: ";
    std::cin >> cantidadTrofeos;
    set_cantidadtrofeos(cantidadTrofeos);

    std::cout << "INGRESE CANTIDAD DE DESCENSOS: ";
    std::cin >> cantidadDescensos;
    set_cantidaddescensos(cantidadDescensos);

    set_activo(true);
}

void Club::mostrar()
{
    std::cout << "ID CLUB: " << _IdClub << std::endl;
    std::cout << "NOMBRE: " << _Nombre << std::endl;
    std::cout << "PRESIDENTE: " << _Presidente << std::endl;

    std::cout << "FECHA DE FUNDACION: ";
    _FechaFundacion.mostrar();

    std::cout << "CANTIDAD DE TROFEOS: " << _CantidadTrofeos << std::endl;
    std::cout << "CANTIDAD DE DESCENSOS: " << _CantidadDescensos << std::endl;

    std::cout << "RACHA: ";
    for (int i = 0; i < 16; i++)
    {
        std::cout << _Racha[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "ACTIVO: ";
    if (_Activo == true)
    {
        std::cout << "SI" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }
}

bool Club::grabarEnDisco()
{
    FILE *pFile;
    bool result;

    pFile = fopen("clubes.dat", "ab");

    if (pFile == NULL)
    {
        return false;
    }

    result = fwrite(this, sizeof(Club), 1, pFile);

    fclose(pFile);

    return result;
}

bool Club::leerDeDisco(int posicion)
{
    FILE *pFile;
    bool result;

    pFile = fopen("clubes.dat", "rb");

    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * sizeof(Club), SEEK_SET);
    result = fread(this, sizeof(Club), 1, pFile);

    fclose(pFile);

    return result;
}

int Club::get_idclub()
{
    return _IdClub;
}

const char* Club::get_nombre()
{
    return _Nombre;
}

const char* Club::get_presidente()
{
    return _Presidente;
}

Fecha Club::get_fechafundacion()
{
    return _FechaFundacion;
}

int Club::get_cantidadtrofeos()
{
    return _CantidadTrofeos;
}

int Club::get_cantidaddescensos()
{
    return _CantidadDescensos;
}

int Club::get_racha(int jornada)
{
    if (jornada >= 0 && jornada < 16)
    {
        return _Racha[jornada];
    }

    return -1;
}

bool Club::get_activo()
{
    return _Activo;
}

void Club::set_idclub(int idClub)
{
    _IdClub = idClub;
}

void Club::set_nombre(const char nombre[])
{
    strcpy(_Nombre, nombre);
}

void Club::set_presidente(const char presidente[])
{
    strcpy(_Presidente, presidente);
}

void Club::set_fechafundacion(Fecha fechaFundacion)
{
    _FechaFundacion = fechaFundacion;
}

void Club::set_cantidadtrofeos(int cantidadTrofeos)
{
    _CantidadTrofeos = cantidadTrofeos;
}

void Club::set_cantidaddescensos(int cantidadDescensos)
{
    _CantidadDescensos = cantidadDescensos;
}

void Club::set_racha(int jornada, int resultado)
{
    if (jornada >= 0 && jornada < 16)
    {
        if (resultado >= 0 && resultado <= 3)
        {
            _Racha[jornada] = resultado;
        }
    }
}

void Club::set_activo(bool activo)
{
    _Activo = activo;
}
