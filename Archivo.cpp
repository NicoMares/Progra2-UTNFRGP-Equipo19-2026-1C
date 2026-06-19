#include "Archivo.h"

#include <cstdio>

Archivo::~Archivo()
{
}

bool Archivo::grabarRegistro(const void* registro, std::size_t tamanioRegistro) const
{
    FILE* pFile = fopen(getNombreArchivo(), "ab");
    if (pFile == NULL)
    {
        return false;
    }

    bool seEscribio = fwrite(registro, tamanioRegistro, 1, pFile) == 1;
    fclose(pFile);

    return seEscribio;
}

bool Archivo::leerRegistro(void* registro, std::size_t tamanioRegistro, int posicion) const
{
    FILE* pFile = fopen(getNombreArchivo(), "rb");
    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * tamanioRegistro, SEEK_SET);
    bool seLeyo = fread(registro, tamanioRegistro, 1, pFile) == 1;
    fclose(pFile);

    return seLeyo;
}

bool Archivo::modificarRegistro(const void* registro, std::size_t tamanioRegistro, int posicion) const
{
    FILE* pFile = fopen(getNombreArchivo(), "rb+");
    if (pFile == NULL)
    {
        return false;
    }

    fseek(pFile, posicion * tamanioRegistro, SEEK_SET);
    bool seEscribio = fwrite(registro, tamanioRegistro, 1, pFile) == 1;
    fclose(pFile);

    return seEscribio;
}

int Archivo::contarRegistros(std::size_t tamanioRegistro) const
{
    FILE* pFile = fopen(getNombreArchivo(), "rb");
    if (pFile == NULL)
    {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / tamanioRegistro;
}

bool Archivo::vaciarArchivo() const
{
    FILE* pFile = fopen(getNombreArchivo(), "wb");
    if (pFile == NULL)
    {
        return false;
    }

    fclose(pFile);
    return true;
}
