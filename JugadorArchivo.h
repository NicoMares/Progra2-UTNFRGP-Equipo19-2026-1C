#pragma once

class JugadorArchivo
{
public:
    bool grabarEnDisco();
    bool leerDeDisco(int posicion); 
    void ConsultarPorDNI();
    void consultarPorPosicion();
    void TodosJugadores();
    void listarPorClub();
    void ListarDni();
    void EliminarJugador();
    bool modificarEnDisco(int posicion);

private:

};

