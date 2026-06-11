#include "EntrenadorArchivo.h"
#include "Entrenador.h"
#include "Club.h"
#include <iostream>

EntrenadorArchivo::EntrenadorArchivo()
{
}
bool EntrenadorArchivo::leerDisco(int posicion) {
    FILE *pFile;
    bool result;

    pFile = fopen("entrenadores.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Entrenador), SEEK_SET);
    result = fread(this, sizeof(Entrenador), 1, pFile);

    fclose(pFile);

    return result;
}

void EntrenadorArchivo::mostrarDTPorID() {
    int idBuscado;

    std::cout << "Ingrese el ID del entrenador a buscar: " << std::endl;
    std::cin >> idBuscado;

    Entrenador entrenador;
    EntrenadorArchivo archivo;

    int pos = 0;
    bool encontrado = false;

    while (archivo.leerDisco(pos)) {
        if (entrenador.get_IdEntrenador() == idBuscado) {
            entrenador.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
            break;
        }
        pos++;
    }

    if (!encontrado) {
        std::cout << "No se encontró un entrenador con el ID: " << idBuscado << std::endl;
    }
}

void EntrenadorArchivo::MostrarTodos() {

int pos = 0;

Entrenador entrenador;
EntrenadorArchivo archivo;

            while (archivo.leerDisco(pos))
            {
                entrenador.mostrar();
              
                pos++;
            }


}
    


void EntrenadorArchivo::EliminarEntrenador() {

 int idBuscado;
            std::cout << "Ingrese el ID del club que desea eliminar: ";
            std::cin >> idBuscado;

            Club equipo;
            int pos = 0;
            bool encontrado = false;

            while (equipo.leerDeDisco(pos))
            {
                if (equipo.get_idclub() == idBuscado && equipo.get_activo() == true)
                {
                    encontrado = true;


                    equipo.set_activo(false);


                    if (equipo.modificarEnDisco(pos))
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


}