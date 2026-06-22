#include "JugadorArchivo.h"
#include <iostream>

#include <cstring>
#include <cstdio>
#include <cstdlib>
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
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return -1;

    Jugador jugador;
    int pos = 0;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
        if (jugador.get_idjugador() == idJugador) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

int JugadorArchivo::buscarPorDNI(int dni) {
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return -1;

    Jugador jugador;
    int pos = 0;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
        if (jugador.get_dni() == dni) {
            fclose(pFile);
            return pos;
        }
        pos++;
    }

    fclose(pFile);
    return -1;
}

int JugadorArchivo::obtenerProximoID() {
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return 1;

    Jugador jugador;
    int maximoID = 0;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
        if (jugador.get_idjugador() > maximoID) {
            maximoID = jugador.get_idjugador();
        }
    }

    fclose(pFile);
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

    FILE *pFile = fopen("jugadores.dat", "rb");
    Jugador jugador;
    bool encontrado = false;

    if (pFile != NULL) {
        while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
            if (jugador.get_activo() && strcmp(jugador.get_posicion(), posicionBuscada) == 0) {
                jugador.mostrar();
                std::cout << "-----------------------------" << std::endl;
                encontrado = true;
            }
        }
        fclose(pFile);
    }

    if (!encontrado) {
        std::cout << "No se encontraron jugadores activos con la posición: " << posicionBuscada << std::endl;
    }
}

int JugadorArchivo::buscarDNI(int dni) {
    int pos = 0;
    Jugador j;
    // Abrimos el archivo y recorremos registro por registro
    FILE* p = fopen("jugadores.dat", "rb");
    if (p == NULL) return -1;

    while (fread(&j, sizeof(Jugador), 1, p)) {
        if (j.get_dni() == dni) {
            fclose(p);
            return pos; // Devuelve la posición si lo encuentra
        }
        pos++;
    }
    fclose(p);
    return -1; // No se encontró
}

