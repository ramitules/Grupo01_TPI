#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "utils/ManagerInput.h"
#include "utils/rlutil.h"
#include "Protocolo.h"
#include "Turno.h"
#include "utils/funcFrontend.h"
#include "Paciente.h"
#include <algorithm>
#include <iomanip>

ManagerTurno::ManagerTurno(){};

bool ManagerTurno::comprobar(int idTurno) {
    Turno regTurno;
    int posTurno = _repo.getPos(idTurno);

    if (posTurno == -1) {
        std::cout << "\n\tATENCION: No existe el TURNO\n";
        return false;
    }

    regTurno = _repo.leer(idTurno-1);

    if (regTurno.getEliminado()) {
        std::cout << "\n\tATENCION: TURNO eliminado\n";
        return false;
    }

    return true;
}

Turno ManagerTurno::seleccionar(int idTurno) {

    int posicion = _repo.getPos(idTurno);
    Turno turno = _repo.leer(posicion);

    return turno;
}

void ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ManagerPaciente mPaciente;
    ManagerFecha mFecha;
    ManagerHora mHora;
    ManagerInput mInput;
    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    int proximoID = _repo.cantidadRegistros() + 1;
    int dniPaciente;
    float importe = 0.0f;
    bool pacienteExiste = false;
    Fecha fechaAtencion;
    Hora horaAtencion;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI

    std::cout << "Menu Turno\n==============================\n";
    std::cout << "Ingrese el DNI del paciente (0 - listar todos):\n\n";

    dniPaciente = mInput.ingresarDni();

    if (dniPaciente == 0) {
        rlutil::cls();
        std::cout << "Menu Turno\n==============================\n\n";
        mPaciente.mostrarTodos();
        std::cout << std::endl;
    }

    dniPaciente = mInput.ingresarDni();

    if (dniPaciente == 0) {
        menuVolver();
        return;
    }

    ///COMPROBAR DNI: Si no existe se da la posibilidad de cargar;

    pacienteExiste = mPaciente.comprobar(dniPaciente);

    Paciente paciente;

    if (pacienteExiste) {
        paciente = mPaciente.seleccionar(dniPaciente);
    } else {
        std::cout << "Paciente inexistente. Desea cargar sus datos ahora? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            if (!mPaciente.cargar(dniPaciente)) {
                std::cout << "No se pudo cargar el paciente. El turno no sera guardado.\n";
                std::cout << "Presione ENTER para continuar\n";
                std::cin.get();
                return;
            }
        } else {
            menuVolver();
        }
    }

    rlutil::cls();
    std::cout << "Menu Turno\n==============================\n";
    std::cout << "\nPaciente " << paciente.getNombre() << " " << paciente.getApellido() << std::endl;

    while (true) {
        std::cout << "\nSe atendera ahora? s/n: ";
        std::cin >> opc;

        Fecha fechaAtencion;
        Hora horaAtencion;

        if (opc == 's') {
            break;
        } else if (opc == 'n') {
            std::cout << std::endl;

            std::cout << "INGRESE la fecha de atención\n";

            while (true) {
                fechaAtencion = mFecha.cargar();
                Fecha actual;
                if (fechaAtencion < actual) {
                    std::cout << "\n\tATENCION: Ingrese una fecha actual \n" << std::endl;
                    continue;
                }
                break;
            }
            horaAtencion = mHora.cargar();
            break;
        }
    }

    // GUARDAR EL TURNO

    Turno turno(proximoID, dniPaciente, fechaAtencion, horaAtencion);

    if (_repo.guardar(turno)) {
        rlutil::cls();
        std::cout << "\nCONFIRMADO: Turno guardado con el ID " << turno.getID() ;
        std::cout << std::endl;
        mostrarUno(turno);
    } else {
        std::cout << "\nOcurrio un error al intentar guardar el turno. ";
        std::cin.get();
        return;
    }

    while (true) {
        std::cout << "\nDesea iniciar el PROTOCOLO ahora? (s/n) ";
        std::cin >> opc;

        if (opc != 's' && opc != 'n') {
            std::cout << "\tIngrese una opción valida: \n";
            continue;
        } else {
            break;
        }
    }

    if (opc == 'n') {
        return;
    }

    //PASO INICIAR EL PROTOCOLO y CARGAR ESTUDIOS

    Protocolo protocolo;
    protocolo.setIdTurno(proximoID);

    if (mProtocolo.iniciar(protocolo)) {
        std::cout << "\nPROTOCOLO INICIADO. \n" << std::endl;
        mProtocolo.mostrar(protocolo);
        std::cout << std::endl;
        pausa();
    } else {
        std::cout << "\nPROTOCOLO CANCELADO.";
        return;
    }

    if (mProtocolo.cargarAnalisis(protocolo)) {
        pausa();
        rlutil::cls();
        std::cout << "\nATENCION: Los estudios se han cargardo al PROTOCOLO\n";
        mProtocolo.mostrar(protocolo);
    } else {
        std::cout << "\nERROR: los estudios no se ha cargado al PROTOCOLO\n";
        pausa();
        return;
    }

    // PASO ASIGNAR PROTOCOLO: Solo si la fecha es la del dia.

    Fecha fechaActual;

    if (fechaAtencion == fechaActual) {
        while (true) {
            std::cout << "\nCONSULTA: Desea asignar el PROTOCOLO ahora? (s/n) ";
            std::cin >> opc;

            if (opc != 's' && opc != 'n') {
                std::cout << "\tIngrese una opcion valida: \n";
                continue;
            }
            break;
        }

        if (opc == 'n') {
            return;
        }
    }
    else {
        return;
    }

}

