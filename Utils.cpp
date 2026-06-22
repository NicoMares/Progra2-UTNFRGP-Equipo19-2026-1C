#include "utils.h"
#include <iostream>

bool soloLetras(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

bool soloLetrasYNumeros(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ')) {
            return false;
        }
    }
    return true;
}

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
