#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
#include "ClubArchivo.h"
#include "utils.h"
#include "Entrenador.h"
#include "EntrenadorArchivo.h"

Club::Club()
{
    _IdClub = 0;
    strcpy(_Nombre, "");
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

    std::cout << "Datos Del Club: " << std::endl;
    std::cout << "--------------------------------" << std::endl;

    bool nombreValido = false;
    do {
        std::cout << "INGRESE NOMBRE DEL CLUB: ";
        std::cin.getline(_Nombre, 50);
        if (!soloLetrasYNumeros(_Nombre)) {
            std::cout << "ERROR: Solo se permiten letras y espacios." << std::endl;
        } else {
            nombreValido = true;
        }
    } while (!nombreValido);

    std::cout << "INGRESE FECHA DE FUNDACIÓN: " << std::endl;
    Fecha f;
    f.cargar();
    set_fechafundacion(f);

    // VALIDACIÓN TROFEOS
    int auxTrofeos;
    do {
        std::cout << "INGRESE CANTIDAD DE TROFEOS: ";
        std::cin >> auxTrofeos;
        if (auxTrofeos < 0) {
            std::cout << "ERROR: La cantidad de trofeos no puede ser negativa." << std::endl;
        }
    } while (auxTrofeos < 0);
    set_cantidadtrofeos(auxTrofeos);

    //VALIDACIÓN DESCENSOS
    int auxDescensos;
    do {
        std::cout << "INGRESE CANTIDAD DE DESCENSOS: ";
        std::cin >> auxDescensos;
        if (auxDescensos < 0) {
            std::cout << "ERROR: La cantidad de descensos no puede ser negativa." << std::endl;
        }
    } while (auxDescensos < 0);
    set_cantidaddescensos(auxDescensos);

    _Activo = true;

    std::cout << std::endl;
    std::cin.ignore();

    std::cout << "DATOS DEL PRESIDENTE: " << std::endl;
    std::cout << "--------------------------------" << std::endl;
    _Presidente.cargar();

    std::cout << std::endl;
}

void Club::mostrar()
{
    std::cout << std::endl;
    std::cout << "ID CLUB: " << _IdClub << std::endl;
    std::cout << "NOMBRE: " << _Nombre << std::endl;

    std::cout << "PRESIDENTE: " << _Presidente.get_nombre() << " " << _Presidente.get_apellido() << std::endl;

    std::cout << "FECHA DE FUNDACIÓN: ";
    _FechaFundacion.mostrar();

    EntrenadorArchivo entArch;
    int posDT = entArch.buscarPorIdClub(_IdClub);
    if (posDT != -1) {
        Entrenador dt = entArch.leerDisco(posDT);
        std::cout << "TECNICO: " << dt.get_nombre() << " " << dt.get_apellido() << std::endl;
    } else {
        std::cout << "TECNICO: Sin asignar" << std::endl;
    }

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
            std::cout << "[-] ";
        }
    }
    std::cout << std::endl;
}

int Club::calcularPuntos()
{
    int puntos = 0;

    for (int j = 1; j <= 15; j++)
    {
        int resultado = _Racha[j];
        if (resultado == 1)      puntos += 3;
        else if (resultado == 2) puntos += 1;
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

Persona Club::get_presidente()
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

void Club::set_presidente(Persona presidente)
{
    _Presidente = presidente;
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
