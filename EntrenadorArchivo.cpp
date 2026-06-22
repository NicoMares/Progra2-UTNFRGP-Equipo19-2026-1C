#include "EntrenadorArchivo.h"
#include "Entrenador.h"
#include <iostream>
EntrenadorArchivo::EntrenadorArchivo()
{
}

Entrenador EntrenadorArchivo::leerDisco(int posicion) {
    Entrenador entrenador;
    FILE *pFile;

    pFile = fopen("entrenadores.dat", "rb");

    if (pFile == NULL) {
        return entrenador;
    }

    fseek(pFile, posicion * sizeof(Entrenador), SEEK_SET);
    fread(&entrenador, sizeof(Entrenador), 1, pFile);

    fclose(pFile);

    return entrenador;
}

bool EntrenadorArchivo::grabarEnDisco(Entrenador entrenador){

    FILE *pFile;
    bool result;

    pFile = fopen("entrenadores.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(&entrenador, sizeof(Entrenador), 1, pFile);

    fclose(pFile);

    return result;
}

bool EntrenadorArchivo::modificarEnDisco(Entrenador entrenador, int posicion) {
    FILE *pFile = fopen("entrenadores.dat", "rb+");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Entrenador), SEEK_SET);
    bool result = fwrite(&entrenador, sizeof(Entrenador), 1, pFile);

    fclose(pFile);
    return result;
}

int EntrenadorArchivo::contarRegistros() {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return 0;

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Entrenador);
}

int EntrenadorArchivo::buscarPorID(int idEntrenador) {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return -1;

    Entrenador entrenador;
    int pos = 0;
    while (fread(&entrenador, sizeof(Entrenador), 1, pFile) == 1) {
        if (entrenador.get_IdEntrenador() == idEntrenador) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

int EntrenadorArchivo::buscarPorIdClub(int idClub) {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return -1;

    Entrenador entrenador;
    int pos = 0;
    while (fread(&entrenador, sizeof(Entrenador), 1, pFile) == 1) {
        if (entrenador.get_IdClub() == idClub && entrenador.get_activo()) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

int EntrenadorArchivo::obtenerProximoID() {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return 1;

    Entrenador entrenador;
    int maximoID = 0;
    while (fread(&entrenador, sizeof(Entrenador), 1, pFile) == 1) {
        if (entrenador.get_IdEntrenador() > maximoID) {
            maximoID = entrenador.get_IdEntrenador();
        }
    }

    fclose(pFile);
    return maximoID + 1;
}

void EntrenadorArchivo::mostrarDTPorID() {
    int idBuscado;

    std::cout << "Ingrese el ID del entrenador a buscar: " << std::endl;
    std::cin >> idBuscado;

    EntrenadorArchivo archivo;
    int pos = archivo.buscarPorID(idBuscado);

    if (pos == -1) {
        std::cout << "No se encontró un entrenador con el ID: " << idBuscado << std::endl;
        return;
    }

    Entrenador entrenador = archivo.leerDisco(pos);
    if (!entrenador.get_activo()) {
        std::cout << "No se encontró un entrenador activo con el ID: " << idBuscado << std::endl;
        return;
    }
    entrenador.mostrar();
    std::cout << "-----------------------------" << std::endl;
}

void EntrenadorArchivo::listarActivos() {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return;

    Entrenador entrenador;
    while (fread(&entrenador, sizeof(Entrenador), 1, pFile) == 1) {
        if (entrenador.get_activo()) {
            entrenador.mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    fclose(pFile);
}

void EntrenadorArchivo::listar() {
    FILE *pFile = fopen("entrenadores.dat", "rb");
    if (pFile == NULL) return;

    Entrenador entrenador;
    while (fread(&entrenador, sizeof(Entrenador), 1, pFile) == 1) {
        entrenador.mostrar();
        std::cout << "--------------------------------" << std::endl;
    }

    fclose(pFile);
}

void EntrenadorArchivo::EliminarEntrenador() {

 int idBuscado;
            std::cout << "Ingrese el ID del entrenador que desea eliminar: ";
            std::cin >> idBuscado;

            EntrenadorArchivo archivo;
            Entrenador entrenador;
            int pos = archivo.buscarPorID(idBuscado);
            bool encontrado = false;

            if (pos != -1)
            {
                entrenador = archivo.leerDisco(pos);
                if (entrenador.get_IdEntrenador() == idBuscado && entrenador.get_activo() == true)
                {
                    encontrado = true;


                    entrenador.set_activo(false);


                    if (archivo.modificarEnDisco(entrenador, pos))
                    {
                        std::cout << "\nEl entrenador '" << entrenador.get_nombre() << "' fue eliminado con éxito." << std::endl;
                    }
                    else
                    {
                        std::cout << "\n Error al intentar guardar en el archivo." << std::endl;
                    }
                }
            }
            if (!encontrado) std::cout << "No se encontró ningún entrenador activo con el ID: " << idBuscado << std::endl;
}
