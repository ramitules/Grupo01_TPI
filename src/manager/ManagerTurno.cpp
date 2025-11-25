#include "manager/ManagerPaciente.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTurno.h"
#include "utils/ManagerFecha.h"
#include "utils/ManagerHora.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include "Paciente.h"
#include <algorithm>
#include <iomanip>


ManagerTurno::ManagerTurno(){};

bool ManagerTurno::cargar(){
    std::cin.ignore(100, '\n');

    ManagerPaciente mPaciente;
    ManagerFecha mFecha;
    ManagerHora mHora;

    int proximoID = _repo.cantidadRegistros() + 1;
    int dniPaciente;
    float importe = 0.0f;
    bool pacienteExiste = false;
    Fecha fechaAtencion;
    Hora horaAtencion;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI
    while (true) {
        std::cout << "Ingrese el DNI del paciente (0 - listar todos): ";
        std::cin >> dniPaciente;

        if (dniPaciente == 0) {
            mPaciente.mostrarTodos();
            std::cout << "Ingrese el DNI del paciente: ";
            std::cin >> dniPaciente;
        }

        if (dniPaciente > 10000000 && dniPaciente < 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos.\n";
    }

    // Chequear si el paciente ya existe en la base de datos
    const int CANT_PACIENTES = mPaciente.getRepositorio().cantidadRegistros();

    for (int i = 0; i < CANT_PACIENTES; i ++) {
        if (mPaciente.getRepositorio().leer(i).getDNI() == dniPaciente) {
            pacienteExiste = true;
        }
    }

    // Dar la posibilidad de cargar todos los datos del paciente si no existe
    if (!pacienteExiste) {
        std::cout << "Paciente inexistente. Desea cargar sus datos ahora? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            if (!mPaciente.cargar(dniPaciente)) {
                std::cout << "No se pudo cargar el paciente. El turno no sera guardado.\n";
                std::cout << "Presione ENTER para continuar\n";
                rlutil::anykey();
                return false;
            }
        } else {
            Paciente paciente;
            paciente.setDNI(dniPaciente);
            mPaciente.getRepositorio().guardar(paciente);
        }
    }

    opc = 'n';

    std::cout << "El paciente se atendera ahora? s/n: ";
    std::cin >> opc;


    if (opc == 's') {
        ManagerProtocolo mProtocolo;

        Protocolo protocolo;
        protocolo.setIdTurno(proximoID);

        if (mProtocolo.chequearTurno(protocolo)) {
            std::cout << "\nATENCION: El turno ingresado ya tiene un Protocolo iniciado\n";
            menuVolver();
            return false;
        }

        //int id_proto = mProtocolo.iniciar(proximoID);

        if (mProtocolo.iniciar(protocolo)) {
            std::cout << "\nPROTOCOLO INICIADO.\n";
            pausa();
        } else {
            std::cout << "\nPROTOCOLO CANCELADO.";
            pausa();
            return false;
        }

        std::cout << "\nDesea cargar los estudios ahora s/n: ";
        std::cin >> opc;

        if (opc != 's') {
            //CARGA CANCELADA
            menuVolver();
            return false;
        }

        if (mProtocolo.cargarAnalisis(protocolo)) {
            std::cout << "\nANALISIS CARGADOS EXITOSAMENTE\n" ;
        } else {
            std::cout << "\nCARGA DE ANALISIS CANCELADA\n" ;
            menuVolver();
            return false;
        }

        // Obtener importe sumando todos los analisis por protocolos

        Protocolo auxProto;
        AnalisisProtocolo auxAP;
        ManagerAnalisisProtocolo mAP;

        bool* indices = new bool[mProtocolo.getRepositorio().cantidadRegistros()] {false};

        for (int i = 0; i < mProtocolo.getRepositorio().cantidadRegistros(); i ++) {

            auxProto = mProtocolo.getRepositorio().leer(i);

            if (auxProto.getIdTurno() == proximoID) {

                for (int j = 0; j < mAP.getRepositorio().cantidadRegistros(); j ++) {

                    auxAP = mAP.getRepositorio().leer(j);

                    if (auxAP.getIdProtocolo() == auxProto.getId()){
                        importe += auxAP.getTipoAnalisis().getPrecio();
                    }
                }
            }
        }
        delete[] indices;
        
    } else {
        std::cin.ignore(100, '\n');

        fechaAtencion = mFecha.cargar();
        horaAtencion = mHora.cargar();

        std::cout << "Ingrese a continuacion el importe a cobrar: $";
        std::cin >> importe;
        std::cin.ignore(100, '\n');
    }

    Turno turno(proximoID, dniPaciente, fechaAtencion, horaAtencion, importe);

    if (_repo.guardar(turno)) {
        std::cout << "El turno se ha guardado correctamente. Presione ENTER para continuar\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el turno. Presione ENTER para continuar\n";
    rlutil::anykey();
    return false;
}

