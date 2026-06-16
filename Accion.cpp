#include <iostream>
#include <cstring>
#include "Accion.h"

Accion::Accion()
{
    _IdAccion = 0;
    _IdPartido = 0;
    _DniJugador = 0;
    _IdClub = 0;
    _Minuto = 0;
    strcpy(_TipoAccion, "");
    _Puntaje = 0;
    _Positiva = true;
    _Activo = true;
}

void Accion::cargar()
{
    int idPartido;
    int dniJugador;
    int minuto;
    int opcionAccion;
    bool accionValida = false;

    std::cout << "INGRESE ID DEL PARTIDO: ";
    std::cin >> idPartido;
    set_idpartido(idPartido);

    std::cout << "INGRESE DNI DEL JUGADOR: ";
    std::cin >> dniJugador;
    set_dnijugador(dniJugador);

    std::cout << "INGRESE MINUTO DE LA ACCION: ";
    std::cin >> minuto;
    set_minuto(minuto);

    do
    {
        std::cout << "SELECCIONE TIPO DE ACCION" << std::endl;
        std::cout << "1 - Gol" << std::endl;
        std::cout << "2 - Asistencia" << std::endl;
        std::cout << "3 - Amarilla" << std::endl;
        std::cout << "4 - Roja" << std::endl;
        std::cout << "5 - Falta" << std::endl;
        std::cout << "6 - Atajada" << std::endl;
        std::cout << "7 - Lesion" << std::endl;
        std::cout << "OPCION: ";
        std::cin >> opcionAccion;

        switch (opcionAccion)
        {
            case 1:
                set_idaccion(1);
                set_tipoaccion("Gol");
                accionValida = true;
                break;

            case 2:
                set_idaccion(2);
                set_tipoaccion("Asistencia");
                accionValida = true;
                break;

            case 3:
                set_idaccion(3);
                set_tipoaccion("Amarilla");
                accionValida = true;
                break;

            case 4:
                set_idaccion(4);
                set_tipoaccion("Roja");
                accionValida = true;
                break;

            case 5:
                set_idaccion(5);
                set_tipoaccion("Falta");
                accionValida = true;
                break;

            case 6:
                set_idaccion(6);
                set_tipoaccion("Atajada");
                accionValida = true;
                break;

            case 7:
                set_idaccion(7);
                set_tipoaccion("Lesion");
                accionValida = true;
                break;

            default:
                std::cout << "OPCION INVALIDA. INGRESE UNA ACCION VALIDA." << std::endl;
                accionValida = false;
                break;
        }

    } while (accionValida == false);

    set_idclub(0);
    set_puntaje(0);
    set_activo(true);
}

void Accion::mostrar()
{
    std::cout << "ID TIPO ACCION: " << _IdAccion << std::endl;
    std::cout << "TIPO DE ACCION: " << _TipoAccion << std::endl;
    std::cout << "ID PARTIDO: " << _IdPartido << std::endl;
    std::cout << "DNI JUGADOR: " << _DniJugador << std::endl;
    std::cout << "ID CLUB: " << _IdClub << std::endl;
    std::cout << "MINUTO: " << _Minuto << std::endl;
    std::cout << "PUNTAJE: " << _Puntaje << std::endl;

    std::cout << "POSITIVA: ";
    if (_Positiva == true)
    {
        std::cout << "SI" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }

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

int Accion::get_idaccion()
{
    return _IdAccion;
}

int Accion::get_idpartido()
{
    return _IdPartido;
}

int Accion::get_dnijugador()
{
    return _DniJugador;
}

int Accion::get_idclub()
{
    return _IdClub;
}

int Accion::get_minuto()
{
    return _Minuto;
}

const char* Accion::get_tipoaccion()
{
    return _TipoAccion;
}

int Accion::get_puntaje()
{
    return _Puntaje;
}

bool Accion::get_positiva()
{
    return _Positiva;
}

bool Accion::get_activo()
{
    return _Activo;
}

void Accion::set_idaccion(int idAccion)
{
    _IdAccion = idAccion;
}

void Accion::set_idpartido(int idPartido)
{
    _IdPartido = idPartido;
}

void Accion::set_dnijugador(int dniJugador)
{
    _DniJugador = dniJugador;
}

void Accion::set_idclub(int idClub)
{
    _IdClub = idClub;
}

void Accion::set_minuto(int minuto)
{
    _Minuto = minuto;
}

void Accion::set_tipoaccion(const char tipoAccion[])
{
    strcpy(_TipoAccion, tipoAccion);
}

void Accion::set_puntaje(int puntaje)
{
    _Puntaje = puntaje;

    if (_Puntaje >= 0)
    {
        _Positiva = true;
    }
    else
    {
        _Positiva = false;
    }
}

void Accion::set_positiva(bool positiva)
{
    _Positiva = positiva;
}

void Accion::set_activo(bool activo)
{
    _Activo = activo;
}
