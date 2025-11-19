#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include "utils/funcBackend.h"
#include "utils/funcFrontend.h"
#include "utils/rlutil.h"
#include "csv/CSVTurno.h"
#include "csv/CSVTipoAnalisis.h"
#include "csv/CSVProtocolo.h"
#include "csv/CSVPaciente.h"
#include "csv/CSVObraSocial.h"
#include "csv/CSVEnfermero.h"
#include "csv/CSVAnalisisProtocolo.h"
#include "archivo/ArchivoTurno.h"
#include "archivo/ArchivoTipoAnalisis.h"
#include "archivo/ArchivoProtocolo.h"
#include "archivo/ArchivoPaciente.h"
#include "archivo/ArchivoObraSocial.h"
#include "archivo/ArchivoEnfermero.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "Turno.h"
#include "TipoAnalisis.h"
#include "Protocolo.h"
#include "Paciente.h"
#include "ObraSocial.h"
#include "Enfermero.h"
#include "AnalisisProtocolo.h"


void backup(){
    std::cout << "Realizando copia de seguridad en formato CSV\n";

    std::cout << "Turnos... ";
    CSVTurno csvTurno("backup_turnos.csv");
    csvTurno.guardarTodos();
    rlutil::msleep(500);  // Simula tiempo de procesamiento
    std::cout << "completado.\n";
    
    std::cout << "Pacientes... ";
    CSVPaciente csvPacientes("backup_pacientes.csv");
    csvPacientes.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Protocolos... ";
    CSVProtocolo csvProtocolo("backup_protocolos.csv");
    csvProtocolo.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Tipos de analisis... ";
    CSVTipoAnalisis csvTipoAnalisis("backup_tipos_analisis.csv");
    csvTipoAnalisis.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Obras sociales... ";
    CSVObraSocial csvObraSocial("backup_obras_sociales.csv");
    csvObraSocial.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";

    std::cout << "Enfermeros... ";
    CSVEnfermero csvEnfermero("backup_enfermeros.csv");
    csvEnfermero.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";
    
    std::cout << "Analisis por protocolos... ";
    CSVAnalisisProtocolo csvAnalisisProtocolo("backup_analisis_protocolos.csv");
    csvAnalisisProtocolo.guardarTodos();
    rlutil::msleep(500);
    std::cout << "completado.\n";
    
    std::cout << "Copia de seguridad realizada con exito!\n";
    std::cout << "El archivo encuentra en la carpeta de este mismo ejecutable.\n";
}


