#include "EntrenadorArchivo.h"
#include "Entrenador.h"
#include <iostream>
EntrenadorArchivo::EntrenadorArchivo()
{
}

const char* EntrenadorArchivo::getNombreArchivo() const
{
    return "entrenadores.dat";
}

Entrenador EntrenadorArchivo::leerDisco(int posicion) {
    Entrenador entrenador;
    leerRegistro(&entrenador, sizeof(Entrenador), posicion);
    return entrenador;
}

bool EntrenadorArchivo::grabarEnDisco(Entrenador entrenador){
    return grabarRegistro(&entrenador, sizeof(Entrenador));
}

bool EntrenadorArchivo::modificarEnDisco(Entrenador entrenador, int posicion) {
    return modificarRegistro(&entrenador, sizeof(Entrenador), posicion);
}

int EntrenadorArchivo::contarRegistros() {
    return Archivo::contarRegistros(sizeof(Entrenador));
}

int EntrenadorArchivo::buscarPorID(int idEntrenador) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Entrenador entrenador = leerDisco(i);
        if (entrenador.get_IdEntrenador() == idEntrenador) return i;
    }

    return -1;
}

int EntrenadorArchivo::obtenerProximoID() {
    int maximoID = 0;
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Entrenador entrenador = leerDisco(i);
        if (entrenador.get_IdEntrenador() > maximoID) {
            maximoID = entrenador.get_IdEntrenador();
        }
    }

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

int pos = 0;

Entrenador entrenador;
EntrenadorArchivo archivo;

            while (pos < archivo.contarRegistros())
            {
                entrenador = archivo.leerDisco(pos);
                if (entrenador.get_activo()) {
                    entrenador.mostrar();
                    std::cout << "--------------------------------" << std::endl;
                }
                pos++;
            }


}

void EntrenadorArchivo::listar() {
    int pos = 0;

    Entrenador entrenador;
    EntrenadorArchivo archivo;

    while (pos < archivo.contarRegistros())
    {
        entrenador = archivo.leerDisco(pos);
        entrenador.mostrar();
        std::cout << "--------------------------------" << std::endl;
        pos++;
    }
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
