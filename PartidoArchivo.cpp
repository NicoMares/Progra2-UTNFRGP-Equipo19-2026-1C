#include "PartidoArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

struct RegistroTabla
{
    Club club;
    int posicionArchivo;
    int golesFavor;
    int golesContra;
    int diferenciaGol;
    int puntos;
};

bool estaIncluido(int idsClubes[], int cantidad, int idClub)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (idsClubes[i] == idClub)
        {
            return true;
        }
    }

    return false;
}

bool debeIrAntes(RegistroTabla club1, RegistroTabla club2)
{
    if (club1.puntos != club2.puntos)
    {
        return club1.puntos > club2.puntos;
    }

    if (club1.diferenciaGol != club2.diferenciaGol)
    {
        return club1.diferenciaGol > club2.diferenciaGol;
    }

    if (club1.golesFavor != club2.golesFavor)
    {
        return club1.golesFavor > club2.golesFavor;
    }

    return strcmp(club1.club.get_nombre(), club2.club.get_nombre()) < 0;
}

int cargarTabla(RegistroTabla tabla[])
{
    PartidoArchivo archivoPartidos;
    ClubArchivo archivoClubes;
    int cantidadPartidos = archivoPartidos.contarRegistros();

    int idsClubes[16];
    int cantidadClubes = 0;

    for (int i = 0; i < cantidadPartidos; i++)
    {
        Partido partido = archivoPartidos.leerDeDisco(i);

        if (!estaIncluido(idsClubes, cantidadClubes, partido.get_idclublocal()))
        {
            idsClubes[cantidadClubes] = partido.get_idclublocal();
            cantidadClubes++;
        }

        if (!estaIncluido(idsClubes, cantidadClubes, partido.get_idclubvisitante()))
        {
            idsClubes[cantidadClubes] = partido.get_idclubvisitante();
            cantidadClubes++;
        }
    }

    int cantidadRegistros = 0;

    for (int i = 0; i < cantidadClubes; i++)
    {
        int posicionClub = archivoClubes.buscarPorID(idsClubes[i]);
        Club club = archivoClubes.leerDeDisco(posicionClub);

        tabla[cantidadRegistros].club = club;
        tabla[cantidadRegistros].posicionArchivo = posicionClub;
        tabla[cantidadRegistros].golesFavor = archivoPartidos.calcularGolesFavor(idsClubes[i]);
        tabla[cantidadRegistros].golesContra = archivoPartidos.calcularGolesContra(idsClubes[i]);
        tabla[cantidadRegistros].diferenciaGol = archivoPartidos.calcularDiferenciaGol(idsClubes[i]);
        tabla[cantidadRegistros].puntos = club.calcularPuntos();
        cantidadRegistros++;
    }

    for (int i = 0; i < cantidadRegistros - 1; i++)
    {
        for (int j = 0; j < cantidadRegistros - 1 - i; j++)
        {
            if (debeIrAntes(tabla[j + 1], tabla[j]))
            {
                RegistroTabla auxiliar = tabla[j];
                tabla[j] = tabla[j + 1];
                tabla[j + 1] = auxiliar;
            }
        }
    }

    return cantidadRegistros;
}

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