void restaurarBackup(){
    // Estructuras para metadatos de los archivos CSV
    struct stat stTurnos;
    int resTurno = stat("backup_turnos.csv", &stTurnos);
    struct stat stPacientes;
    int resPacientes = stat("backup_pacientes.csv", &stPacientes);
    struct stat stProtocolos;
    int resProtocolos = stat("backup_protocolos.csv", &stProtocolos);
    struct stat stTiposAnalisis;
    int resTiposAnalisis = stat("backup_tipos_analisis.csv", &stTiposAnalisis);
    struct stat stObraSocial;
    int resObraSocial = stat("backup_obras_sociales.csv", &stObraSocial);
    struct stat stEnfermeros;
    int resEnfermeros = stat("backup_enfermeros.csv", &stEnfermeros);
    struct stat stAP;
    int resAP = stat("backup_analisis_protocolos.csv", &stAP);

    // Calculo de fecha
    // Tambien se comprueba que exista al menos un archivo de backup
    std::tm* tm_local = nullptr;
    if (resTurno == 0) {
        tm_local = std::localtime(&stTurnos.st_mtime);
    } else if (resPacientes == 0) {
        tm_local = std::localtime(&stPacientes.st_mtime);
    } else if (resProtocolos == 0) {
        tm_local = std::localtime(&stProtocolos.st_mtime);
    } else if (resTiposAnalisis == 0) {
        tm_local = std::localtime(&stTiposAnalisis.st_mtime);
    } else if (resObraSocial == 0) {
        tm_local = std::localtime(&stObraSocial.st_mtime);
    } else if (resEnfermeros == 0) {
        tm_local = std::localtime(&stEnfermeros.st_mtime);
    } else if (resAP == 0) {
        tm_local = std::localtime(&stAP.st_mtime);
    } else {
        std::cout << "No se ha encontrado ninguna copia de seguridad. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return;
    }
    
    // Calculo de peso
    char peso = 'b';
    float tamTotal = 0.0f;
    if (resTurno == 0) {
        tamTotal += stTurnos.st_size;
    }
    if (resPacientes == 0) {
        tamTotal += stPacientes.st_size;
    }
    if (resProtocolos == 0) {
        tamTotal += stProtocolos.st_size;
    }
    if (resTiposAnalisis == 0) {
        tamTotal += stTiposAnalisis.st_size;
    }
    if (resObraSocial == 0) {
        tamTotal += stObraSocial.st_size;
    }
    if (resEnfermeros == 0) {
        tamTotal += stEnfermeros.st_size;
    }
    if (resAP == 0) {
        tamTotal += stAP.st_size;
    }
    // Conversion de unidades
    if (tamTotal > 1024) {
        // De bytes a kilobytes
        tamTotal /= 1024;
        peso = 'k';
    }
    if (tamTotal > 1024) {
        // De kilobytes a megabytes
        tamTotal /= 1024;
        peso = 'm';
    }
    
    std::cout << "Restaurar copia de seguridad\n";
    std::cout << separador();
    std::cout << "Se ha encontrado una copia de seguridad con los siguientes datos\n\n";
    std::cout << "Fecha de creacion: " << std::put_time(tm_local, "%d-%m-%Y") << '\n';
    std::cout << "Peso: " << tamTotal << peso << "b\n\n";
    
    CSVTurno csvTurno("backup_turnos.csv");
    std::cout << "Turnos: " << csvTurno.cantidadLineasDatos() << '\n';
    CSVPaciente csvPacientes("backup_pacientes.csv");
    std::cout << "Pacientes: " << csvPacientes.cantidadLineasDatos() << '\n';
    CSVProtocolo csvProtocolo("backup_protocolos.csv");
    std::cout << "Protocolos: " << csvProtocolo.cantidadLineasDatos() << '\n';
    CSVTipoAnalisis csvTipoAnalisis("backup_tipos_analisis.csv");
    std::cout << "Tipos de analisis: " << csvTipoAnalisis.cantidadLineasDatos() << '\n';
    CSVObraSocial csvObraSocial("backup_obras_sociales.csv");
    std::cout << "Obras sociales: " << csvObraSocial.cantidadLineasDatos() << '\n';
    CSVEnfermero csvEnfermero("backup_enfermeros.csv");
    std::cout << "Enfermeros: " << csvEnfermero.cantidadLineasDatos() << '\n';
    CSVAnalisisProtocolo csvAnalisisProtocolo("backup_analisis_protocolos.csv");
    std::cout << "Analisis por protocolos: " << csvAnalisisProtocolo.cantidadLineasDatos() << "\n\n";

    char opc = 'n';
    std::cout << "¿Desea restaurar esta copia de seguridad? (s/n): ";
    std::cin >> opc;
    if (opc == 'n') {
        return;
    }
    std::cout << separador();
    std::cout << "Restaurando copia de seguridad desde archivos CSV\n";
    
    std::cout << "Turnos... ";
    Turno* turnos = csvTurno.leerTodo();
    ArchivoTurno arTurnos;
    arTurnos.guardarVarios(turnos, csvTurno.cantidadLineasDatos());
    delete[] turnos;
    rlutil::msleep(500);  // Simula tiempo de procesamiento
    std::cout << csvTurno.cantidadLineasDatos() << " turnos restaurados.\n";
    
    std::cout << "Pacientes... ";
    Paciente* pacientes = csvPacientes.leerTodo();
    ArchivoPaciente arPacientes;
    arPacientes.guardarVarios(pacientes, csvPacientes.cantidadLineasDatos());
    delete[] pacientes;
    rlutil::msleep(500);
    std::cout << csvPacientes.cantidadLineasDatos() << " pacientes restaurados.\n";

    std::cout << "Protocolos... ";
    Protocolo* protocolos = csvProtocolo.leerTodo();
    ArchivoProtocolo arProtocolos;
    arProtocolos.guardarVarios(protocolos, csvProtocolo.cantidadLineasDatos());
    delete[] protocolos;
    rlutil::msleep(500);
    std::cout << csvProtocolo.cantidadLineasDatos() << " protocolos restaurados.\n";

    std::cout << "Tipos de analisis... ";
    TipoAnalisis* tiposAnalisis = csvTipoAnalisis.leerTodo();
    ArchivoTipoAnalisis arTiposAnalisis;
    arTiposAnalisis.guardarVarios(tiposAnalisis, csvTipoAnalisis.cantidadLineasDatos());
    delete[] tiposAnalisis;
    rlutil::msleep(500);
    std::cout << csvTipoAnalisis.cantidadLineasDatos() << " tipos de analisis restaurados.\n";

    std::cout << "Obras sociales... ";
    ObraSocial* obrasSociales = csvObraSocial.leerTodo();
    ArchivoObraSocial arObrasSociales;
    arObrasSociales.guardarVarios(obrasSociales, csvObraSocial.cantidadLineasDatos());
    delete[] obrasSociales;
    rlutil::msleep(500);
    std::cout << csvObraSocial.cantidadLineasDatos() << " obras sociales restauradas.\n";

    std::cout << "Enfermeros... ";
    Enfermero* enfermeros = csvEnfermero.leerTodo();
    ArchivoEnfermero arEnfermeros;
    arEnfermeros.guardarVarios(enfermeros, csvEnfermero.cantidadLineasDatos());
    delete[] enfermeros;
    rlutil::msleep(500);
    std::cout << csvEnfermero.cantidadLineasDatos() << " enfermeros restaurados.\n";
    
    std::cout << "Analisis por protocolos... ";
    AnalisisProtocolo* analisisProtocolos = csvAnalisisProtocolo.leerTodo();
    ArchivoAnalisisProtocolo arAnalisisProtocolos;
    arAnalisisProtocolos.guardarVarios(analisisProtocolos, csvAnalisisProtocolo.cantidadLineasDatos());
    delete[] analisisProtocolos;
    rlutil::msleep(500);
    std::cout << csvAnalisisProtocolo.cantidadLineasDatos() << " analisis por protocolos restaurados.\n";

    std::cout << "Restauracion completa. Presione ENTER para continuar.\n";
    rlutil::getkey();
}


void paletaColores(){
    std::cout << "Seleccione una variante de colores";
}
