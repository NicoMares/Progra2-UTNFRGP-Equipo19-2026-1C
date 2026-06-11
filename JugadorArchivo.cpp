#include "JugadorArchivo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"

JugadorArchivo::JugadorArchivo()
{
 
}

bool JugadorArchivo::grabarEnDisco() {
    FILE *pFile;
    bool result;

    pFile = fopen("jugadores.dat", "ab");

    if (pFile == NULL) {
        return false;
    }

    result = fwrite(this, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return result;
}

bool JugadorArchivo::leerDeDisco(int posicion) {
    FILE *pFile;
    bool result;

    pFile = fopen("jugadores.dat", "rb");

    if (pFile == NULL) {
        return false;
    }

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET);
    result = fread(this, sizeof(Jugador), 1, pFile);

    fclose(pFile);

    return result;
}

void JugadorArchivo::ConsultarPorDNI() {
    int dniBuscado;
    std::cout << "Ingrese el DNI del jugador que desea consultar: ";
    std::cin >> dniBuscado;

    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;

    int pos = 0;
    bool encontrado = false;

    while (ArchivoTemp.leerDeDisco(pos)) {
        if (JugadorTemp.get_dni() == dniBuscado) {
            JugadorTemp.mostrar();
            encontrado = true;
            break;
        }
        pos++;
    }

    if (!encontrado) {
        std::cout << "No se encontro un jugador con el DNI: " << dniBuscado << std::endl;
    }
}

void JugadorArchivo ::consultarPorPosicion() {
    char posicionBuscada[50];
    std::cout << "Ingrese la posición del jugador que desea consultar: ";
    std::cin >> posicionBuscada;

   JugadorArchivo ArchivoTemp;
   Jugador JugadorTemp;


    int pos = 0;
    bool encontrado = false;

    while (ArchivoTemp.leerDeDisco(pos)) {
        if (strcmp(JugadorTemp.get_posicion(), posicionBuscada) == 0) {
            JugadorTemp.mostrar();
            std::cout << "-----------------------------" << std::endl;
            encontrado = true;
        }
        pos++;
    }

    if (!encontrado) {
        std::cout << "No se encontraron jugadores con la posicion: " << posicionBuscada << std::endl;
    }
}

void JugadorArchivo::ListarDni() {

    

    JugadorArchivo ArchivoTemp;
    Jugador JugadorTemp;
  
    int pos = 0;


 while (ArchivoTemp.leerDeDisco(pos))
            {
                JugadorTemp.mostrar();
             
                pos++;
            }

}

void JugadorArchivo::TodosJugadores() {
   
 JugadorArchivo ArchivoTemp;
Jugador JugadorTemp;



    int pos = 0;

    while (ArchivoTemp.leerDeDisco(pos)) {
        JugadorTemp.mostrar();
        std::cout << "-----------------------------" << std::endl;
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

    while (ArchivoTemp.leerDeDisco(pos)) {
        if (JugadorTemp.get_idclub() == idClubBuscado) {
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

bool JugadorArchivo::modificarEnDisco(int posicion)
{
    FILE *pFile = fopen("jugadores.dat", "rb+"); 
    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * sizeof(Jugador), SEEK_SET); 
    bool seEscribio = fwrite(this, sizeof(Jugador), 1, pFile); 
    fclose(pFile); 
    return seEscribio; 
}

void JugadorArchivo::EliminarJugador() {
   
            int idBuscado;
            std::cout << "Ingrese el ID o DNI del jugador a eliminar: ";
            std::cin >> idBuscado;

         
            JugadorArchivo ArchivoTemp;
            Jugador JugadorTemp;


            int pos = 0;
            bool encontrado = false;

            while (ArchivoTemp.leerDeDisco(pos)) 
            {
                if (JugadorTemp.get_idjugador() == idBuscado && JugadorTemp.get_activo() == true) 
                {
                    encontrado = true;
                    
                    JugadorTemp.set_activo(false); 
                    
                    if (ArchivoTemp.modificarEnDisco(pos)) { 
                        std::cout << "\n  El jugador fue eliminado con éxito del sistema." << std::endl;
                    } else {
                        std::cout << "\n  Error al intentar guardar en el archivo." << std::endl;
                    }
                    break; 
                }
                pos++;
            }
            if (!encontrado) std::cout << "No se encontró ningún jugador activo con el ID/DNI ingresado." << std::endl;
}
