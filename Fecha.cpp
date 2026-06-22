#include <iostream>
#include "Fecha.h"
#include <cstdlib>

Fecha::Fecha() {
    _Dia = 0 ;
    _Mes = 0 ;
    _Anio = 0;
}

int Fecha::get_Dia() {
    return _Dia;

}

int Fecha::get_Mes() {
    return _Mes;
}
int Fecha::get_Anio( ) {
return _Anio;

}
//SAQUE VALIDACIONES DE LOS SETTERS
void Fecha::set_Dia( int dia){


        _Dia = dia;
}

void Fecha::set_Mes(int mes ){

    _Mes = mes;

}

void Fecha::set_Anio(int anio ){
    _Anio = anio;
}


bool Fecha::esValida() {
    if (_Mes < 1 || _Mes > 12) return false;
    int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (_Dia < 1 || _Dia > dias[_Mes]) return false;
    if (_Anio < 1800 || _Anio > 2026) return false;
    return true;
}

void Fecha::cargar() {
    bool esCorrecta = false;
    do {
        std::cout << "Dia: "; std::cin >> _Dia;
        std::cout << "Mes: "; std::cin >> _Mes;
        std::cout << "Año: "; std::cin >> _Anio;

        //Validación
        if (esValida()) {
            esCorrecta = true;
        } else {

            std::cout << "\n¡ERROR EN LA CARGA DE DATOS! La fecha ingresada no es válida." << std::endl;
            std::cout << "Por favor, ingrese los datos nuevamente.\n" << std::endl;
        }
    } while (!esCorrecta);
}

void Fecha::mostrar(){
    std::cout<<_Dia<< "/"<<_Mes << "/"<<_Anio<<std::endl;

}