void JugadorArchivo::listarPorDNI() {
    int cantidadRegistros = contarRegistros();
    Jugador *jugadores = new Jugador[cantidadRegistros];

    FILE *pFile = fopen("jugadores.dat", "rb");
    int cargados = 0;
    if (pFile != NULL) {
        while (cargados < cantidadRegistros && fread(&jugadores[cargados], sizeof(Jugador), 1, pFile) == 1) {
            cargados++;
        }
        fclose(pFile);
    }

    for (int i = 0; i < cargados - 1; i++) {
        for (int j = 0; j < cargados - 1 - i; j++) {
            if (jugadores[j].get_dni() > jugadores[j + 1].get_dni()) {
                Jugador auxiliar = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = auxiliar;
            }
        }
    }

    for (int i = 0; i < cargados; i++) {
        if (jugadores[i].get_activo()) {
            jugadores[i].mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    delete [] jugadores;
}

void JugadorArchivo::listarActivos() {
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return;

    Jugador jugador;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
        if (jugador.get_activo()) {
            jugador.mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    fclose(pFile);
}

void JugadorArchivo::listar() {
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return;

    Jugador jugador;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
        jugador.mostrar();
        std::cout << "--------------------------------" << std::endl;
    }

    fclose(pFile);
}

void JugadorArchivo::listarPorClub() {
    int idClubBuscado;
    std::cout << "Ingrese el ID del club para listar sus jugadores: "<<std::endl;
    std::cin >> idClubBuscado;

    std::cout<<  "------------------------------" << std::endl;

    FILE *pFile = fopen("jugadores.dat", "rb");
    Jugador jugador;
    bool encontrado = false;

    if (pFile != NULL) {
        while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1) {
            if (jugador.get_activo() && jugador.get_idclub() == idClubBuscado) {
                jugador.mostrar();
                std::cout << "-----------------------------" << std::endl;
                encontrado = true;
            }
        }
        fclose(pFile);
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

/* FUNCIONES PARA SIMULAR ACCIONES
   Se usan para validar que el club tenga 11 jugadores activos
   y para elegir un jugador real cuando se genera una accion. */
int JugadorArchivo::contarJugadoresActivosPorClub(int idClub)
{
    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return 0;

    Jugador jugador;
    int total = 0;
    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1)
    {
        if (jugador.get_activo() && jugador.get_idclub() == idClub)
        {
            total++;
        }
    }

    fclose(pFile);
    return total;
}

Jugador JugadorArchivo::obtenerJugadorRandomPorClub(int idClub)
{
    Jugador jugador;
    int cantidadJugadores = contarJugadoresActivosPorClub(idClub);

    if (cantidadJugadores == 0)
    {
        return jugador;
    }

    int elegido = rand() % cantidadJugadores;
    int encontrados = 0;

    FILE *pFile = fopen("jugadores.dat", "rb");
    if (pFile == NULL) return Jugador();

    while (fread(&jugador, sizeof(Jugador), 1, pFile) == 1)
    {
        if (jugador.get_activo() && jugador.get_idclub() == idClub)
        {
            if (encontrados == elegido)
            {
                fclose(pFile);
                return jugador;
            }
            encontrados++;
        }
    }

    fclose(pFile);
    return Jugador();
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

    char confirmacion;
    std::cout << "¿Estás seguro que querés eliminar al jugador '" << JugadorTemp.get_nombre() << " " << JugadorTemp.get_apellido() << "'? (S/N): ";
    std::cin >> confirmacion;
    if (confirmacion != 'S' && confirmacion != 's') {
        std::cout << "Operación cancelada." << std::endl;
        return;
    }

    JugadorTemp.set_activo(false);

    if (ArchivoTemp.modificarEnDisco(JugadorTemp, pos)) {
        std::cout << "\nEl jugador fue eliminado con éxito del sistema." << std::endl;
    } else {
        std::cout << "\nError al intentar guardar en el archivo." << std::endl;
    }
















}

void JugadorArchivo::ModificarJugador()
{
    JugadorArchivo archivo;
    int idJugador;
     std::cout << "Ingrese el ID del jugador a modificar: ";
     std::cin >> idJugador;

    int pos = archivo.buscarPorID(idJugador);
    if (pos == -1)
    {
         std::cout << "No existe un jugador con ese ID." <<  std::endl;
        return;
    }

    Jugador jugador = archivo.leerDeDisco(pos);
    if (!jugador.get_activo())
    {
         std::cout << "No se puede modificar un jugador inactivo." <<  std::endl;
        return;
    }
    int opcion;

     std::cout << "1. Nombre" <<  std::endl;
     std::cout << "2. Apellido" <<  std::endl;
     std::cout << "3. DNI" <<  std::endl;
     std::cout << "4. Fecha de nacimiento" <<  std::endl;
     std::cout << "5. Club" <<  std::endl;
     std::cout << "6. Número de camiseta" <<  std::endl;
     std::cout << "7. Posición" <<  std::endl;
     std::cout << "8. Valor de mercado" <<  std::endl;
     std::cout << "Seleccioná el campo a modificar: ";
     std::cin >> opcion;

    if (opcion == 1)
    {
        char nombre[30];
         std::cout << "Ingrese el nuevo nombre: ";
         std::cin >>  std::ws;
         std::cin.getline(nombre, 30);
        jugador.set_nombre(nombre);
    }
    else if (opcion == 2)
    {
        char apellido[30];
         std::cout << "Ingrese el nuevo apellido: ";
         std::cin >>  std::ws;
         std::cin.getline(apellido, 30);
        jugador.set_apellido(apellido);
    }
    else if (opcion == 3)
    {
        int dni;
         std::cout << "Ingrese el nuevo DNI: ";
         std::cin >> dni;
        jugador.set_dni(dni);
    }
    else if (opcion == 4)
    {
        Fecha fecha;
         std::cout << "Ingrese la nueva fecha:" <<  std::endl;
        fecha.cargar();
        jugador.set_fechanacimiento(fecha);
    }
    else if (opcion == 5)
    {
        int idClub;
         std::cout << "Ingrese el nuevo ID de club: ";
         std::cin >> idClub;
        jugador.set_idclub(idClub);
    }
    else if (opcion == 6)
    {
        int camiseta;
         std::cout << "Ingresá el nuevo número de camiseta: ";
         std::cin >> camiseta;
        jugador.set_numerocamiseta(camiseta);
    }
    else if (opcion == 7)
    {
        char posicion[50];
         std::cout << "Ingresá la nueva posición: ";
         std::cin >>  std::ws;
         std::cin.getline(posicion, 50);
        jugador.set_posicion(posicion);
    }
    else if (opcion == 8)
    {
        float valor;
         std::cout << "Ingrese el nuevo valor de mercado: ";
         std::cin >> valor;
        jugador.set_valormercado(valor);
    }
    else
    {
        std:: cout << "Opción incorrecta." <<  std::endl;
        return;
    }

    if (archivo.modificarEnDisco(jugador, pos))
    {
        std::cout << "Jugador modificado correctamente." <<  std::endl;
    }
    else
    {
         std::cout << "No se pudo modificar el jugador." <<  std::endl;
    }
}