#include "ClubArchivo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
#include "utils.h"


ClubArchivo::ClubArchivo()
{

}

bool ClubArchivo::grabarEnDisco(Club equipo) {
    FILE *p = fopen("clubes.dat", "ab"); // "ab" abre para agregar al final
    if (p == NULL) return false;


    bool guardo = fwrite(&equipo, sizeof(Club), 1, p);
    fclose(p);
    return guardo;
}

Club ClubArchivo::leerDeDisco(int posicion)
{
    Club equipo;
    FILE *pFile;

    pFile = fopen("clubes.dat", "rb");

    if (pFile == NULL)
    {
        return equipo;
    }

    fseek(pFile, posicion * sizeof(Club), SEEK_SET);
    fread(&equipo, sizeof(Club), 1, pFile);

    fclose(pFile);

    return equipo;
}

int ClubArchivo::contarRegistros()
{
    FILE *pFile = fopen("clubes.dat", "rb");
    if (pFile == NULL) return 0;

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Club);
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

    FILE *pFile = fopen("clubes.dat", "rb+");


    if (pFile == NULL)
    {
        return false;
    }


    fseek(pFile, posicion * sizeof(Club), SEEK_SET);


    bool seEscribio = fwrite(&equipo, sizeof(Club), 1, pFile);


    fclose(pFile);


    return seEscribio;
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
    Club aux;
    // Abrimos en modo lectura binaria ("rb")
    FILE *p = fopen("clubes.dat", "rb");

    if (p == NULL) {
        std::cout << "No hay clubes cargados en el sistema." << std::endl;
        return;
    }

    // Leemos registro por registro
    // Mientras fread devuelva 1, significa que leyó un objeto correctamente
    while (fread(&aux, sizeof(Club), 1, p) == 1) {
        if (aux.get_activo()) {
            aux.mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    fclose(p);
}

void ClubArchivo::listar() {
    Club aux;
    FILE *p = fopen("clubes.dat", "rb");

    if (p == NULL) {
        std::cout << "No hay clubes cargados en el sistema." << std::endl;
        return;
    }

    while (fread(&aux, sizeof(Club), 1, p) == 1) {
        aux.mostrar();
        std::cout << "--------------------------------" << std::endl;
    }

    fclose(p);
}

void ClubArchivo::mostrarCout(){

    ClubArchivo archivo;
    Club aux;
 if (archivo.grabarEnDisco(aux))
            {
                std::cout << "Accion guardada correctamente." << std::endl;
            }
            else
            {
               std::cout << "No se pudo guardar la accion." << std::endl;
            }


}
