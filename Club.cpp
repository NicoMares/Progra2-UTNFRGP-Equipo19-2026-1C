#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
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
    char nombre[50];
    char presidente[50];
    Fecha fechaFundacion;
    int cantidadTrofeos;
    int cantidadDescensos;

    int siguienteId = 1;
    FILE *pFile = fopen("clubes.dat", "rb");

    if (pFile != NULL)
    {
        Club Tempclub;

        while (fread(&Tempclub, sizeof(Club), 1, pFile) == 1)
        {
            if (Tempclub.get_idclub() >= siguienteId)
            {
                siguienteId = Tempclub.get_idclub() + 1;
            }
        }

        fclose(pFile);
    }

    set_idclub(siguienteId);
    std::cout << "ID CLUB ASIGNADO Al Club: " << _IdClub << std::endl;

    std::cout << "INGRESE NOMBRE DEL CLUB: ";
    
    cargarCadena(nombre, 49);
   

    std::cout << "INGRESE NOMBRE DEL PRESIDENTE "; 
 

    cargarCadena(presidente, 49);
 

    do ///VALIDACI�N PARA FECHA DE FUNDACI�N -Leandro
    {
        std::cout << "INGRESE FECHA DE FUNDACIóN: " << std::endl;
        fechaFundacion.cargar();

        if (fechaFundacion.get_Anio() < 1800 || fechaFundacion.get_Anio() > 2026)
        {
            std::cout << "\n ERROR: El anio de fundacion debe estar entre 1800 y 2026." << std::endl;
            std::cout << "Por favor, ingrese la fecha nuevamente.\n" << std::endl;
        }

    } while (fechaFundacion.get_Anio() < 1800 || fechaFundacion.get_Anio() > 2026);

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

    std::cout << "RACHA (ULTIMOS 5 PARTIDOS): ";

    int contadorMostrados = 0;

    /// Recorremos el vector al revez as� podemos utilizar las ultimas jornadas - Leandro
    for (int i = 15; i >= 0; i--)
    {
        int resultado = get_racha(i);

        if (resultado == 0 || resultado == 1 || resultado == 2 || resultado == 3)
        {
            switch (resultado)
            {
                case 0:
                    std::cout << "[-] "; /// Jornada no jugada o sin resultado registrado
                    break;
                case 1:
                    std::cout << "[V] "; /// Victoria
                    break;
                case 2:
                    std::cout << "[E] "; /// Empate
                    break;
                case 3:
                    std::cout << "[D] "; /// Derrota
                    break;
            }
            contadorMostrados++;
        }

        /// Contador en 5, nos permite ver sus ultimos partidos, recordar que vamos del elemento 15 al 0
        /// Cortandolo en 5, nos permite ver los ultimos 5 partidos - leandro
        if (contadorMostrados == 5) {
            break;
        }
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