std::string ManagerTurno::mostrarCabecera(const int anchoPaciente, const int anchoFecha, const int anchoImporte, const int anchoObraSocial, const int anchoEstado) {
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(5, '-') + 
                        "+" + std::string(anchoPaciente + 2, '-') + 
                        "+" + std::string(anchoFecha + 2, '-') + 
                        "+" + std::string(15, '-') +
                        "+" + std::string(anchoImporte + 2, '-') +
                        "+" + std::string(anchoObraSocial + 1, '-') +
                        "+" + std::string(anchoEstado + 2, '-') + "+\n";

    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(3) << "ID" << " | " 
              << std::setw(anchoPaciente) << "Paciente" << " | "
              << std::setw(anchoFecha) << "Fecha atencion" << " | "
              << std::setw(13) << "Hora atencion" << " | "
              << std::setw(anchoImporte) << "Importe" << " | "
              << std::setw(anchoImporte) << "Obra Social" << "   |"
              << std::setw(anchoImporte) << " Estado " << "     |\n";

    std::cout << linea;

    return linea;
}

void ManagerTurno::mostrarUno(Turno turno){
    ManagerFecha mFecha;
    ManagerHora mHora;
    
    // -- Calcular ancho maximo --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 7;  // Largo minimo "Importe"
    int anchoObraSocial = 14;
    int anchoEstado = 10;
    std::string nombreCompleto;
    std::string precioStr;
    std::string nombreObraSocial;
    std::string estado;

    nombreCompleto = turno.getPaciente().getNombre();
    nombreCompleto += " ";
    nombreCompleto += turno.getPaciente().getApellido();
    nombreObraSocial = turno.getPaciente().getObraSocial().getNombre();

    anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
    anchoFecha = std::max(anchoFecha, (int)turno.getFechaAtencion().to_str().length());
    precioStr = std::to_string((int)turno.getImporte()) + ".00";
    anchoImporte = std::max(anchoImporte, (int)precioStr.length());
    anchoObraSocial = std::max(anchoObraSocial, (int)nombreObraSocial.length());

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte, anchoObraSocial, anchoEstado);

    std::cout << "| " << std::setw(3) << turno.getID() << " | " 
              << std::setw(anchoPaciente) << nombreCompleto << " | "
              << std::setw(anchoFecha) << turno.getFechaAtencion().to_str() << " | "
              << std::setw(13) << turno.getHoraAtencion().to_str() << " | "
              << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turno.getImporte() << " |\n";
    std::cout << linea;
}

