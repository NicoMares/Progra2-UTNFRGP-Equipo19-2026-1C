#include "ClubArchivo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
#include "utils.h"


ClubArchivo::ClubArchivo()
{

}

const char* ClubArchivo::getNombreArchivo() const
{
    return "clubes.dat";
}

bool ClubArchivo::grabarEnDisco(Club equipo) {
    return grabarRegistro(&equipo, sizeof(Club));
}

Club ClubArchivo::leerDeDisco(int posicion)
{
    Club equipo;
    leerRegistro(&equipo, sizeof(Club), posicion);
    return equipo;
}

int ClubArchivo::contarRegistros()
{
    return Archivo::contarRegistros(sizeof(Club));
}

int ClubArchivo::buscarPorID(int idClub)
{
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++)
    {
        Club equipo = leerDeDisco(i);
        if (equipo.get_idclub() == idClub) return i;
    }

    return -1;
}

int ClubArchivo::obtenerProximoID()
{
    int maximoID = 0;
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++)
    {
        Club equipo = leerDeDisco(i);
        if (equipo.get_idclub() > maximoID)
        {
            maximoID = equipo.get_idclub();
        }
    }

    return maximoID + 1;
}

void ClubArchivo :: mostrarPorID()
{
    int idBuscado;
    std::cout << "Ingrese el ID del club que desea consultar: ";
    std::cin >> idBuscado;

    ClubArchivo archivo;
    int pos = archivo.buscarPorID(idBuscado);

    if (pos == -1)
    {
        std::cout << "No se encontró un club con el ID: " << idBuscado << std::endl;
        return;
    }

    Club clubTemp = archivo.leerDeDisco(pos);
    if (!clubTemp.get_activo())
    {
        std::cout << "No se encontró un club activo con el ID: " << idBuscado << std::endl;
        return;
    }
    clubTemp.mostrar();
}

bool ClubArchivo::modificarEnDisco(Club equipo, int posicion)
{
    return modificarRegistro(&equipo, sizeof(Club), posicion);
}

void ClubArchivo::eliminarDeDisco()
{
            int idBuscado;
            std::cout << "Ingrese el ID del club que desea eliminar: ";
            std::cin >> idBuscado;

            Club equipo;
            ClubArchivo archivo;
            int pos = archivo.buscarPorID(idBuscado);
            bool encontrado = false;

            if (pos != -1)
            {
                equipo = archivo.leerDeDisco(pos);
                if (equipo.get_idclub() == idBuscado && equipo.get_activo() == true)
                {
                    encontrado = true;


                    equipo.set_activo(false);


                    if (archivo.modificarEnDisco(equipo, pos))
                    {
                        std::cout << "\n El club '" << equipo.get_nombre() << "' fue eliminado con éxito." << std::endl;
                    }
                    else
                    {
                        std::cout << "\n Error al intentar guardar en el archivo." << std::endl;
                    }
                }
            }
            if (!encontrado) std::cout << "No se encontró ningún club activo con el ID: " << idBuscado << std::endl;
        }

void ClubArchivo::listarActivos() {
    int cantidad = contarRegistros();
    if (cantidad == 0) {
        std::cout << "No hay clubes cargados en el sistema." << std::endl;
        return;
    }

    for (int pos = 0; pos < cantidad; pos++) {
        Club aux = leerDeDisco(pos);
        if (aux.get_activo()) {
            aux.mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }
}

void ClubArchivo::listar() {
    int cantidad = contarRegistros();
    if (cantidad == 0) {
        std::cout << "No hay clubes cargados en el sistema." << std::endl;
        return;
    }

    for (int pos = 0; pos < cantidad; pos++) {
        Club aux = leerDeDisco(pos);
        aux.mostrar();
        std::cout << "--------------------------------" << std::endl;
    }
}
