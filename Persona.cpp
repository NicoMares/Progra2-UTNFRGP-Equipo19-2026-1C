#include <iostream>
#include <cstring>
#include "Persona.h"
#include "utils.h"

Persona::Persona() {
    strcpy(_Nombre, "");
    strcpy(_Apellido, "");
    _Dni = 0;
    _Activo = true;
}

void Persona::cargar() {
    char nombre[30], apellido[30];
    int dni;
    Fecha fecha;

    //Validación Nombre
    do {
        std::cout << "Ingrese nombre: ";
        std::cin >> nombre;
    } while (!soloLetras(nombre));
    set_nombre(nombre);

    //Validación Apellido
    do {
        std::cout << "Ingrese apellido: ";
        std::cin >> apellido;
    } while (!soloLetras(apellido));
    set_apellido(apellido);

    //Validación DNI (20M a 50M)
    do {
        std::cout << "Ingrese DNI (20.000.000 - 50.000.000): ";
        std::cin >> dni;
        if (dni < 20000000 || dni > 50000000) {
            std::cout << "ERROR: El DNI debe estar entre 20M y 50M." << std::endl;
        }
    } while (dni < 20000000 || dni > 50000000);
    set_dni(dni);

    //Fecha
    std::cout << "Ingrese fecha de nacimiento: " << std::endl;
    fecha.cargar();
    set_fechanacimiento(fecha);

    set_activo(true);
}

void Persona::mostrar() {
    std::cout << "Nombre: " << _Nombre << std::endl;
    std::cout << "Apellido: " << _Apellido << std::endl;
    std::cout << "DNI: " << _Dni << std::endl;

    std::cout << "Fecha de nacimiento: ";
    _FechaNacimiento.mostrar();

    std::cout << "Activo: ";
    if (_Activo == true) {
        std::cout << "Si" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
}

const char* Persona::get_nombre() {
    return _Nombre;
}

const char* Persona::get_apellido() {
    return _Apellido;
}

int Persona::get_dni() {
    return _Dni;
}

bool Persona::get_activo() {
    return _Activo;
}

Fecha Persona::get_fechanacimiento() {
    return _FechaNacimiento;
}

void Persona::set_nombre(const char nombre[]) {
    strcpy(_Nombre, nombre);
}

void Persona::set_apellido(const char apellido[]) {
    strcpy(_Apellido, apellido);
}

void Persona::set_dni(int dni) {
    _Dni = dni;
}

void Persona::set_fechanacimiento(Fecha fecha_nacimiento) {
    _FechaNacimiento = fecha_nacimiento;
}

void Persona::set_activo(bool activo) {
    _Activo = activo;
}
