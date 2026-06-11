#include "ClubArchivo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Club.h"
#include "utils.h"


ClubArchivo::ClubArchivo()
{

}

bool ClubArchivo::grabarEnDisco()
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

void ClubArchivo::mostrarClubes()
        {
        int pos = 0;

            Club equipo;
            ClubArchivo archivo;

            while (archivo.leerDeDisco(pos))
            {
                if (equipo.get_activo() == true)
                {
                    equipo.mostrar();
                   
                }
                pos++;
            }
            system("pause");
            


        }   

void ClubArchivo::mostrarCout(){

    ClubArchivo archivo;
 if (archivo.grabarEnDisco())
            {
                std::cout << "Accion guardada correctamente." << std::endl;
            }
            else
            {
               std::cout << "No se pudo guardar la accion." << std::endl;
            }


}