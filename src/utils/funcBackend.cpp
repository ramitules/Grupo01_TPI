#include "utils/funcBackend.h"
#include "utils/funcFrontend.h"
#include "utils/rlutil.h"
#include "utils/Fecha.h"
#include "utils/Hora.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerTipoAnalisis.h"
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
    /*
    std::cout << "Pacientes... ";
    ManagerPaciente mPacientes;
    mPacientes.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Protocolos... ";
    ManagerProtocolo mProto;
    mProto.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Tipos de analisis... ";
    ManagerTipoAnalisis mTipoAnalisis;
    mTipoAnalisis.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Obras sociales... ";
    ManagerObraSocial mOS;
    mOS.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Enfermeros... ";
    ManagerEnfermero mEnfermeros;
    mEnfermeros.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";
    
    std::cout << "Analisis por protocolos... ";
    ManagerAnalisisProtocolo mAP;
    mAP.exportarTodosCSV();
    rlutil::msleep(500);
    std::cout << "completado.\n";
    */
    std::cout << "Copia de seguridad realizada con exito!\n";
    std::cout << "El archivo encuentra en la carpeta de este mismo ejecutable.\n";
}


void restaurarBackup(){
    std::cout << "Restaurando copia de seguridad desde archivos CSV\n";
    
}


void paletaColores(){

}