void ManagerTurno::mostrarVarios(Turno* turnos, const int cantidad) {
    if (cantidad == 0) {
        std::cout << "No hay turnos para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 11;  // Largo minimo "Importe"
    int anchoObraSocial = 14;
    int anchoEstado = 10;
    std::string nombreCompleto;
    std::string precioStr;
    std::string nombreObraSocial;
    std::string estado;

    for(int i=0; i<cantidad; i++) {
        if (turnos[i].getEliminado()) {
            continue;
        }
        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();
        nombreObraSocial = turnos[i].getPaciente().getObraSocial().getNombre();

        ManagerProtocolo mProtocolo;
        Protocolo protocolo = mProtocolo.seleccionarxTurno(turnos[i].getID());
        bool estadoProtocolo = protocolo.getEstado();
        std::string estado = "";

        estado = (estadoProtocolo) ? "Finalizado" : "Pendiente";

        anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
        anchoFecha = std::max(anchoFecha, (int)turnos[i].getFechaAtencion().to_str().length());
        precioStr = std::to_string((int)turnos[i].getImporte()) + ".00";
        anchoImporte = std::max(anchoImporte, (int)precioStr.length());
        anchoObraSocial = std::max(anchoObraSocial, (int)nombreObraSocial.length());
        anchoEstado = std::max(anchoObraSocial, (int)estado.length());
    }

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte, anchoObraSocial, anchoEstado);

    // Datos
    for(int i=0; i<cantidad; i++){
        if (turnos[i].getEliminado()) {
            continue;
        }

        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();
        nombreObraSocial = turnos[i].getPaciente().getObraSocial().getNombre();

        ManagerProtocolo mProtocolo;
        Protocolo protocolo = mProtocolo.seleccionarxTurno(turnos[i].getID());
        bool estadoProtocolo = protocolo.getEstado();
        estado = (estadoProtocolo) ? "Finalizado" : "Pendiente";
        
        std::cout << "| " << std::setw(3) << turnos[i].getID() << " | " 
                  << std::setw(anchoPaciente) << nombreCompleto << " | "
                  << std::setw(anchoFecha) << turnos[i].getFechaAtencion().to_str() << " | "
                  << std::setw(13) << turnos[i].getHoraAtencion().to_str() << " | "
                  << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turnos[i].getImporte() << " |"
                  << std::setw(anchoObraSocial) << nombreObraSocial << " | "
                  << std::setw(anchoEstado) << estado << " |\n";
    }

    std::cout << linea;
}

void ManagerTurno::mostrarTodos(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Turno* todos = _repo.leerTodos();
    
    mostrarVarios(todos, CANTIDAD);
    delete[] todos;
}

void ManagerTurno::ordenadosFecha(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Turno *turnos = _repo.leerTodos();
    Turno aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (turnos[i].getEliminado()) {

            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (turnos[i].getFechaAtencion() > turnos[j].getFechaAtencion()) {
                aux = turnos[i];
                turnos[i] = turnos[j];
                turnos[j] = aux;
            } else if (turnos[i].getFechaAtencion() == turnos[j].getFechaAtencion()) {
                // Corroborar hora si la fecha es la misma
                if (turnos[i].getHoraAtencion() > turnos[j].getHoraAtencion()) {
                    aux = turnos[i];
                    turnos[i] = turnos[j];
                    turnos[j] = aux;
                }
            }
        }
    }

    // Mostrar
    mostrarVarios(turnos, CANTIDAD);
    std::cout << "Presione ENTER para continuar";
    std::cin.get();

    // Finalizar
    delete[] turnos;
    std::cout << "Presione ENTER para continuar";
    std::cin.get();
}

