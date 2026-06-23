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

int EntrenadorArchivo::buscarDNI(int dni) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Entrenador entrenador = leerDisco(i);
        if (entrenador.get_dni() == dni) return i;
    }

    return -1;
}

int EntrenadorArchivo::buscarPorID(int idEntrenador) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Entrenador entrenador = leerDisco(i);
        if (entrenador.get_IdEntrenador() == idEntrenador) return i;
    }

    return -1;
}

int EntrenadorArchivo::buscarPorIdClub(int idClub) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Entrenador entrenador = leerDisco(i);
        if (entrenador.get_IdClub() == idClub && entrenador.get_activo()) return i;
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

                    char confirmacion;
                    std::cout << "¿Estás seguro que querés eliminar al entrenador '" << entrenador.get_nombre() << " " << entrenador.get_apellido() << "'? (S/N): ";
                    std::cin >> confirmacion;
                    if (confirmacion != 'S' && confirmacion != 's')
                    {
                        std::cout << "Operación cancelada." << std::endl;
                        return;
                    }

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

void EntrenadorArchivo::modificarEntrenador()
{
    EntrenadorArchivo archivo;
    int idEntrenador;
    std:: cout << "Ingrese el ID del entrenador a modificar: ";
    std:: cin >> idEntrenador;

    int pos = archivo.buscarPorID(idEntrenador);
    if (pos == -1)
    {
         std::cout << "No existe un entrenador con ese ID." <<  std::endl;
        return;
    }

    Entrenador entrenador = archivo.leerDisco(pos);
    if (!entrenador.get_activo())
    {
         std::cout << "No se puede modificar un entrenador inactivo." << std:: endl;
        return;
    }

    char confirmacion;
    std::cout << "¿Estás seguro que querés modificar al entrenador '" << entrenador.get_nombre() << " " << entrenador.get_apellido() << "'? (S/N): ";
    std::cin >> confirmacion;
    if (confirmacion != 'S' && confirmacion != 's') {
        std::cout << "Operación cancelada." << std::endl;
        return;
    }

    int opcion;

     std::cout << "1. Nombre" << std:: endl;
    std:: cout << "2. Apellido" <<  std::endl;
    std:: cout << "3. DNI" <<  std::endl;
    std:: cout << "4. Fecha de nacimiento" <<  std::endl;
     std::cout << "5. Club" <<  std::endl;
     std::cout << "Seleccioná el campo a modificar: ";
     std::cin >> opcion;

    if (opcion == 1)
    {
        char nombre[30];
       std::  cout << "Ingrese el nuevo nombre: ";
        std:: cin >>  std::ws;
         std::cin.getline(nombre, 30);
        entrenador.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        char apellido[30];
        std:: cout << "Ingrese el nuevo apellido: ";
        std:: cin >>  std::ws;
        std:: cin.getline(apellido, 30);
        entrenador.set_apellido(apellido);
    }
    else if (opcion == 3)
    {
        int dni;
        std:: cout << "Ingrese el nuevo DNI: ";
        std:: cin >> dni;
        entrenador.set_dni(dni);
    }
    else if (opcion == 4)
    {
        Fecha fecha;
        std:: cout << "Ingrese la nueva fecha:" << std:: endl;
        fecha.cargar();
        entrenador.set_fechanacimiento(fecha);
    }
    else if (opcion == 5)
    {
        int idClub;
         std::cout << "Ingrese el nuevo ID de club: ";
        std:: cin >> idClub;
        entrenador.set_idclub(idClub);
    }
    else
    {
         std::cout << "Opción incorrecta." << std:: endl;
        return;
    }

    if (archivo.modificarEnDisco(entrenador, pos))
    {
         std::cout << "Entrenador modificado correctamente." << std:: endl;
    }
    else
    {
        std:: cout << "No se pudo modificar el entrenador." <<  std::endl;
    }
}
