#include <iostream>
#include "Fecha.h"
#include <cstdlib>

Fecha::Fecha() {
    _Dia = 0 ;
    _Mes = 0 ;
    _Anio = 0;
}

void Fecha::cargar() {
    int dia,mes,anio;
    std::cout<< "ingrese el dia" <<std::endl;
    std::cin>>dia;
    set_Dia(dia);
    std::cout<< "ingrese el mes " <<std::endl;
    std::cin>>mes;
    set_Mes(mes);
    std::cout<< "ingrese el año "<< std::endl;
    std::cin>>anio;
    set_Anio(anio);
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

/*VER SI SE NECESITA MAS CONDICIONES PARA CARGAR*/
void Fecha::set_Dia( int dia){
    if (dia > 0 && dia <=31 ){

        _Dia = dia;
    }
    else {
        exit (-1);
    }
}

void Fecha::set_Mes(int mes ){
    if (mes > 0 && mes < 13){

        _Mes = mes;
    }
    else {
        exit (-1);
    }
}

void Fecha::set_Anio(int anio ){
    _Anio = anio;

}