void ManagerTurno::agrupadosPaciente(){
    const int CANTIDAD = _repo.cantidadRegistros();
    bool* indicesVisitados = new bool[CANTIDAD] {false};
    bool* indicesPacientes = new bool[CANTIDAD] {false};
    Turno *turnos = _repo.leerTodos();
    Paciente auxPaciente;

    int totalPacientes = 0;
    int iAux = 0;
    for (int i=0; i<CANTIDAD; i++) {
        if (indicesVisitados[i]) {      // Saltear turnos ya mostrados
            continue;
        }

        if (turnos[i].getEliminado()) { // y eliminados
            indicesVisitados[i] = true;
            continue;
        }

        auxPaciente = turnos[i].getPaciente();
        std::cout << "-- Turnos del paciente " << auxPaciente.getNombre() << ' ' << auxPaciente.getApellido() << " --\n";
       
        for (int j=0; j<CANTIDAD; j++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            if (indicesVisitados[j]) {
                continue;
            }

            if (turnos[j].getDniPaciente() == auxPaciente.getDNI()) {
                totalPacientes += 1;
                indicesVisitados[j] = true;
                indicesPacientes[j] = true;
            }
        }

        Turno *turnosPaciente = new Turno[totalPacientes];

        for (int j = 0; j < CANTIDAD; j ++) {
            if (indicesPacientes[j]) {
                turnosPaciente[iAux] = turnos[j];
                iAux ++;
            }
        }

        mostrarVarios(turnosPaciente, totalPacientes);
        std::cout << "\n\n";

        std::cout << "Presione ENTER para continuar";
        std::cin.get();

        // Reiniciar variables
        totalPacientes = 0;
        iAux = 0;
        for (int j = 0; j < CANTIDAD; j ++) { indicesPacientes[j] = false; }
        delete[] turnosPaciente;
    }



    delete[] turnos;
    delete[] indicesVisitados;
    delete[] indicesPacientes;


}

void ManagerTurno::busquedaFecha(){
    std::cin.ignore(100, '\n');

    const int CANTIDAD = _repo.cantidadRegistros();
    bool* indicesVisitados = new bool[CANTIDAD] {false};
    Turno *turnos = _repo.leerTodos();

    ManagerFecha mFecha;
    int dias = 0;

    std::cout << "-- Ingreso de rango de fechas --\n\n";
    std::cout << "DESDE\n";
    Fecha desde = mFecha.cargar();
    
    while (true) {
        std::cout << "Cantidad de dias (1 = solo la fecha ingresada): ";
        std::cin >> dias;

        if (dias > 0 && dias < 366) {
            break;
        }

        if (dias > 365) {
            std::cout << "No se permiten busquedas superiores a 365 dias. Intente nuevamente\n";
        }

        if (dias < 1) {
            std::cout << "No se permiten dias negativos. Intente nuevamente\n";
        }
    }

    buscando();
    
    bool* indicesTurnos = new bool[CANTIDAD] {false};
    int totalTurnos = 0, iAux = 0;

    if (dias == 1) {  // Una fecha determinada
        // Filtrar
        for (int i=0; i<CANTIDAD; i++) {
            if (turnos[i].getEliminado()) {
                continue;
            }

            if (turnos[i].getFechaAtencion() == desde) {
                indicesTurnos[i] = true;
                totalTurnos ++;
            }
        }
        // Mostrar
        if (totalTurnos > 0) {
            std::cout << "-- Se encontraron los siguientes turnos en la fecha provista --\n";
            Turno *turnosFecha = new Turno[totalTurnos];

            for (int j = 0; j < CANTIDAD; j ++) {
                if (indicesTurnos[j]) {
                    turnosFecha[iAux] = turnos[j];
                    iAux ++;
                }
            }

            mostrarVarios(turnosFecha, totalTurnos);
            std::cout << "\n\n";
            delete[] turnosFecha;
        } else {
            std::cout << "No se han encontrado turnos en la fecha provista.\n";
        }
    } else {  // Un rango de fechas
        Fecha* fechasElegidas = mFecha.rangoFechas(desde, dias);
        // Filtrar
        for (int i=0; i<CANTIDAD; i++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            
            for (int j=0; j<dias; j++) {
                if (turnos[i].getFechaAtencion() == fechasElegidas[j]) {
                    indicesTurnos[i] = true;
                    totalTurnos ++;
                }
            }
        }
        // Mostrar
        if (totalTurnos > 0) {
            std::cout << "-- Se encontraron los siguientes turnos en el rango de fechas --\n";
            Turno *turnosFecha = new Turno[totalTurnos];

            for (int j = 0; j < CANTIDAD; j ++) {
                if (indicesTurnos[j]) {
                    turnosFecha[iAux] = turnos[j];
                    iAux ++;
                }
            }

            mostrarVarios(turnosFecha, totalTurnos);
            std::cout << "\n\n";
            delete[] turnosFecha;
        } else {
            std::cout << "No se han encontrado turnos en el rango de fechas.\n";
        }

        delete[] fechasElegidas;
    }
    delete[] turnos;
    delete[] indicesVisitados;
    delete[] indicesTurnos;

    std::cout << "Presione ENTER para continuar";
    std::cin.get();
}

