#include "menu/consultas/ConsultasAnalisis.h"
#include <iostream>

#include "Turno.h"
#include "Protocolo.h"

#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerObraSocial.h"
#include "utils/funcFrontend.h"
#include "utils/rlutil.h"


ConsultasAnalisis::ConsultasAnalisis(): Menu(3, "Menu Consultas"){
    std::string opciones[3] = {
        "Busqueda por tipo",
        "Busqueda por paciente",
        "Busqueda por Obra Social"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ConsultasAnalisis::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerAnalisisProtocolo mAnalisisProtocolo;
    ManagerProtocolo mProtocolo;

    if (_opcionSeleccionada == 1) {busquedaxTipo();};
    if (_opcionSeleccionada == 2) {busquedaxPaciente();};
    if (_opcionSeleccionada == 3) {busquedaxObraSocial();};
}

void ConsultasAnalisis::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Consulta de pacientes\n";
    std::cout << "- Consulta de analisis\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "  Consulta de turnos\n";
    std::cout << "  Consulta de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}

void ConsultasAnalisis::busquedaxTipo() {
    ManagerTipoAnalisis mTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    ManagerProtocolo mProtocolo;
    mTipoAnalisis.mostrarTodos();
    int seleccion;

    while (true) {
        std::cout << "\nSeleccione el ID del tipo de analisis a buscar: ";
        std::cin >> seleccion;

        if (seleccion == 0) {
            return;
        }

        if (mTipoAnalisis.comprobar(seleccion)) {
            break;
        } else {
            continue;
        }
    }

    buscando();

    // BUSCAR Y CONTAR EL TIPO DE ANALISIS en AnalisisProtocolo

    const int CANTIDAD = mAnalisisProtocolo.getRepositorio().cantidadRegistros();
    AnalisisProtocolo* archivoAnalisisProtocolo = mAnalisisProtocolo.getRepositorio().leerTodos();
    bool* busquedaAnalisis = new bool[CANTIDAD]{};

    if (busquedaAnalisis == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    int cantidadEncontrados = 0;

    for (int i = 0; i < CANTIDAD; i++) {

        if (archivoAnalisisProtocolo[i].getEliminado()) {
            continue;
        }

        if (archivoAnalisisProtocolo[i].getIdTipoAnalisis()==seleccion){
            busquedaAnalisis[i] = true;
            cantidadEncontrados++;
        }
    }

    //SELECCIONAR LOS PROTOCOLOS mediante su id en AnalisisProtocolo

    Protocolo* protocolo = new Protocolo[cantidadEncontrados];
    if (protocolo == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }


    int idProtocolo = 0;
    int auxContador = 0;

    for (int i = 0; i < CANTIDAD; i++){

        if (busquedaAnalisis[i]) {
            idProtocolo = archivoAnalisisProtocolo[i].getIdProtocolo();
            protocolo[auxContador] = mProtocolo.seleccionar(idProtocolo);
            auxContador++;
        }
    }

    //MOSTRAR LOS PROTOCOLOS ENCONTRADOS

    if (cantidadEncontrados == 0) {
        std::cout << "\nNo se encontraron Protocolos con el Tipo de Analisis seleccionado\n\n";
    } else {
        std::cout << "BUSQUEDA X TIPO DE ANALISIS: Se encontraron los siguientes protocolos\n\n";
        rlutil::cls();
        mProtocolo.mostrarVarios(protocolo, cantidadEncontrados);
    }

    pausa();

    delete []archivoAnalisisProtocolo;
    delete []busquedaAnalisis;
    delete []protocolo;
}

void ConsultasAnalisis::busquedaxPaciente() {
    ManagerPaciente mPaciente;
    Paciente paciente;

    int dni = 0;

    std::cout << "Si conoce el DNI del paciente, ingreselo a continuacion (0 = listar todos | -1 = salir): ";
    std::cin >> dni;

    if (dni == 0) {
        // Mostrar todos los pacientes por pantalla
        mPaciente.mostrarTodos();

        while (true) {
            std::cout << "Ingrese el DNI del paciente, o 0 para cancelar: ";
            std::cin >> dni;

            if (dni == 0) {
                return;
            }

            paciente = mPaciente.seleccionar(dni);

            if (paciente.getDNI() != 0) {
                break;
            } else {
                std::cout << "El DNI ingresado no existe. Intente nuevamente\n";
                continue;
            }
        }
    }

    buscando();

    ///BUSCAR LOS TURNOS DEL PACIENTE
    ManagerTurno mTurno;

    const int CANTIDADTURNOS = mTurno.getRepositorio().cantidadRegistros();
    Turno* archivoTurnos = mTurno.getRepositorio().leerTodos();
    bool* pacienteEncontrado = new bool[CANTIDADTURNOS]{};
    int cantidadEncontrados = 0;

    if (pacienteEncontrado == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    for (int i = 0; i < CANTIDADTURNOS; i++) {
        if (archivoTurnos[i].getEliminado()) {
            continue;
        }

        if (archivoTurnos[i].getDniPaciente()==dni) {
            pacienteEncontrado[i] = true;
            cantidadEncontrados++;
        }
    }

    //SELECCIONAR LOS TURNOS ENCONTRADOS DEL PACIENTE

    Turno* turnoEncontrado = new Turno[cantidadEncontrados];
    int indiceAux = 0;
    int idTurno = 0;

    if (turnoEncontrado == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    for (int i = 0; i < CANTIDADTURNOS; i++) {
        if (archivoTurnos[i].getEliminado()) {
            continue;
        }

        if (pacienteEncontrado[i]) {
            idTurno = archivoTurnos[i].getID();
            turnoEncontrado[indiceAux] = mTurno.seleccionar(idTurno);
            indiceAux++;
        }
    }

    //SELECCIONAR LOS PROTOCOLOS mediante los turnos encontrados.

    ManagerProtocolo mProtocolo;
    Protocolo* protocoloEncontrado = new Protocolo[cantidadEncontrados];
    idTurno = 0;

    if (protocoloEncontrado == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    for (int i = 0; i < cantidadEncontrados; i++) {
        idTurno = turnoEncontrado[i].getID();
        protocoloEncontrado[i] = mProtocolo.seleccionarxTurno(idTurno);
    }

    //MOSTRAR LOS PROTOCOLOS ENCONTRADOS

    if (cantidadEncontrados == 0) {
        std::cout << "\nNo se encontraron Protocolos con el Paciente seleccionado\n\n";
    } else {
        rlutil::cls();
        std::cout << "BUSQUEDA X PACIENTE: Se encontraron los siguientes protocolos\n\n";
        mProtocolo.mostrarVarios(protocoloEncontrado, cantidadEncontrados);
    }

    pausa();

    delete []archivoTurnos;
    delete []pacienteEncontrado;
    delete []protocoloEncontrado;
}

void ConsultasAnalisis::busquedaxObraSocial() {
    ManagerObraSocial mObraSocial;
    int idObraSocial = 0;
    std::string nombreObraSocial;

    mObraSocial.mostrarTodos(true); // Mostrar lista ID - Nombre

    std::cout << "\nIngrese el ID de la Obra Social: ";
    std::cin >> idObraSocial;

    if (mObraSocial.getRepositorio().getPos(idObraSocial) == -1) {
        std::cout << "ID de Obra Social no valido.\n";
        std::cin.get();
        return;
    }

    nombreObraSocial = mObraSocial.getRepositorio().leer(idObraSocial-1).getNombre();

    ///BUSCAR PACIENTES DE LA OBRA SOCIAL SELECCIONADA

    ManagerPaciente mPaciente;
    int cantidadPacientes = mPaciente.getRepositorio().cantidadRegistros();
    Paciente *archivoPacientes = mPaciente.getRepositorio().leerTodos();

    bool* listarPacientes = new bool[cantidadPacientes]{};
    int contadorPacientes = 0;

    if (archivoPacientes == nullptr && cantidadPacientes > 0) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    if (listarPacientes == nullptr) {
        std::cout << "No hay suficiente memoria";
        exit(1000);
    }

    for (int i = 0; i < cantidadPacientes; i++) {
        if (archivoPacientes[i].getEliminado()) {
            continue;
        }
        if (archivoPacientes[i].getObraSocial().getID() == idObraSocial) {
            listarPacientes[i] = true;
            contadorPacientes++;
        }
    }

    int auxIndice = 0 ;
    Paciente* listadoPacientes = new Paciente[contadorPacientes]();

    for (int i = 0; i < cantidadPacientes; i++) {
        if (listarPacientes[i]) {
            listadoPacientes[auxIndice] = archivoPacientes[i];
            auxIndice++;
        }
    }

    delete []listarPacientes;

    ///BUSCAR LOS TURNOS DE LOS PACIENTES

    ManagerTurno mTurno;
    int cantidadTurnos = mTurno.getRepositorio().cantidadRegistros();
    Turno* archivoTurnos = mTurno.getRepositorio().leerTodos();
    bool* listarTurnos = new bool[cantidadTurnos]{};
    int contadorTurnos = 0;

    for (int i = 0; i < cantidadTurnos; i++) {
        if (archivoTurnos[i].getEliminado()) {
            continue;
        }
        for (int j = 0; j < cantidadPacientes; j++) {
            if (archivoTurnos[i].getDniPaciente() == listadoPacientes[j].getDNI()){
                listarTurnos[i] = true;
                contadorTurnos++;
            }
        }
    }

    Turno* listadoTurnos = new Turno[contadorTurnos]();
    auxIndice = 0 ;
    int idTurno = 0;

    for (int i = 0; i < cantidadTurnos; i++) {
        if (listarTurnos[i]) {
            listadoTurnos [auxIndice] = archivoTurnos[i];
            auxIndice++;
        }
    }

    delete []listarTurnos;

    // BUSCAR PROTOCOLOS DE LOS PACIENTES
    ManagerProtocolo mProtocolo;

    int cantidadProtocolos = mProtocolo.getRepositorio().cantidadRegistros();
    Protocolo* archivoProtocolo = mProtocolo.getRepositorio().leerTodos();
    bool* listarProtocolos = new bool[cantidadProtocolos]{};
    int contadorProtocolos = 0;

    for (int i = 0; i < cantidadProtocolos; i++) {
        if (archivoProtocolo[i].getEliminado() == true || archivoProtocolo[i].getEstado() != true) {
            continue;
        }
        for (int j = 0; j < contadorTurnos; j++) {
            if (archivoProtocolo[i].getIdTurno() == listadoTurnos[j].getID() ){
                listarProtocolos[i] = true;
                contadorProtocolos++;
            }
        }
    }

    Protocolo* listadoProtocolos = new Protocolo[contadorProtocolos]();
    auxIndice = 0 ;

    for (int i = 0; i < cantidadProtocolos; i++) {
        if (listarProtocolos[i]) {
            listadoProtocolos[auxIndice] = archivoProtocolo[i];
            auxIndice++;
        }
    }

    delete []listarProtocolos;

    ///CONTAR ANALISIS CON EL IDPROTOCOLO

    ManagerAnalisisProtocolo mAnalisisProtocolo;

    int cantidadAnalisisProtocolo = mAnalisisProtocolo.getRepositorio().cantidadRegistros();
    AnalisisProtocolo* archivoAnalisisProtocolo = mAnalisisProtocolo.getRepositorio().leerTodos();
    int contadorAnalisis = 0;

    for (int i = 0; i < cantidadAnalisisProtocolo; i++) {
        if (archivoAnalisisProtocolo[i].getEliminado()) {
            continue;
        }
        for (int j = 0; j < contadorProtocolos; j++) {
            if (archivoAnalisisProtocolo[i].getIdProtocolo() == listadoProtocolos->getId()) {
                contadorAnalisis++;
            }
        }
    }

    /// MOSTRAR RESULTADOS


    std::cout << "\nRESULTADOS: Analisis realizados con " << nombreObraSocial ;
    std::cout << "\n\n\tCANTIDAD DE ANALISIS: " << contadorAnalisis << std::endl;
    std::cout << "\tCANTIDAD DE PROTOCOLOS: " << contadorProtocolos << "\n" << std::endl;

    pausa();

    delete []listadoPacientes;
    delete []archivoPacientes;
    delete []archivoTurnos;


}