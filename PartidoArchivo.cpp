#include "PartidoArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include <iostream>
#include <cstdio>


bool PartidoArchivo::grabarEnDisco(Partido partido)
{
    FILE *pFile = fopen("partidos.dat", "ab");
    if (pFile == NULL) return false;

    bool ok = fwrite(&partido, sizeof(Partido), 1, pFile);

    fclose(pFile);
    return ok;
}

Partido PartidoArchivo::leerDeDisco(int posicion)
{
    Partido partido;

    FILE *pFile = fopen("partidos.dat", "rb");
    if (pFile == NULL) return partido;

    fseek(pFile, sizeof(Partido) * posicion, SEEK_SET);
    fread(&partido, sizeof(Partido), 1, pFile);

    fclose(pFile);

    return partido;
}
bool PartidoArchivo::modificarEnDisco(Partido partido, int posicion)
{
    FILE *pFile = fopen("partidos.dat", "rb+");
    if (pFile == NULL) return false;

    fseek(pFile, sizeof(Partido) * posicion, SEEK_SET);
    bool ok = fwrite(&partido, sizeof(Partido), 1, pFile);

    fclose(pFile);

    return ok;
}
int PartidoArchivo::contarRegistros()
{
    FILE *pFile = fopen("partidos.dat", "rb");
    if (pFile == NULL) return 0;

    fseek(pFile, 0, SEEK_END);
    int cantidad = ftell(pFile) / sizeof(Partido);

    fclose(pFile);

    return cantidad;
}
void PartidoArchivo::listarPorJornada(int jornadaBuscada)
{
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++)
    {
        Partido partido = leerDeDisco(i);

        if (partido.get_activo() &&
            partido.get_jornada() == jornadaBuscada)
        {
            std::cout << "ID Partido: " << partido.get_idpartido() << std::endl;
            std::cout << "Local: " << partido.get_idclublocal() << std::endl;
            std::cout << "Visitante: " << partido.get_idclubvisitante() << std::endl;
            std::cout << "Goles Local: " << partido.get_goleslocal() << std::endl;
            std::cout << "Goles Visitante: " << partido.get_golesvisitante() << std::endl;
            std::cout << "Jugado: " << (partido.get_jugado() ? "Si" : "No") << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
}

void PartidoArchivo::generarFixtureTorneo() {
    ClubArchivo archivoClub;
    int totalClubes = archivoClub.contarRegistros();

    int vIdsClubes[16];
    int cantidadActivos = 0;

    for (int i = 0; i < totalClubes; i++) {
        Club equipo = archivoClub.leerDeDisco(i); //
        if (equipo.get_activo()) {
            vIdsClubes[cantidadActivos] = equipo.get_idclub();
            cantidadActivos++;

            if (cantidadActivos == 16) break;
        }
    }

    if (cantidadActivos < 16) {
        std::cout << "ERROR: Se necesitan exactamente 16 equipos activos para generar el fixture." << std::endl;
        return;
    }

    FILE *pFile = fopen("partidos.dat", "wb");
    if (pFile != NULL) fclose(pFile);

    int idPartidoContador = 1;
    const int NUM_JORNADAS = 15;
    const int PARTIDOS_POR_FECHA = 8;

    for (int jornada = 1; jornada <= NUM_JORNADAS; jornada++) {
        for (int i = 0; i < PARTIDOS_POR_FECHA; i++) {
            int localIndex = i;
            int visitanteIndex = 15 - i;

            int idLocal = vIdsClubes[localIndex];
            int idVisitante = vIdsClubes[visitanteIndex];

            if (jornada % 2 == 0) {
                int aux = idLocal;
                idLocal = idVisitante;
                idVisitante = aux;
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

        int ultimo = vIdsClubes[15];
        for (int k = 15; k > 1; k--) {
            vIdsClubes[k] = vIdsClubes[k - 1];
        }
        vIdsClubes[1] = ultimo;
    }

    std::cout << "¡Fixture de 15 jornadas generado con éxito!" << std::endl;
}
