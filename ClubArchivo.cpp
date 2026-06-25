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
    clubTemp.mostrarRacha();

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

                    char confirmacion;
                    std::cout << "¿Estás seguro que querés eliminar el club '" << equipo.get_nombre() << "'? (S/N): ";
                    std::cin >> confirmacion;
                    if (confirmacion != 'S' && confirmacion != 's')
                    {
                        std::cout << "Operación cancelada." << std::endl;
                        return;
                    }

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

    for (int i = 0; i < cantidad; i++) {
        Club aux = leerDeDisco(i);
        if (aux.get_activo()) {
            aux.mostrar();
            aux.mostrarRacha();
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

    for (int i = 0; i < cantidad; i++) {
        Club aux = leerDeDisco(i);
        aux.mostrar();
        std::cout << "--------------------------------" << std::endl;
    }
}

void ClubArchivo::sumarTrofeo(int idClub)
{
    int pos = buscarPorID(idClub);
    if (pos == -1) return;

    Club equipo = leerDeDisco(pos);
    equipo.set_cantidadtrofeos(equipo.get_cantidadtrofeos() + 1);
    modificarEnDisco(equipo, pos);
}

void ClubArchivo::sumarDescenso(int idClub)
{
    int pos = buscarPorID(idClub);
    if (pos == -1) return;

    Club equipo = leerDeDisco(pos);
    equipo.set_cantidaddescensos(equipo.get_cantidaddescensos() + 1);
    modificarEnDisco(equipo, pos);
}

void ClubArchivo::ModificarClub()
{
    ClubArchivo archivo;
    int idClub;
    std::cout << "Ingrese el ID del club a modificar: ";
    std:: cin >> idClub;

    int pos = archivo.buscarPorID(idClub);
    if (pos == -1)
    {
         std::cout << "No existe un club con ese ID." <<  std::endl;
        return;
    }

    Club club = archivo.leerDeDisco(pos);
    if (!club.get_activo())
    {
         std::cout << "No se puede modificar un club inactivo." <<  std::endl;
        return;
    }

    char confirmacion;
    std::cout << "¿Estás seguro que querés modificar el club '" << club.get_nombre() << "'? (S/N): ";
    std::cin >> confirmacion;
    if (confirmacion != 'S' && confirmacion != 's') {
        std::cout << "Operación cancelada." << std::endl;
        return;
    }


    int opcion;

     std::cout << "1. Nombre" <<  std::endl;
     std::cout << "2. Presidente" << std::endl;
     std::cout << "3. Fecha de fundación" <<  std::endl;
     std::cout << "4. Cantidad de trofeos" <<  std::endl;
     std::cout << "5. Cantidad de descensos" <<  std::endl;
     std::cout << "Seleccioná el campo a modificar: ";
     std::cin >> opcion;

    if (opcion == 1)
    {
        char nombre[50];
        bool nombreValido = false;
        do {
            std::cout << "Ingrese el nuevo nombre: ";
            std::cin >> std::ws;
            std::cin.getline(nombre, 50);
            if (!soloLetrasYNumeros(nombre)) {
                std::cout << "ERROR: Solo se permiten letras y espacios." << std::endl;
            } else {
                nombreValido = true;
            }
        } while (!nombreValido);
        club.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        Persona presidente;
         std::cout << "Ingrese los datos del nuevo presidente: " <<   std::endl;
        presidente.cargar();
        club.set_presidente(presidente);
    }
    else if (opcion == 3)
    {
        Fecha fecha;
        std:: cout << "Ingrese la nueva fecha:" <<  std::endl;
        fecha.cargar();
        club.set_fechafundacion(fecha);
    }
    else if (opcion == 4)
    {
        int trofeos;
        std::cout << "Ingrese la nueva cantidad de trofeos: ";
        std::cin >> trofeos;
        if (trofeos < 0)
        {
            std::cout << "La cantidad de trofeos no puede ser negativa." << std::endl;
            return;
        }
        club.set_cantidadtrofeos(trofeos);
    }
    else if (opcion == 5)
    {
        int descensos;
        std::cout << "Ingrese la nueva cantidad de descensos: ";
        std::cin >> descensos;
        if (descensos < 0)
        {
            std::cout << "La cantidad de descensos no puede ser negativa." << std::endl;
            return;
        }
        club.set_cantidaddescensos(descensos);
    }
    else
    {
         std::cout << "Opción incorrecta." <<  std::endl;
        return;
    }

    if (archivo.modificarEnDisco(club, pos))
    {
         std::cout << "Club modificado correctamente." <<  std::endl;
    }
    else
    {
         std::cout << "No se pudo modificar el club." <<  std::endl;
    }
}