std::string ManagerTurno::mostrarCabecera(const int anchoPaciente, const int anchoFecha, const int anchoImporte) {
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(5, '-') + 
                        "+" + std::string(anchoPaciente + 2, '-') + 
                        "+" + std::string(anchoFecha + 2, '-') + 
                        "+" + std::string(15, '-') +
                        "+" + std::string(anchoImporte + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(3) << "ID" << " | " 
              << std::setw(anchoPaciente) << "Paciente" << " | "
              << std::setw(anchoFecha) << "Fecha atencion" << " | "
              << std::setw(13) << "Hora atencion" << " | "
              << std::setw(anchoImporte) << "Importe" << " |\n";
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
    std::string nombreCompleto;
    std::string precioStr;

    nombreCompleto = turno.getPaciente().getNombre();
    nombreCompleto += " ";
    nombreCompleto += turno.getPaciente().getApellido();

    anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
    anchoFecha = std::max(anchoFecha, (int)turno.getFechaAtencion().to_str().length());
    precioStr = std::to_string((int)turno.getImporte()) + ".00";
    anchoImporte = std::max(anchoImporte, (int)precioStr.length());

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte);

    std::cout << "| " << std::setw(3) << turno.getID() << " | " 
              << std::setw(anchoPaciente) << nombreCompleto << " | "
              << std::setw(anchoFecha) << turno.getFechaAtencion().to_str() << " | "
              << std::setw(13) << turno.getHoraAtencion().to_str() << " | "
              << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turno.getImporte() << " |\n";
}

