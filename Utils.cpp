#include "utils.h"
#include <iostream>

void cargarCadena(char *palabra, int tamano){
    int i=0;

    for(i=0; i<tamano; i++){
        palabra[i]=std::cin.get();
        if(palabra[i]=='\n'){
            break;
        }
    }

    palabra[i]='\0';
}
