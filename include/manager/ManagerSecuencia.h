#pragma once
#include <iostream>
#include "archivo/ArchivoSecuencia.h"


class ManagerSecuencia{
    private:
        ArchivoSecuencia _repo;

    public:
        ManagerSecuencia();

        // Carga una nueva secuencia y la guarda en su respectivo archivo.
        // @return secuencia creada y guardada, o la secuencia asociada al objeto.
        Secuencia cargar(std::string objeto);
        bool eliminar(Secuencia secuencia);
        bool actualizar(Secuencia secuencia);
        // Devuelve el próximo ID disponible para una secuencia.
        // @return 0 si la secuencia no existe.
        int getNuevoID(Secuencia secuencia);

        ArchivoSecuencia getRepositorio();
};
