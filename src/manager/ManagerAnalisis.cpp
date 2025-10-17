#include "manager/ManagerAnalisis.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerSecuencia.h"
#include "manager/ManagerPaciente.h"


ManagerAnalisis::ManagerAnalisis(){};

bool ManagerAnalisis::cargar(){
    std::cin.ignore(100, '\n');

    ArchivoTipoAnalisis repoTipoAnalisis;
    ArchivoPaciente repoPacientes;

    ManagerTipoAnalisis mTipoAnalisis;
    ManagerPaciente managerPaciente;
    ManagerSecuencia managerSecuencia;

    Analisis analisis;
    Secuencia sec = managerSecuencia.cargar("Analisis");

    int proximoID = sec.getIdActual() + 1;
    int idTipoAnalisis = 0;
    int sala = 0;
    int dniPaciente = 0;
    bool opcValida = false;

    std::cout << "ID del analisis: " << proximoID << "\n";

    std::cout << "Tipos de analisis disponibles:\n";
    mTipoAnalisis.mostrarTodos();

    while (true) {
        std::cout << "------------------------------\n";
        std::cout << "ID tipo de analisis (0 para cancelar): ";
        std::cin >> idTipoAnalisis;
        
        if (idTipoAnalisis == 0) {
            return false;
        }

        for (int i = 0; i < repoTipoAnalisis.cantidadRegistros(); i++) {
            if (repoTipoAnalisis.leer(i).getID() == idTipoAnalisis) {
                opcValida = true;
                break;
            }
        }
        
        if (opcValida) {
            break;
        }

        std::cout << "Por favor ingrese un tipo de analisis valido\n";
    }
    
    std::cout << "Sala: ";
    std::cin >> sala;

    bool pacienteExiste = false;

    while (true) {
        std::cout << "DNI del paciente (0 para cancelar): ";
        std::cin >> dniPaciente;

        if (dniPaciente == 0) {
            return false;
        }

        // Entre un millon y cien millones
        if (dniPaciente < 1000000 || dniPaciente > 100000000) {
            std::cout << "Por favor ingrese un DNI valido\n";
        } else {
            for (int i = 0; i < repoPacientes.cantidadRegistros(); i++) {
                if (repoPacientes.leer(i).getDNI() == dniPaciente) {
                    pacienteExiste = true;
                    break;
                }
            }
            break;
        }
    }

    // Si el paciente no existe, solicitar mas datos del mismo de ser necesario
    char opc;

    if (!pacienteExiste) {
        std::cout << "El paciente no existe. Desea cargar los datos del mismo? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            managerPaciente.cargar();
        }
    }

    if (_repo.guardar(analisis)) {
        std::cout << "El analisis se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el analisis.\n";
    return false;
}

void ManagerAnalisis::mostrar(Analisis analisis){
    Paciente auxP = analisis.getPaciente();
    TipoAnalisis auxTA = analisis.getTipoAnalisis();

    std::cout << "ID: " << analisis.getId() << "\n";
    std::cout << "Paciente: " << auxP.getNombre() << " " << auxP.getApellido() << ", con DNI " << auxP.getDNI() << "\n";
    std::cout << "Tipo de analsis: " << auxTA.getID() << " - " << auxTA.getNombreAnalisis() << "\n";
    std::cout << "Sala: " << analisis.getSala() << "\n";
}

void ManagerAnalisis::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerAnalisis::actualizar(Analisis analisis){
    // PENDIENTE
}

bool ManagerAnalisis::eliminar(Analisis analisis){
    char opc;

    std::cout << "Seguro que desea eliminar el analisis? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (_repo.eliminar(_repo.getPos(analisis.getId()))){
            std::cout << "El analisis se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el analisis.\n";
            return false;
        }
    }
}
