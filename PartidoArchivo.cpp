#include "PartidoArchivo.h"
#include "AccionArchivo.h"
#include "ClubArchivo.h"
#include "Club.h"
#include "JugadorArchivo.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

bool PartidoArchivo::existeClub(int idsClubes[], int cantidad, int idClub)
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

int PartidoArchivo::cargarTabla(PosicionTabla filas[])
{
    ClubArchivo archivoClubes;
    int cantidadPartidos = contarRegistros();

    int idsClubes[16];
    int cantidadClubes = 0;

    for (int i = 0; i < cantidadPartidos; i++)
    {
        Partido partido = leerDeDisco(i);

        if (!existeClub(idsClubes, cantidadClubes, partido.get_idclublocal()))
        {
            idsClubes[cantidadClubes] = partido.get_idclublocal();
            cantidadClubes++;
        }

        if (!existeClub(idsClubes, cantidadClubes, partido.get_idclubvisitante()))
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

        filas[cantidadRegistros].setClub(club);
        filas[cantidadRegistros].setGolesFavor(calcularGolesFavor(idsClubes[i]));
        filas[cantidadRegistros].setGolesContra(calcularGolesContra(idsClubes[i]));
        filas[cantidadRegistros].setDiferenciaGol(calcularDiferenciaGol(idsClubes[i]));
        filas[cantidadRegistros].setPuntos(club.calcularPuntos());
        cantidadRegistros++;
    }

    for (int i = 0; i < cantidadRegistros - 1; i++)
    {
        for (int j = 0; j < cantidadRegistros - 1 - i; j++)
        {
            if (filas[j + 1].superaA(filas[j]))
            {
                PosicionTabla auxiliar = filas[j];
                filas[j] = filas[j + 1];
                filas[j + 1] = auxiliar;
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

    // Solo participan clubes ACTIVOS y de PRIMERA DIVISION
    int vIdsClubes[16];
    int cantidadActivos = 0;
    for (int i = 0; i < cantidadClubes && cantidadActivos < 16; i++) {
        Club c = archivoClub.leerDeDisco(i);

        if (c.get_activo() && c.get_division() == 1) {
            vIdsClubes[cantidadActivos] = c.get_idclub();
            cantidadActivos++;
        }
    }

    if (cantidadActivos < 16) {
        std::cout << "Error: Se necesitan al menos 16 clubes ACTIVOS y de PRIMERA DIVISION para generar el fixture." << std::endl;
        return;
    }

    for (int i = 0; i < cantidadClubes; i++) {
        Club c = archivoClub.leerDeDisco(i);
        for (int j = 0; j < 16; j++) {
            c.set_racha(j, 0);
        }
        archivoClub.modificarEnDisco(c, i);
    }

    int idPartidoContador = 1;

    // Vaciamos el archivo de partidos anterior para crear el nuevo fixture vacío
    FILE *pLimpiar = fopen("partidos.dat", "wb");
    if (pLimpiar != NULL) fclose(pLimpiar);

    // AL GENERAR FIXTURE NUEVO SE BORRAN LAS ACCIONES ANTERIORES

    AccionArchivo archivoAcciones;
    archivoAcciones.vaciarArchivo();

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

    std::cout << "Fixture generado exitosamente con 16 equipos de Primera Division." << std::endl;
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
    /* No se simula la jornada si algun club que participa no tiene 11 jugadores activos. */
    JugadorArchivo archivoJugadoresValidacion;
    ClubArchivo archivoClubValidacion;
    int cantPartidosValidacion = contarRegistros();
    bool faltanJugadores = false;

    for (int i = 0; i < cantPartidosValidacion; i++) {
        Partido partido = leerDeDisco(i);
        if (partido.get_jornada() == jornadaAIntervenir && !partido.get_jugado() && partido.get_activo()) {
            int jugadoresLocal = archivoJugadoresValidacion.contarJugadoresActivosPorClub(partido.get_idclublocal());
            int jugadoresVisitante = archivoJugadoresValidacion.contarJugadoresActivosPorClub(partido.get_idclubvisitante());

            if (jugadoresLocal < 11 || jugadoresVisitante < 11) {
                if (!faltanJugadores) {
                    std::cout << "No todos los equipos tienen 11 jugadores." << std::endl;
                    faltanJugadores = true;
                }
                if (jugadoresLocal < 11) {
                    Club club = archivoClubValidacion.leerDeDisco(archivoClubValidacion.buscarPorID(partido.get_idclublocal()));
                    std::cout << "Club " << club.get_nombre() << " tiene " << jugadoresLocal << " jugadores activos. Faltan " << 11 - jugadoresLocal << "." << std::endl;
                }
                if (jugadoresVisitante < 11) {
                    Club club = archivoClubValidacion.leerDeDisco(archivoClubValidacion.buscarPorID(partido.get_idclubvisitante()));
                    std::cout << "Club " << club.get_nombre() << " tiene " << jugadoresVisitante << " jugadores activos. Faltan " << 11 - jugadoresVisitante << "." << std::endl;
                }
            }
        }
    }

    if (faltanJugadores) {
        return;
    }

    std::cout << "\n=======================================================" << std::endl;
    std::cout << "          SIMULANDO AUTOMATICAMENTE JORNADA " << jornadaAIntervenir << std::endl;
    std::cout << "=======================================================" << std::endl;

    srand(time(NULL));
    int cantPartidos = contarRegistros();
    ClubArchivo archivoClub;
    AccionArchivo archivoAcciones;

    for (int i = 0; i < cantPartidos; i++) {
        Partido partido = leerDeDisco(i);

        if (partido.get_jornada() == jornadaAIntervenir && !partido.get_jugado() && partido.get_activo()) {

            int posLocal = archivoClub.buscarPorID(partido.get_idclublocal());
            int posVisitante = archivoClub.buscarPorID(partido.get_idclubvisitante());

            if (posLocal == -1 || posVisitante == -1) {
                std::cout << "[ERROR] No se encontraron los clubes del partido ID "
                          << partido.get_idpartido() << "." << std::endl;
                continue;
            }

            Club clubLocal = archivoClub.leerDeDisco(posLocal);
            Club clubVisitante = archivoClub.leerDeDisco(posVisitante);

            /* LAS ACCIONES GENERAN EL RESULTADO DEL PARTIDO
               Antes se hacia:
                   golesL = rand() % 5;
                   golesV = rand() % 5;
               Eso daba un resultado sin jugadores.
               Ahora AccionArchivo genera acciones y PartidoArchivo cuenta
               cuantos goles hizo cada club segun acciones.dat. */
            archivoAcciones.simularAccionesDePartido(partido);

            int golesL = archivoAcciones.contarGolesPorPartidoYClub(partido.get_idpartido(), partido.get_idclublocal());
            int golesV = archivoAcciones.contarGolesPorPartidoYClub(partido.get_idpartido(), partido.get_idclubvisitante());

            /* El partido guarda el resultado como resumen.
               La base del resultado fueron las acciones tipo Gol. */
            partido.set_goleslocal(golesL);
            partido.set_golesvisitante(golesV);
            partido.set_jugado(true);

            // 1. Guardamos el partido modificado en partidos.dat
            bool guardoPartido = modificarEnDisco(partido, i);

            if (!guardoPartido) {
                std::cout << "[ERROR] No se pudo guardar el resultado en el archivo binario." << std::endl;
                continue;
            }

            if (posLocal != -1 && posVisitante != -1) {
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
                          << " - " << golesV << " " << clubVisitante.get_nombre() << std::endl;
            }
        }
    }
    std::cout << "=======================================================" << std::endl;
    std::cout << "Jornada " << jornadaAIntervenir << " procesada con exito." << std::endl;

    if (obtenerSiguienteJornadaAJugarse() == -1)
    {
        aplicarResultadosFinales();
    }
}

/* Simula todas las jornadas que falten de una sola vez (para testeo rapido).
   (p. ej. la validacion la bloqueo porque un club no tiene 11 jugadores). */
void PartidoArchivo::simularTorneoCompleto()
{
    int fecha = obtenerSiguienteJornadaAJugarse();

    if (fecha == -1) {
        std::cout << "\n[!] El torneo ya finalizo. No hay jornadas para simular." << std::endl;
        return;
    }

    while (fecha != -1) {
        simularSiguienteJornada();

        int siguiente = obtenerSiguienteJornadaAJugarse();
        if (siguiente == fecha) {
            break;
        }
        fecha = siguiente;
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

    PosicionTabla tabla[16];
    int cantidadRegistros = cargarTabla(tabla);
    bool torneoFinalizado = obtenerSiguienteJornadaAJugarse() == -1;

    std::cout << "==============================================================================" << std::endl;
    std::cout << "                             TABLA DE POSICIONES" << std::endl;
    std::cout << "==============================================================================" << std::endl;
    std::cout << "POS\tCLUB                    GF\tGC\tDG\tPTS\tCONDICION" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        Club club = tabla[i].getClub();
        const char *nombreClub = club.get_nombre();
        const char *estado = "";

        if (torneoFinalizado && i == 0)
        {
            estado = "CAMPEON";
        }
        else if (torneoFinalizado && i >= cantidadRegistros - 3)
        {
            estado = "DESCENSO";
        }

        std::cout << i + 1 << "\t" << nombreClub;

        for (int j = strlen(nombreClub); j < 24; j++)
        {
            std::cout << " ";
        }

        std::cout << tabla[i].getGolesFavor() << "\t"
                  << tabla[i].getGolesContra() << "\t"
                  << tabla[i].getDiferenciaGol() << "\t"
                  << tabla[i].getPuntos() << "\t"
                  << estado << std::endl;
    }

    std::cout << "==============================================================================" << std::endl;
    std::cout << "GF: Goles a favor | GC: Goles en contra | DG: Diferencia de gol | PTS: Puntos" << std::endl;

    if (torneoFinalizado) {
        ClubArchivo archClub;

        Club ultimoEquipo = tabla[cantidadRegistros - 1].getClub();
        int posUltimo = archClub.buscarPorID(ultimoEquipo.get_idclub());
        Club checkClub = archClub.leerDeDisco(posUltimo);

        if (checkClub.get_division() == 1) {
            std::cout << "\n[!] PROCESANDO CIERRE DE TEMPORADA..." << std::endl;

        

            // Contamos primero cuántos hay en Segunda
            int totalRegistros = archClub.contarRegistros();
            int posicionesSegunda[100];
            int contadorSegunda = 0;

            for (int i = 0; i < totalRegistros; i++) {
                Club c = archClub.leerDeDisco(i);
                if (c.get_activo() && c.get_division() == 2) {
                    posicionesSegunda[contadorSegunda] = i;
                    contadorSegunda++;
                }
            }

            //
            if (contadorSegunda >= 3) {

            

                //ASCENDER A 3 RANDOM
                std::cout << "\n=== NUEVOS ASCENDIDOS A PRIMERA DIVISION ===" << std::endl;
                int ascendidos = 0;
                bool elegido[100] = { false };
                srand(time(NULL));

                while (ascendidos < 3) {
                    int indiceAzar = rand() % contadorSegunda;
                    if (!elegido[indiceAzar]) {
                        elegido[indiceAzar] = true;
                        int posDisco = posicionesSegunda[indiceAzar];

                        Club c = archClub.leerDeDisco(posDisco);
                        c.set_division(1);
                        archClub.modificarEnDisco(c, posDisco);

                        std::cout << "- " << c.get_nombre() << " (Ascendio de 2da a 1era)" << std::endl;
                        ascendidos++;
                    }
                }
                std::cout << "============================================" << std::endl;

            } else {
                // Si no hay tres en segunda, se cancela el recambio de equipos para no romper el fixture
                std::cout << "\n[AVISO] No hay suficientes equipos en 2da Division (Solo hay " << contadorSegunda << ")." << std::endl;
                std::cout << "-> Esta temporada NO HABRA DESCENSOS para mantener los 16 equipos de Primera." << std::endl;
                std::cout << "-> Por favor, crea mas clubes en Segunda Division para activar el sistema." << std::endl;
            }
        }
    }
}

/* RACHAS ORDENADAS DEL MEJOR AL PEOR RENDIMIENTO */
void PartidoArchivo::listarRachasClubesOrdenadas()
{
    int cantidadPartidos = contarRegistros();

    if (cantidadPartidos == 0)
    {
        std::cout << "No hay un fixture generado, generarlo antes de mostrar las rachas." << std::endl;
        return;
    }

    PosicionTabla tabla[16];
    int cantidadRegistros = cargarTabla(tabla);

    std::cout << "==========================================================" << std::endl;
    std::cout << "              RACHAS DE CLUBES" << std::endl;
    std::cout << "==========================================================" << std::endl;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        Club club = tabla[i].getClub();
        std::cout << i + 1 << ". " << club.get_nombre()
                  << " | PTS: " << tabla[i].getPuntos()
                  << " | DG: " << tabla[i].getDiferenciaGol() << std::endl;
        club.mostrarRacha();
        std::cout << "----------------------------------------------------------" << std::endl;
    }
}

void PartidoArchivo::aplicarResultadosFinales()
{
    PosicionTabla tabla[16];
    int cantidadRegistros = cargarTabla(tabla);

    ClubArchivo archivoClubes;

    // El campeon es el primero de la tabla ordenada.
    Club campeon = tabla[0].getClub();
    archivoClubes.sumarTrofeo(campeon.get_idclub());

    // Los ultimos 3 de la tabla descienden.
    for (int i = cantidadRegistros - 3; i < cantidadRegistros; i++)
    {
        Club descendido = tabla[i].getClub();
        archivoClubes.sumarDescenso(descendido.get_idclub());
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



