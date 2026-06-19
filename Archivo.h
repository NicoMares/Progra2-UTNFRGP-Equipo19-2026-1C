#pragma once

#include <cstddef>

class Archivo
{
public:
    virtual ~Archivo();

protected:
    virtual const char* getNombreArchivo() const = 0;

    bool grabarRegistro(const void* registro, std::size_t tamanioRegistro) const;
    bool leerRegistro(void* registro, std::size_t tamanioRegistro, int posicion) const;
    bool modificarRegistro(const void* registro, std::size_t tamanioRegistro, int posicion) const;
    int contarRegistros(std::size_t tamanioRegistro) const;
    bool vaciarArchivo() const;
};