void ManagerTurno::busquedaPaciente(){
    std::cin.ignore(100, '\n');

    const int CANTIDAD = _repo.cantidadRegistros();

    bool* indices = new bool[CANTIDAD];
    for (int i = 0; i < CANTIDAD; i ++) { indices[i] = false; }

    Turno *turnos = _repo.leerTodos();
    ManagerPaciente mPaciente;
    
    // Busqueda personalizada por DNI o por nombre
    int opc = 0;

    std::cout << "Como desea buscar el paciente?\n";
    std::cout << "1. Por DNI\n";
    std::cout << "2. Por nombre completo\n";

    do{
        std::cout << "Opcion: ";
        std::cin >> opc;
    } while (opc != 1 && opc != 2);

    std::cin.ignore(100, '\n');

    int totalTurnos = 0, iAux = 0;
    // Busqueda por DNI
    if (opc == 1) {
        
        int dni = 0;

        std::cout << "Ingrese el DNI del paciente: ";
        std::cin >> dni;

        buscando();

        for (int i = 0; i < CANTIDAD; i ++) {
            if (turnos[i].getEliminado()) {
                continue;
            }
            if (turnos[i].getDniPaciente() == dni) {
                indices[i] = true;
                totalTurnos ++;
            }
        }
    }
    // Busqueda por nombre completo
    if (opc == 2) {
        std::string nombreCompleto;
        std::string nombreIngresado;
        Paciente auxPaciente;
        
        std::cout << "Ingrese el nombre y apellido del paciente, separados por espacio: ";
        std::getline(std::cin, nombreIngresado);

        buscando();
        
        for (int i = 0; i < CANTIDAD; i ++) {
            if (turnos[i].getEliminado()) {
                continue;
            }

            auxPaciente = turnos[i].getPaciente();

            nombreCompleto = "";
            nombreCompleto.append(auxPaciente.getNombre());
            nombreCompleto.append(" ");
            nombreCompleto.append(auxPaciente.getApellido());

            if (nombreCompleto.compare(nombreIngresado) == 0) {
                indices[i] = true;
                totalTurnos ++;
            }
        }
    }

    // Mostrar
    if (totalTurnos > 0) {
        std::cout << "-- Se encontraron los siguientes turnos para el paciente seleccionado --\n";
        Turno *turnosPaciente = new Turno[totalTurnos];

        for (int i = 0; i < CANTIDAD; i ++) {
            if (indices[i]) {
                turnosPaciente[iAux] = turnos[i];
                iAux ++;
            }
        }

        mostrarVarios(turnosPaciente, totalTurnos);
        pausa();
        std::cout << "\n\n";
        delete[] turnosPaciente;
    } else {
        std::cout << "No se ha encontrado el paciente en la base de datos de turnos\n";
    }

    std::cout << "Presione ENTER para continuar";
    std::cin.get();

    delete[] turnos;
    delete[] indices;
}

void ManagerTurno::actualizarImportes(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Turno* turnos = _repo.leerTodos();
    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAP;

    Protocolo auxProto;

    for (int i = 0; i < CANTIDAD; i ++) {
        if (turnos[i].getEliminado()) {
            continue;
        }

        float nuevoImporte = 0.0f;

        for (int j = 0; j < mProtocolo.getRepositorio().cantidadRegistros(); j ++) {
            auxProto = mProtocolo.getRepositorio().leer(j);
            
            if (auxProto.getIdTurno() == turnos[i].getID()) {
                for (int k = 0; k < mAP.getRepositorio().cantidadRegistros(); k ++) {
                    if (mAP.getRepositorio().leer(k).getIdProtocolo() == auxProto.getId()){
                        nuevoImporte += mAP.getRepositorio().leer(k).getTipoAnalisis().getPrecio();
                    }
                }
            }
        }

        turnos[i].setImporte(nuevoImporte);
        _repo.modificar(turnos[i], _repo.getPos(turnos[i].getID()));
    }

    delete[] turnos;
}

