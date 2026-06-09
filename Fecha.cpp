#include <iostream>
#include "Fecha.h"
#include <cstdlib>
#include <locale>

Fecha::Fecha() {
    _Dia = 0 ;
    _Mes = 0 ;
    _Anio = 0;
}

void Fecha::cargar() {
    
      setlocale(LC_ALL, "spanish");
      
    int dia,mes,anio;
    bool fechaCorrecta = false;
    do {
        std::cout << "Ingrese el día: ";
        std::cin >> dia;
        set_Dia(dia);

        std::cout << "Ingrese el mes: ";
        std::cin >> mes;
        set_Mes(mes);

        std::cout << "Ingrese el año: ";
        std::cin >> anio;
        set_Anio(anio);

        if (esValida()) {
            fechaCorrecta = true;
        } else {
            std::cout << "\n ERROR: La fecha ingresada es invalida. Intente nuevamente.\n" << std::endl;
        }

    } while (!fechaCorrecta); /// Si no es false, termina el Do While - Leandro
}


void Fecha::mostrar(){
    std::cout<<_Dia<< "/"<<_Mes << "/"<<_Anio<<std::endl;

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

void Fecha::set_Dia( int dia){
    if (dia > 0 && dia <=31 ){

        _Dia = dia;
    }
}

void Fecha::set_Mes(int mes ){
    if (mes > 0 && mes < 13){

        _Mes = mes;
    }
}

void Fecha::set_Anio(int anio ){
    _Anio = anio;
}

///Nos sirve para validar los dias, meses y años. -Leandro
bool Fecha::esValida() {
    if (_Anio <= 0 || _Mes < 1 || _Mes > 12) {
        return false;
    }

    ///Le asignamos los dias a los Doce meses del año - Leandro
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    ///Consultar al profe si quiere validación por año biciesto - Leandro

    ///Recordar poner -1 dado que si el usuario ingresa enero, mostrara febrero.
    if (_Dia < 1 || _Dia > diasPorMes[_Mes - 1]) {
        return false;
    }

    return true;
}
