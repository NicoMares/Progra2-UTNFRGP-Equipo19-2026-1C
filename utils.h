#pragma once
#include <string>

void cargarCadena(char *palabra, int tamano);
bool soloLetras(const char* str);
bool soloLetrasYNumeros(const char* str);
bool buscarDNIEnSistema(int dni, std::string& nombre, std::string& apellido, std::string& tipo);

