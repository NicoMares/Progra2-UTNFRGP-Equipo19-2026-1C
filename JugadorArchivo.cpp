#include "JugadorArchivo.h"
#include <iostream>
#include <limits>

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

int JugadorArchivo::buscarDNI(int dni) {
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++) {
        Jugador jugador = leerDeDisco(i);
        if (jugador.get_dni() == dni) return i;
    }

    return -1;
}

void JugadorArchivo::listarPorDNI() {
    int cantidadRegistros = contarRegistros();
    Jugador *jugadores = new Jugador[cantidadRegistros];

    int pos = 0;
    while (pos < cantidadRegistros) {
        jugadores[pos] = leerDeDisco(pos);
        pos++;
    }

    for (int i = 0; i < cantidadRegistros - 1; i++) {
        for (int j = 0; j < cantidadRegistros - 1 - i; j++) {
            if (jugadores[j].get_dni() > jugadores[j + 1].get_dni()) {
                Jugador auxiliar = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = auxiliar;
            }
        }
    }

    for (int i = 0; i < cantidadRegistros; i++) {
        if (jugadores[i].get_activo()) {
            jugadores[i].mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    delete [] jugadores;
}

void JugadorArchivo::listarActivos() {
    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;

    int pos = 0;

    while (pos < ArchivoTemp.contarRegistros()) {
        JugadorTemp = ArchivoTemp.leerDeDisco(pos);
        if (JugadorTemp.get_activo()) {
            JugadorTemp.mostrar();
            std::cout << "--------------------------------" << std::endl;
        }
        pos++;
    }
}

void JugadorArchivo::listar() {
    JugadorArchivo archivo;
    Jugador jugador;

    int pos = 0;

    while (pos < archivo.contarRegistros()) {
        jugador = archivo.leerDeDisco(pos);
        jugador.mostrar();
        std::cout << "--------------------------------" << std::endl;
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

/* FUNCIONES PARA SIMULAR ACCIONES
   Se usan para validar que el club tenga 11 jugadores activos
   y para elegir un jugador real cuando se genera una accion. */
int JugadorArchivo::contarJugadoresActivosPorClub(int idClub)
{
    int cantidad = contarRegistros();
    int total = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Jugador jugador = leerDeDisco(i);
        if (jugador.get_activo() && jugador.get_idclub() == idClub)
        {
            total++;
        }
    }

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
    int cantidad = contarRegistros();

    for (int i = 0; i < cantidad; i++)
    {
        jugador = leerDeDisco(i);
        if (jugador.get_activo() && jugador.get_idclub() == idClub)
        {
            if (encontrados == elegido)
            {
                return jugador;
            }
            encontrados++;
        }
    }

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

    char confirmacion;
    std::cout << "¿Estás seguro que querés modificar al jugador '" << jugador.get_nombre() << " " << jugador.get_apellido() << "'? (S/N): ";
    std::cin >> confirmacion;
    if (confirmacion != 'S' && confirmacion != 's') {
        std::cout << "Operación cancelada." << std::endl;
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
        bool dniValido = false;
        do {
            std::cout << "Ingrese el nuevo DNI (20.000.000 - 50.000.000): ";
            std::cin >> dni;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ERROR: Solo se pueden ingresar números en el DNI." << std::endl;
            } else if (dni < 20000000 || dni > 50000000) {
                std::cout << "ERROR: El DNI debe estar entre 20M y 50M." << std::endl;
            } else {
                dniValido = true;
            }
        } while (!dniValido);
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