/*
void ManagerTurno::actualizarImportesSeleccionados() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Turno* turnos = _repo.leerTodos();
    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAP;
    Fecha hoy; // Fecha actual por defecto

    // 1. Filtrar turnos candidatos
    bool* candidatos = new bool[CANTIDAD] {false};
    int totalCandidatos = 0;

    for (int i = 0; i < CANTIDAD; i++) {
        if (turnos[i].getEliminado()) continue;

        // Verificar fecha futura
        if (turnos[i].getFechaAtencion() > hoy || turnos[i].getFechaAtencion() == hoy) {
            // Verificar protocolo no terminado (estado = false)
            int idProtocolo = mProtocolo.seleccionar(turnos[i].getID());

            if (idProtocolo != -1) {
                Protocolo proto = mProtocolo.seleccionar(idProtocolo);
                if (!proto.getEstado()) {
                    candidatos[i] = true;
                    totalCandidatos++;
                }
            }
        }
    }

    if (totalCandidatos == 0) {
        std::cout << "No hay turnos pendientes de actualizacion (fecha futura y protocolo abierto).\n";
        delete[] turnos;
        delete[] candidatos;
        std::cout << "Presione ENTER para continuar";
        std::cin.get();
        return;
    }

    // 2. Mostrar candidatos
    std::cout << "Turnos disponibles para actualizar importes:\n";
    Turno* turnosMostrar = new Turno[totalCandidatos];
    int idx = 0;
    for (int i = 0; i < CANTIDAD; i++) {
        if (candidatos[i]) {
            turnosMostrar[idx++] = turnos[i];
        }
    }
    mostrarVarios(turnosMostrar, totalCandidatos);
    delete[] turnosMostrar;

    // 3. Pedir seleccion al usuario
    std::cout << "\nIngrese los ID de los turnos a actualizar, separados por coma (ej: 1, 3, 5): ";
    std::string input;
    std::getline(std::cin, input); // Usar getline para leer toda la linea

    // 4. Parsear y validar input
    std::string idStr;
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == ',') {
            if (!idStr.empty()) {
                int id = std::stoi(idStr);
                // Buscar el turno con ese ID y actualizarlo si es candidato
                bool encontrado = false;

                for (int j = 0; j < CANTIDAD; j++) {
                    if (turnos[j].getID() == id && candidatos[j]) {
                        // Actualizar importe
                        float nuevoImporte = 0.0f;
                        int idProto = mProtocolo.buscarTurno(id);
                        // Recalcular importe
                         for (int k = 0; k < mAP.getRepositorio().cantidadRegistros(); k ++) {
                            if (mAP.getRepositorio().leer(k).getIdProtocolo() == idProto){
                                nuevoImporte += mAP.getRepositorio().leer(k).getTipoAnalisis().getPrecio();
                            }
                        }

                        turnos[j].setImporte(nuevoImporte);
                        _repo.modificar(turnos[j], _repo.getPos(id));
                        
                        std::cout << "Turno ID " << id << " actualizado. Nuevo importe: $" << nuevoImporte << "\n";
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "ID " << id << " no valido o no corresponde a un turno actualizable.\n";
                }
                idStr = "";
            }
        } else if (isdigit(input[i])) {
            idStr += input[i];
        }
    }
    // Procesar el ultimo ID si existe
    if (!idStr.empty()) {
        int id = std::stoi(idStr);
        bool encontrado = false;
        
        for (int j = 0; j < CANTIDAD; j++) {
            if (turnos[j].getID() == id && candidatos[j]) {
                 // Actualizar importe
                float nuevoImporte = 0.0f;
                int idProto = mProtocolo.buscarTurno(id);

                for (int k = 0; k < mAP.getRepositorio().cantidadRegistros(); k ++) {
                    if (mAP.getRepositorio().leer(k).getIdProtocolo() == idProto){
                        nuevoImporte += mAP.getRepositorio().leer(k).getTipoAnalisis().getPrecio();
                    }
                }

                turnos[j].setImporte(nuevoImporte);
                _repo.modificar(turnos[j], _repo.getPos(id));

                std::cout << "Turno ID " << id << " actualizado. Nuevo importe: $" << nuevoImporte << "\n";
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
             std::cout << "ID " << id << " no valido o no corresponde a un turno actualizable.\n";
        }
    }

    delete[] turnos;
    delete[] candidatos;
    std::cout << "Operacion finalizada. Presione ENTER para continuar";
    std::cin.get();
}

*/

