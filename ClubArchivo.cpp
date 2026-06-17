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

bool ClubArchivo::leerDeDisco(int posicion)
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

void ClubArchivo :: mostrarPorID()
{
std::cout << "ENTRE AL MOSTRAR POR ID" << std::endl;

    int idBuscado;
    std::cout << "Ingrese el ID del club que desea consultar: ";
    std::cin >> idBuscado;

    Club clubTemp;
    ClubArchivo archivo;

    int pos = 0;
    bool encontrado = false;

    while (archivo.leerDeDisco(pos))
    {
        if (clubTemp.get_idclub() == idBuscado)
        {
            clubTemp.mostrar();
            encontrado = true;
            break;
        }
        pos++;
    }

    if (!encontrado)
    {
        std::cout << "No se encontro un club con el ID: " << idBuscado << std::endl;
    }
}

bool ClubArchivo::modificarEnDisco(int posicion)
{

    FILE *pFile = fopen("clubes.dat", "rb+");


    if (pFile == NULL)
    {
        return false;
    }


    fseek(pFile, posicion * sizeof(Club), SEEK_SET);


    bool seEscribio = fwrite(this, sizeof(Club), 1, pFile);


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
            int pos = 0;
            bool encontrado = false;

            while (archivo.leerDeDisco(pos))
            {
                if (equipo.get_idclub() == idBuscado && equipo.get_activo() == true)
                {
                    encontrado = true;


                    equipo.set_activo(false);


                    if (archivo.modificarEnDisco(pos))
                    {
                        std::cout << "\n El club '" << equipo.get_nombre() << "' fue eliminado con éxito." << std::endl;
                    }
                    else
                    {
                        std::cout << "\n Error al intentar guardar en el archivo." << std::endl;
                    }
                    break;
                }
                pos++;
            }
            if (!encontrado) std::cout << "No se encontró ningún club activo con el ID: " << idBuscado << std::endl;
            system("pause");
        }

void ClubArchivo::mostrarClubes() {
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
