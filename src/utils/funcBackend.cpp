#include "utils/funcBackend.h"
#include "utils/funcFrontend.h"
#include "utils/rlutil.h"
#include "utils/Fecha.h"
#include "utils/Hora.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerSecuencia.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerPaciente.h"
#include "manager/ManagerObraSocial.h"
#include "manager/ManagerEnfermero.h"
#include "manager/ManagerAnalisisProtocolo.h"


void backup(){
    std::cout << "Realizando copia de seguridad en formato CSV\n";

    std::cout << "Turnos... ";
    ManagerTurno mTurno;
    mTurno.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    // PENDIENTE las demas clases

    std::cout << "Copia de seguridad realizada con exito!\n";
    std::cout << "El archivo encuentra en la carpeta de este mismo ejecutable.\n";
}


void restaurarBackup(){
    std::cout << "Restaurando copia de seguridad desde archivos CSV\n";
    
}


void paletaColores(){

}

