#include "ValidadorDNI.h"
#include "JugadorArchivo.h"
#include "EntrenadorArchivo.h"
#include "ClubArchivo.h"

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
