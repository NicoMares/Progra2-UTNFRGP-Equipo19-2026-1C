#include "utils.h"
#include "JugadorArchivo.h"
#include "EntrenadorArchivo.h"
#include "ClubArchivo.h"
#include <iostream>

bool soloLetras(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

bool soloLetrasYNumeros(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ')) {
            return false;
        }
    }
    return true;
}

void cargarCadena(char *palabra, int tamano){
    int i=0;

    for(i=0; i<tamano; i++){
        palabra[i]=std::cin.get();
        if(palabra[i]=='\n'){
            break;
        }
    }

    palabra[i]='\0';
}

bool buscarDNIEnSistema(int dni, std::string& nombre, std::string& apellido, std::string& tipo) {
    bool encontrado = false;

    JugadorArchivo archivoJugadores;
    int posJ = archivoJugadores.buscarPorDNI(dni);
    if (posJ != -1) {
        Jugador j = archivoJugadores.leerDeDisco(posJ);
        encontrado = true;
        nombre   = j.get_nombre();
        apellido = j.get_apellido();
        tipo     = "Jugador";
    }

    EntrenadorArchivo archivoEntrenadores;
    int posE = archivoEntrenadores.buscarDNI(dni);
    if (posE != -1) {
        Entrenador e = archivoEntrenadores.leerDisco(posE);
        if (!encontrado) {
            encontrado = true;
            nombre   = e.get_nombre();
            apellido = e.get_apellido();
            tipo     = "Entrenador (DT)";
        } else {
            tipo += ", Entrenador (DT)";
        }
    }

    ClubArchivo archivoClubes;
    int cantClubes = archivoClubes.contarRegistros();
    for (int i = 0; i < cantClubes; i++) {
        Club club = archivoClubes.leerDeDisco(i);
        if (club.get_presidente().get_dni() == dni) {
            if (!encontrado) {
                encontrado = true;
                nombre   = club.get_presidente().get_nombre();
                apellido = club.get_presidente().get_apellido();
                tipo     = "Presidente";
            } else {
                tipo += ", Presidente";
            }
            break;
        }
    }

    return encontrado;
}
