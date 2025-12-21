#pragma once
#include "../Menu.h"


class MenuInformes: public Menu {
    public:
        MenuInformes();

        void ejecutarOpcion() override;

    private:
        void informeFacturacionMensualPorObraSocial();
        void informeFacturacionMensualTotal();
        void informeAnalisisPorTipo();
        void informePacientesPorObraSocial();
        void informeAnalisisPorObraSocial();
};
