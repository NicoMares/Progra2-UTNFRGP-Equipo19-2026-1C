#include "JugadorArchivo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"

JugadorArchivo::JugadorArchivo()
{
 
}

bool JugadorArchivo::grabarEnDisco(Jugador jugador) {
    FILE *pFile;
    bool result;

    pFile = fopen("jugadores.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(&jugador, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return result;
}

Jugador JugadorArchivo::leerDeDisco(int posicion) {
    Jugador jugador;
    FILE *pFile;

    pFile = fopen("jugadores.dat", "rb");

    if (pFile == NULL) {
        return jugador;
    }

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    fread(&jugador, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return jugador;
}

int JugadorArchivo::contarRegistros() {
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return 0;

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Jugador);
}

int JugadorArchivo::buscarPorID(int idJugador) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Jugador jugador = leerDeDisco(i);
        if (jugador.get_idjugador() == idJugador) return i;
    }

    return -1;
}

int JugadorArchivo::buscarPorDNI(int dni) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Jugador jugador = leerDeDisco(i);
        if (jugador.get_dni() == dni) return i;
    }

    return -1;
}

int JugadorArchivo::obtenerProximoID() {
    int maximoID = 0;
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Jugador jugador = leerDeDisco(i);
        if (jugador.get_idjugador() > maximoID) {
            maximoID = jugador.get_idjugador();
        }
    }

    return maximoID + 1;
}

void JugadorArchivo::ConsultarPorDNI() {
    int dniBuscado;
    std::cout << "Ingrese el DNI del jugador que desea consultar: ";
    std::cin >> dniBuscado;

    JugadorArchivo ArchivoTemp;
    int pos = ArchivoTemp.buscarPorDNI(dniBuscado);

    if (pos == -1) {
        std::cout << "No se encontró un jugador con el DNI: " << dniBuscado << std::endl;
        return;
    }

    Jugador JugadorTemp = ArchivoTemp.leerDeDisco(pos);
    if (!JugadorTemp.get_activo()) {
        std::cout << "No se encontró un jugador activo con el DNI: " << dniBuscado << std::endl;
        return;
    }
    JugadorTemp.mostrar();
}

void JugadorArchivo ::consultarPorPosicion() {
    char posicionBuscada[50];
    std::cout << "Ingrese la posición del jugador que desea consultar: ";
    std::cin >> posicionBuscada;

   JugadorArchivo ArchivoTemp;
   Jugador JugadorTemp;


    int pos = 0;
    bool encontrado = false;

    while (pos < ArchivoTemp.contarRegistros()) {
        JugadorTemp = ArchivoTemp.leerDeDisco(pos);
        if (JugadorTemp.get_activo() && strcmp(JugadorTemp.get_posicion(), posicionBuscada) == 0) {
            JugadorTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }
        pos++;
    }

    if (!encontrado) {
        std::cout << "No se encontraron jugadores activos con la posición: " << posicionBuscada << std::endl;
    }
}

void JugadorArchivo::ListarDni() {
    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;
  
    int pos = 0;


    while (pos < ArchivoTemp.contarRegistros())
    {
        JugadorTemp = ArchivoTemp.leerDeDisco(pos);
        if (JugadorTemp.get_activo()) {
            JugadorTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
        }
        pos++;
    }
}

void JugadorArchivo::TodosJugadores() {
    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;

    int pos = 0;

    while (pos < ArchivoTemp.contarRegistros()) {
        JugadorTemp = ArchivoTemp.leerDeDisco(pos);
        if (JugadorTemp.get_activo()) {
            JugadorTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
        }
        pos++;
    }
}

void JugadorArchivo::listarPorClub() {
    int idClubBuscado;
    std::cout << "Ingrese el ID del club para listar sus jugadores: "<<std::endl;
    std::cin >> idClubBuscado;

    std::cout<<  "------------------------------" << std::endl;

    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;

    int pos = 0;
    bool encontrado = false;

    while (pos < ArchivoTemp.contarRegistros()) {
        JugadorTemp = ArchivoTemp.leerDeDisco(pos);
        if (JugadorTemp.get_activo() && JugadorTemp.get_idclub() == idClubBuscado) {
            JugadorTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }
        pos++;
    }

    if (!encontrado) {
        std::cout << "No se encontraron jugadores para el club con ID: " << idClubBuscado << std::endl;
    }
}

bool JugadorArchivo::modificarEnDisco(Jugador jugador, int posicion)
{
    FILE *pFile = fopen("jugadores.dat", "rb+"); 
    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET); 
    bool seEscribio = fwrite(&jugador, sizeof(Jugador), 1, pFile);
    fclose(pFile); 
    return seEscribio; 
}

void JugadorArchivo::EliminarJugador() {
    int idBuscado;
    std::cout << "Ingrese el ID del jugador a eliminar: ";
    std::cin >> idBuscado;

    JugadorArchivo ArchivoTemp;
    int pos = ArchivoTemp.buscarPorID(idBuscado);

    if (pos == -1) {
        std::cout << "No se encontró ningún jugador con el ID ingresado." << std::endl;
        return;
    }

    Jugador JugadorTemp = ArchivoTemp.leerDeDisco(pos);

    if (JugadorTemp.get_activo() == false) {
        std::cout << "El jugador ya se encuentra inactivo." << std::endl;
        return;
    }

    JugadorTemp.set_activo(false);

    if (ArchivoTemp.modificarEnDisco(JugadorTemp, pos)) {
        std::cout << "\nEl jugador fue eliminado con éxito del sistema." << std::endl;
    } else {
        std::cout << "\nError al intentar guardar en el archivo." << std::endl;
    }
}