void ManagerTurno::mostrarVarios(Turno* turnos, const int cantidad) {
    if (cantidad == 0) {
        std::cout << "No hay turnos para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoPaciente = 8; // Largo minimo "Paciente"
    int anchoFecha = 14;   // Largo minimo "Fecha Atencion"
    int anchoImporte = 7;  // Largo minimo "Importe"
    std::string nombreCompleto;
    std::string precioStr;

    for(int i=0; i<cantidad; i++) {
        if (turnos[i].getEliminado()) {
            continue;
        }
        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();

        anchoPaciente = std::max(anchoPaciente, (int)nombreCompleto.length());
        anchoFecha = std::max(anchoFecha, (int)turnos[i].getFechaAtencion().to_str().length());
        precioStr = std::to_string((int)turnos[i].getImporte()) + ".00";
        anchoImporte = std::max(anchoImporte, (int)precioStr.length());
    }

    std::string linea = mostrarCabecera(anchoPaciente, anchoFecha, anchoImporte);

    // Datos
    for(int i=0; i<cantidad; i++){
        if (turnos[i].getEliminado()) {
            continue;
        }

        nombreCompleto = turnos[i].getPaciente().getNombre();
        nombreCompleto += " ";
        nombreCompleto += turnos[i].getPaciente().getApellido();
        
        std::cout << "| " << std::setw(3) << turnos[i].getID() << " | " 
                  << std::setw(anchoPaciente) << nombreCompleto << " | "
                  << std::setw(anchoFecha) << turnos[i].getFechaAtencion().to_str() << " | "
                  << std::setw(13) << turnos[i].getHoraAtencion().to_str() << " | "
                  << "$ " << std::setw(anchoImporte - 2) << std::fixed << std::setprecision(2) << turnos[i].getImporte() << " |\n";
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

    // Finalizar
    delete[] turnos;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
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

        // Reiniciar variables
        totalPacientes = 0;
        iAux = 0;
        for (int j = 0; j < CANTIDAD; j ++) { indicesPacientes[j] = false; }
        delete[] turnosPaciente;
    }

    delete[] turnos;
    delete[] indicesVisitados;
    delete[] indicesPacientes;

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
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
    rlutil::anykey();
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
        std::cout << "\n\n";
        delete[] turnosPaciente;
    } else {
        std::cout << "No se ha encontrado el paciente en la base de datos de turnos\n";
    }

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();

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

bool ManagerTurno::actualizar(Turno turno){
    std::cin.ignore(100, '\n');

    ManagerFecha mFecha;
    ManagerHora mHora;

    int dniPaciente;
    float importe = 0.0f;
    char opc = 'n';

    // Carga de paciente. Comienza con DNI
    while (true) {
        std::cout << "Ingrese el DNI del paciente (0 para dejarlo como estaba): ";
        std::cin >> dniPaciente;

        if (dniPaciente == 0) {
            dniPaciente = turno.getDniPaciente();
            break;
        }

        if (dniPaciente > 10000000 && dniPaciente < 99999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 8 digitos.\n";
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

    std::cout << "El paciente se atendera ahora? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        ManagerProtocolo mProtocolo;

        Protocolo protocolo;
        protocolo.setIdTurno(turno.getID());

        if (mProtocolo.chequearTurno(protocolo)) {
            std::cout << "\nATENCION: El turno ingresado ya tiene un Protocolo iniciado\n";
            menuVolver();
            return false;
        }

        //int id_proto = mProtocolo.iniciar(proximoID);

        if (mProtocolo.iniciar(protocolo)) {
            std::cout << "\nPROTOCOLO INICIADO.\n";
            pausa();
        } else {
            std::cout << "\nPROTOCOLO CANCELADO.";
            pausa();
            return false;
        }

        std::cout << "\nDesea cargar los estudios ahora s/n: ";
        std::cin >> opc;

        if (opc != 's') {
            //CARGA CANCELADA
            menuVolver();
            return false;
        }

        if (mProtocolo.cargarAnalisis(protocolo)) {
            std::cout << "\nANALISIS CARGADOS EXITOSAMENTE\n" ;
        } else {
            std::cout << "\nCARGA DE ANALISIS CANCELADA\n" ;
            menuVolver();
            return false;
        }

        // Obtener importe sumando todos los analisis por protocolos
        Protocolo auxProto;
        ManagerAnalisisProtocolo mAP;

        bool* indices = new bool[mProtocolo.getRepositorio().cantidadRegistros()] {false};
        for (int i = 0; i < mProtocolo.getRepositorio().cantidadRegistros(); i ++) {
            auxProto = mProtocolo.getRepositorio().leer(i);
            if (auxProto.getIdTurno() == turno.getID()) {
                for (int j = 0; j < mAP.getRepositorio().cantidadRegistros(); j ++) {
                    if (mAP.getRepositorio().leer(j).getIdProtocolo() == auxProto.getId()){
                        importe += mAP.getRepositorio().leer(j).getTipoAnalisis().getPrecio();
                    }
                }
            }
        }
        delete[] indices;
        
    }

    if (_repo.modificar(turno, _repo.getPos(turno.getID()))) {
        std::cout << "El turno se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el turno. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
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
            rlutil::anykey();
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
        rlutil::anykey();
        return false;
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoTurno ManagerTurno::getRepositorio(){
    return _repo;
}