bool ManagerTurno::actualizar(Turno turno){
    std::cin.ignore(100, '\n');

    ManagerFecha mFecha;
    ManagerHora mHora;

    int dniPaciente;
    float importe = 0.0;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI
    while (true) {
        std::cout << "Ingrese el DNI del paciente (0 para dejarlo como estaba): ";
        std::cin >> dniPaciente;

        if (dniPaciente == 0) {
            dniPaciente = turno.getDniPaciente();
            break;
        }

        if (dniPaciente >= 1000000 && dniPaciente <= 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos (1M - 100M).\n";
    }

    turno.setDniPaciente(dniPaciente);

    std::cin.ignore(100, '\n');

    std::cout << "La fecha sera la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cin.ignore(2, '\n');
        turno.setFechaAtencion(mFecha.cargar());
    }
    
    std::cout << "La hora sera la misma? s/n: ";
    std::cin >> opc;
    
    if (opc != 's') {
        std::cin.ignore(2, '\n');
        turno.setHoraAtencion(mHora.cargar());
    }

    if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
        std::cout << "El turno se ha modificado correctamente. Presione ENTER para continuar.\n";
        std::cin.get();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el turno. Presione ENTER para continuar.\n";
    std::cin.get();
    return false;
}

bool ManagerTurno::actualizarImporte(AnalisisProtocolo analisisProtocolo) {

    int idProtocolo = analisisProtocolo.getIdProtocolo();

    //Selecciono el protocolo correspondiente

    ManagerProtocolo mProtocolo;
    Protocolo protocolo = mProtocolo.seleccionar(idProtocolo);

    //Selecciono el turno del protocolo

    ManagerTurno mTurno;
    int idTurno = protocolo.getIdTurno();
    Turno turno = mTurno.seleccionar(protocolo.getIdTurno());
    int posicionTurno = mTurno.getRepositorio().getPos(idTurno);

    //Selecciono el paciente del turno y tomo la cobertura de obra social (no hace falta la cobertura)

    ManagerPaciente mPaciente;
    Paciente paciente = mPaciente.seleccionar(turno.getDniPaciente());
    int cobertura = paciente.getObraSocial().getCobertura();

    //Modifico el importe del protocolo en el turno

    int precioAnalisis = analisisProtocolo.getPrecioSolicitud();
    int importeModificado = turno.getImporte() + precioAnalisis ;
    turno.setImporte(importeModificado);

    //Guardo el turno en archivo

    if (mTurno.getRepositorio().modificar(turno, posicionTurno)) {
        return true;
    }
    else {
        return false;
    }
}

bool ManagerTurno::eliminar(Turno turno) {
    char opc;

    std::cout << "Seguro que desea eliminar el turno? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        // ELIMINACION LOGICA
        turno.setEliminado(true);
        if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
            std::cout << "El turno se ha eliminado correctamente. Presione ENTER para continuar.\n";
            std::cin.get();
            return true;
        };

        // ELIMINACION FISICA
        /*
        if (_repo.eliminar(_repo.getPos(turno.getID()))){
            std::cout << "El turno se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el turno.\n";
            return false;
        }
        */
        std::cout << "Ocurrio un error al intentar eliminar el turno. Presione ENTER para continuar.\n";
        std::cin.get();
        return false;
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoTurno ManagerTurno::getRepositorio(){
    return _repo;
}
