#include "PartidoArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include <iostream>
#include <vector>
#include <algorithm> // Para std::swap

// 1. EL GRABAR (Tiene que llevar PartidoArchivo::)
bool PartidoArchivo::grabarEnDisco(Partido partido) {
    FILE *pFile = fopen("partidos.dat", "ab");
    if (pFile == NULL) return false;

    bool result = fwrite(&partido, sizeof(Partido), 1, pFile);
    fclose(pFile);
    return result;
}

// 2. EL LEER (Tiene que llevar PartidoArchivo::)
Partido PartidoArchivo::leerDeDisco(int posicion) {
    Partido partido;
    FILE *pFile = fopen("partidos.dat", "rb");
    if (pFile == NULL) return partido;

    fseek(pFile, posicion * sizeof(Partido), SEEK_SET);
    fread(&partido, sizeof(Partido), 1, pFile);
    fclose(pFile);
    return partido;
}

bool PartidoArchivo::modificarEnDisco(Partido partido, int posicion) {
    FILE *pFile = fopen("partidos.dat", "rb+");
    if (pFile == NULL) return false;

    fseek(pFile, posicion * sizeof(Partido), SEEK_SET);
    bool result = fwrite(&partido, sizeof(Partido), 1, pFile);
    fclose(pFile);
    return result;
}

int PartidoArchivo::contarRegistros() {
    FILE *pFile = fopen("partidos.dat", "rb");
    if (pFile == NULL) return 0;

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);
    return bytes / sizeof(Partido);
}

// 3. EL LISTAR POR JORNADA (Tiene que llevar PartidoArchivo::)
void PartidoArchivo::listarPorJornada(int jornadaBuscada) {
    Partido partidoTemp;
    int pos = 0;
    int cont = 0;

    std::cout << "\n=========================================" << std::endl;
    std::cout << "         PARTIDOS DE LA JORNADA " << jornadaBuscada << std::endl;
    std::cout << "=========================================" << std::endl;

    while (pos < contarRegistros()) {
        partidoTemp = leerDeDisco(pos);
        if (partidoTemp.get_jornada() == jornadaBuscada && partidoTemp.get_activo()) {
            partidoTemp.mostrar();
            cont++;
        }
        pos++;
    }

    if (cont == 0) {
        std::cout << "No hay partidos generados para esta jornada." << std::endl;
    }
    std::cout << "=========================================" << std::endl;
}

// 5. TU GENERADOR DE FIXTURE (Tiene que llevar PartidoArchivo::)
void PartidoArchivo::generarFixtureTorneo() {
    Club clubTemp;
    ClubArchivo archivoClubes;
    std::vector<int> vIdsClubes;

    for (int pos = 0; pos < archivoClubes.contarRegistros(); pos++) {
        clubTemp = archivoClubes.leerDeDisco(pos);
        if (clubTemp.get_activo()) {
            vIdsClubes.push_back(clubTemp.get_idclub());
        }
    }

    const int NUM_EQUIPOS = vIdsClubes.size();

    if (NUM_EQUIPOS < 2 || NUM_EQUIPOS % 2 != 0) {
        std::cout << "\n[ERROR] Se necesita una cantidad par de clubes activos para el fixture." << std::endl;
        std::cout << "Cantidad de clubes activos detectados: " << NUM_EQUIPOS << std::endl;
        return;
    }

    FILE *pFile = fopen("partidos.dat", "wb");
    if (pFile != NULL) fclose(pFile);

    int idPartidoContador = 1;
    const int NUM_JORNADAS = NUM_EQUIPOS - 1;
    const int PARTIDOS_POR_JORNADA = NUM_EQUIPOS / 2;

    for (int jornada = 1; jornada <= NUM_JORNADAS; jornada++) {
        for (int i = 0; i < PARTIDOS_POR_JORNADA; i++) {
            int localIndex = i;
            int visitanteIndex = NUM_EQUIPOS - 1 - i;

            int idLocal = vIdsClubes[localIndex];
            int idVisitante = vIdsClubes[visitanteIndex];

            if (jornada % 2 == 0) {
                std::swap(idLocal, idVisitante);
            }

            Partido nuevoPartido;
            nuevoPartido.set_idpartido(idPartidoContador++);
            nuevoPartido.set_idclublocal(idLocal);
            nuevoPartido.set_idclubvisitante(idVisitante);
            nuevoPartido.set_jornada(jornada);
            nuevoPartido.set_goleslocal(0);
            nuevoPartido.set_golesvisitante(0);
            nuevoPartido.set_jugado(false);
            nuevoPartido.set_activo(true);

            grabarEnDisco(nuevoPartido);
        }

        int ultimo = vIdsClubes[NUM_EQUIPOS - 1];
        for (int k = NUM_EQUIPOS - 1; k > 1; k--) {
            vIdsClubes[k] = vIdsClubes[k - 1];
        }
        vIdsClubes[1] = ultimo;
    }

    std::cout << "\n¡Fixture generado con éxito!" << std::endl;
    std::cout << "Se crearon " << (idPartidoContador - 1) << " partidos distribuidos en " << NUM_JORNADAS << " jornadas." << std::endl;
}