bool PartidoArchivo::modificarEnDisco(Partido reg, int pos) {
    FILE* p = fopen("partidos.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    fseek(p, pos * sizeof(Partido), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Partido), 1, p);
    fclose(p);
    return escribio;
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
    ClubArchivo archivoClub;

    for (int i = 0; i < cantidad; i++)
    {
        Partido partido = leerDeDisco(i);

        if (partido.get_activo() &&
            partido.get_jornada() == jornadaBuscada)
        {
            int posLocal = archivoClub.buscarPorID(partido.get_idclublocal());
            int posVisitante = archivoClub.buscarPorID(partido.get_idclubvisitante());

            Club clubLocal = archivoClub.leerDeDisco(posLocal);
            Club clubVisitante = archivoClub.leerDeDisco(posVisitante);

            std::cout << "ID Partido: " << partido.get_idpartido() << std::endl;
            std::cout << "Local: " << clubLocal.get_nombre() << std::endl;
            std::cout << "Visitante: " << clubVisitante.get_nombre() << std::endl;
            std::cout << "Goles Local: " << partido.get_goleslocal() << std::endl;
            std::cout << "Goles Visitante: " << partido.get_golesvisitante() << std::endl;
            std::cout << "Jugado: " << (partido.get_jugado() ? "Si" : "No") << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
}

void PartidoArchivo::generarFixtureTorneo() {
    srand(time(NULL));

    ClubArchivo archivoClub;
    int cantidadClubes = archivoClub.contarRegistros();

    if (cantidadClubes < 16) {
        std::cout << "Error: Se necesitan al menos 16 clubes cargados para generar el fixture." << std::endl;
        return;
    }

    // Ponemos en 0 todas las rachas de los clubes antes de arrancar
    for (int i = 0; i < cantidadClubes; i++) {
        Club c = archivoClub.leerDeDisco(i);
        for (int j = 0; j < 16; j++) {
            c.set_racha(j, 0);
        }
        archivoClub.modificarEnDisco(c, i);
    }

    int vIdsClubes[16];
    for (int i = 0; i < 16; i++) {
        Club c = archivoClub.leerDeDisco(i);
        vIdsClubes[i] = c.get_idclub();
    }

    int idPartidoContador = 1;

    // Vaciamos el archivo de partidos anterior para crear el nuevo fixture vacío
    FILE *pLimpiar = fopen("partidos.dat", "wb");
    if (pLimpiar != NULL) fclose(pLimpiar);

    for (int jornada = 1; jornada <= 15; jornada++) {
        for (int i = 0; i < 8; i++) {
            int idLocal = vIdsClubes[i];
            int idVisitante = vIdsClubes[15 - i];

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

            // Nacen sin goles y en FALSE (no jugados todavía)
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

    std::cout << "¡Fixture de 15 jornadas generado con éxito! Listo para simular progresivamente." << std::endl;
}

int PartidoArchivo::obtenerSiguienteJornadaAJugarse()
{
    int cantPartidos = contarRegistros();

    if (cantPartidos <= 0) {
        return 1; // Si no hay registros (o da error), asumimos que arranca en la Jornada 1
    }

    for (int i = 0; i < cantPartidos; i++) {
        Partido p = leerDeDisco(i);
        if (p.get_activo() && !p.get_jugado()) {
            return p.get_jornada(); // Retorna la primera jornada que encuentre colgada
        }
    }

    return -1; // Solo si recorrió absolutamente TODO y todo está en true, devuelve -1
}

void PartidoArchivo::VerPartidos()
{
    system("cls");
    std::cout << "========================================" << std::endl;
    std::cout << "        LISTADO TOTAL DE PARTIDOS       " << std::endl;
    std::cout << "========================================" << std::endl;

    // Recorremos las 15 jornadas y reutilizamos tu lógica de listado
    for (int j = 1; j <= 15; j++)
    {
        std::cout << "\n>>> JORNADA " << j << " <<<" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        listarPorJornada(j);
    }

    std::cout << "\nSe han listado los 120 partidos del torneo." << std::endl;
    system("pause");
}

void PartidoArchivo::simularSiguienteJornada()
{
    int jornadaAIntervenir = obtenerSiguienteJornadaAJugarse();

    if (jornadaAIntervenir == -1) {
        std::cout << "\n[!] El torneo ya finalizo. No hay mas jornadas para simular." << std::endl;
        return;
    }

    std::cout << "\n=======================================================" << std::endl;
    std::cout << "          SIMULANDO AUTOMATICAMENTE JORNADA " << jornadaAIntervenir << std::endl;
    std::cout << "=======================================================" << std::endl;

    srand(time(NULL));
    int cantPartidos = contarRegistros();
    ClubArchivo archivoClub;

    for (int i = 0; i < cantPartidos; i++) {
        Partido partido = leerDeDisco(i);

        if (partido.get_jornada() == jornadaAIntervenir && !partido.get_jugado() && partido.get_activo()) {

            int golesL = rand() % 5;
            int golesV = rand() % 5;

            partido.set_goleslocal(golesL);
            partido.set_golesvisitante(golesV);
            partido.set_jugado(true);
           

            // 1. Guardamos el partido modificado en partidos.dat
            bool guardoPartido = modificarEnDisco(partido, i);

            if (!guardoPartido) {
                std::cout << "[ERROR] No se pudo guardar el resultado en el archivo binario." << std::endl;
                continue;
            }

            // 2. Buscamos los clubes para impactar sus vectores de racha en clubes.dat
            int posLocal = archivoClub.buscarPorID(partido.get_idclublocal());
            int posVisitante = archivoClub.buscarPorID(partido.get_idclubvisitante());

            if (posLocal != -1 && posVisitante != -1) {
                Club clubLocal = archivoClub.leerDeDisco(posLocal);
                Club clubVisitante = archivoClub.leerDeDisco(posVisitante);

                if (golesL > golesV) {
                    clubLocal.set_racha(jornadaAIntervenir, 1);     // [V]
                    clubVisitante.set_racha(jornadaAIntervenir, 3); // [D]
                }
                else if (golesL < golesV) {
                    clubLocal.set_racha(jornadaAIntervenir, 3);     // [D]
                    clubVisitante.set_racha(jornadaAIntervenir, 1); // [V]
                }
                else {
                    clubLocal.set_racha(jornadaAIntervenir, 2);     // [E]
                    clubVisitante.set_racha(jornadaAIntervenir, 2); // [E]
                }


                archivoClub.modificarEnDisco(clubLocal, posLocal);
                archivoClub.modificarEnDisco(clubVisitante, posVisitante);

                std::cout << " -> " << clubLocal.get_nombre() << " " << golesL
                          << " - " << golesV << " " << clubVisitante.get_nombre() << " [OK]" << std::endl;
            }
        }
    }
    std::cout << "=======================================================" << std::endl;
    std::cout << "[OK] Jornada " << jornadaAIntervenir << " procesada con exito." << std::endl;

    if (obtenerSiguienteJornadaAJugarse() == -1)
    {
        aplicarResultadosFinales();
    }
}

int PartidoArchivo::calcularGolesFavor(int idClub)
{
    int total = 0;
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {

        Partido partidoJugado = leerDeDisco(i);


        if (partidoJugado.get_activo() && partidoJugado.get_jugado()) {

            if (partidoJugado.get_idclublocal() == idClub)
            {
                total += partidoJugado.get_goleslocal();

            }
            
            else if (partidoJugado.get_idclubvisitante() == idClub)
            {
                total += partidoJugado.get_golesvisitante();

            }
        }
    }
    return total;
}

int PartidoArchivo::calcularGolesContra(int idClub)
{
    int total = 0;
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {

        Partido partidoJugado = leerDeDisco(i);

        if (partidoJugado.get_activo() && partidoJugado.get_jugado()) 
        {

            if (partidoJugado.get_idclublocal() == idClub)
            {
                total += partidoJugado.get_golesvisitante();

            }

            else if (partidoJugado.get_idclubvisitante() == idClub)
        {
            total += partidoJugado.get_goleslocal();

        }
        
        }
    }
    return total;
}

int PartidoArchivo::calcularDiferenciaGol(int idClub)
{
    return calcularGolesFavor(idClub) - calcularGolesContra(idClub);
}

void PartidoArchivo::listarTablaPosiciones()
{
    int cantidadPartidos = contarRegistros();

    if (cantidadPartidos == 0)
    {
        std::cout << "No hay un fixture generado, generarlo antes de mostrar la tabla." << std::endl;
        return;
    }

    RegistroTabla tabla[16];
    int cantidadRegistros = cargarTabla(tabla);
    bool torneoFinalizado = obtenerSiguienteJornadaAJugarse() == -1;

    std::cout << "==============================================================================" << std::endl;
    std::cout << "                             TABLA DE POSICIONES" << std::endl;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "POS\tCLUB                    GF\tGC\tDG\tPTS\tCONDICION" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        const char *nombreClub = tabla[i].club.get_nombre();
        const char *estado = "";

        if (torneoFinalizado && i == 0)
        {
            estado = "CAMPEON";
        }
        else if (torneoFinalizado && i >= cantidadRegistros - 3)
        {
            estado = "DESCENSO";
        }

        std::cout << i + 1 << "\t"
                  << nombreClub;

        for (int j = strlen(nombreClub); j < 24; j++)
        {
            std::cout << " ";
        }

        std::cout << tabla[i].golesFavor << "\t"
                  << tabla[i].golesContra << "\t"
                  << tabla[i].diferenciaGol << "\t"
                  << tabla[i].puntos << "\t"
                  << estado << std::endl;
    }

    std::cout << "==============================================================================" << std::endl;
    std::cout << "GF: Goles a favor | GC: Goles en contra | DG: Diferencia de gol | PTS: Puntos" << std::endl;
}

void PartidoArchivo::aplicarResultadosFinales()
{
    RegistroTabla tabla[16];
    int cantidadRegistros = cargarTabla(tabla);

    ClubArchivo archivoClubes;

    Club campeon = tabla[0].club;

    // Se aumenta en 1 la cantidad de trofeos del campeón
    campeon.set_cantidadtrofeos(campeon.get_cantidadtrofeos() + 1);
    archivoClubes.modificarEnDisco(campeon, tabla[0].posicionArchivo);

    // Se aumenta en 1 la cantidad de descensos de los últimos 3 clubes
    for (int i = cantidadRegistros - 3; i < cantidadRegistros; i++)
    {
        Club descendido = tabla[i].club;
        descendido.set_cantidaddescensos(descendido.get_cantidaddescensos() + 1);
        archivoClubes.modificarEnDisco(descendido, tabla[i].posicionArchivo);
    }

    std::cout << "Campeon y descensos registrados en los clubes." << std::endl;
}

void PartidoArchivo:: VerJornada(){

    PartidoArchivo archivo;
 int nroJornada;

                std::cout << "\nIngrese el numero de Jornada que desea ver (1 a 15): "<< std::endl;
                std::cout << "-------------------------------------------------------"<< std::endl;
               std::cin >> nroJornada;

                system ("cls");

                if (nroJornada >= 1 && nroJornada <= 15) {
                    archivo.listarPorJornada(nroJornada);
                } else {
                    std::cout << "Número de jornada invalido." <<std:: endl;
                }



}



