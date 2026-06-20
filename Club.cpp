#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
#include "ClubArchivo.h"
#include "utils.h"

Club::Club()
{
    _IdClub = 0;
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
    ClubArchivo archivo;
    set_idclub(archivo.obtenerProximoID());
    std::cout << "ID CLUB ASIGNADO: " << _IdClub << std::endl;

    std::cin.ignore();

    std::cout << "INGRESE NOMBRE DEL CLUB: ";
    std::cin.getline(_Nombre, 50);

    std::cout << "INGRESE NOMBRE DEL PRESIDENTE: ";
    std::cin.getline(_Presidente, 50);

    std::cout << "INGRESE FECHA DE FUNDACIÓN: "<<std::endl;

    Fecha f;
    f.cargar();
    set_fechafundacion(f);


    std::cout << "INGRESE CANTIDAD DE TROFEOS: ";
    std::cin >> _CantidadTrofeos;

    std::cout << "INGRESE CANTIDAD DE DESCENSOS: ";
    std::cin >> _CantidadDescensos;

    _Activo = true;
}

void Club::mostrar()
{

    std::cout<<std::endl;
    std::cout << "ID CLUB: " << _IdClub << std::endl;
    std::cout << "NOMBRE: " << _Nombre << std::endl;
    std::cout << "PRESIDENTE: " << _Presidente << std::endl;

    std::cout << "FECHA DE FUNDACIÓN: ";
    _FechaFundacion.mostrar();

    std::cout << "CANTIDAD DE TROFEOS: " << _CantidadTrofeos << std::endl;
    std::cout << "CANTIDAD DE DESCENSOS: " << _CantidadDescensos << std::endl;

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

void Club::mostrarRacha()
{
    std::cout << "RACHA (ÚLTIMOS 5 PARTIDOS): ";

    int encontrados = 0;
    int resultadosEncontrados[5] = {0, 0, 0, 0, 0};

    for (int j = 15; j >= 1; j--)
    {
        int res = get_racha(j);
        if (res == 1 || res == 2 || res == 3)
        {
            resultadosEncontrados[encontrados] = res;
            encontrados++;
        }
        if (encontrados == 5) break;
    }

    for (int i = 0; i < 5; i++)
    {
        if (i < encontrados)
        {
            switch (resultadosEncontrados[i])
            {
                case 1: std::cout << "[V] "; break;
                case 2: std::cout << "[E] "; break;
                case 3: std::cout << "[D] "; break;
            }
        }
        else
        {
            // Si ya no hay más partidos encontrados, llenamos con guiones
            std::cout << "[-] ";
        }
    }
    std::cout << std::endl;
}

int Club::calcularPuntos(){
    int puntos = 0;

    for (int j = 1; j <= 15; j++) {
        int resultado = _Racha[j];
        if (resultado == 1)      puntos += 3; // Victoria
        else if (resultado == 2) puntos += 1; // Empate
    }

    return puntos;
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
