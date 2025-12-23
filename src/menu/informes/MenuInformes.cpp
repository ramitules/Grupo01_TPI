#include "menu/informes/MenuInformes.h"
#include "archivo/ArchivoTurno.h"
#include "archivo/ArchivoPaciente.h"
#include "archivo/ArchivoObraSocial.h"
#include "archivo/ArchivoProtocolo.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "archivo/ArchivoTipoAnalisis.h"
#include "utils/rlutil.h"
#include <iostream>
#include <map>
#include <iomanip>
#include "manager/ManagerObraSocial.h"
#include "manager/ManagerProtocolo.h"


MenuInformes::MenuInformes(): Menu(5, "Menu Informes"){
    std::string opciones[5] = {
        "Analisis totales realizados en el mes por tipo",
        "Analisis totales realizados en el mes por Obra Social",
        "Pacientes atendidos por Obra Social",
        "Facturacion mensual total",
        "Facturacion mensual por Obra Social"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuInformes::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) { return; }

    if (_opcionSeleccionada == 1) {
        informeAnalisisPorTipo();
    }
    if (_opcionSeleccionada == 3) {
        informePacientesPorObraSocial();
    }
    if (_opcionSeleccionada == 4) {
        informeFacturacionMensualTotal();
    }
    if (_opcionSeleccionada == 5) {
        informeFacturacionMensualPorObraSocial();
    }
    if (_opcionSeleccionada == 2) {
        informeAnalisisPorObraSocial();
    }

    std::cin.get();
}

void MenuInformes::informeAnalisisPorObraSocial() {
    rlutil::cls();
    std::cout << "INFORME - CANTIDAD DE ANALISIS POR OBRA SOCIAL\n";
    std::cout << "----------------------------------------------\n";

    int mes, anio, idObraSocial;
    Fecha fechaActual;

    std::cout << "Ingrese el anio (0 para el actual): ";
    std::cin >> anio;
    if (anio == 0) anio = fechaActual.getAnio();

    std::cout << "Ingrese el mes (0 para todo el anio): ";
    std::cin >> mes;

    ManagerObraSocial managerObraSocial;
    std::cout << "\nSeleccione una Obra Social:\n";
    managerObraSocial.mostrarTodos(true); // Mostrar lista ID - Nombre

    std::cout << "\nIngrese el ID de la Obra Social: ";
    std::cin >> idObraSocial;

    ArchivoObraSocial archivoObraSocial;
    if (archivoObraSocial.getPos(idObraSocial) == -1) {
        std::cout << "ID de Obra Social no valido.\n";
        std::cin.get();
        return;
    }

    ArchivoTurno archivoTurno;
    int cantidadTurnos = archivoTurno.cantidadRegistros();
    Turno* turnos = archivoTurno.leerTodos();

    ArchivoPaciente archivoPaciente;
    int cantidadPacientes = archivoPaciente.cantidadRegistros();
    Paciente* pacientes = archivoPaciente.leerTodos();

    ArchivoProtocolo archivoProtocolo;
    int cantidadProtocolos = archivoProtocolo.cantidadRegistros();
    Protocolo* protocolos = archivoProtocolo.leerTodos();

    ArchivoAnalisisProtocolo archivoAnalisisProtocolo;
    int cantidadAnalisisProtocolo = archivoAnalisisProtocolo.cantidadRegistros();
    AnalisisProtocolo* analisisProtocolos = archivoAnalisisProtocolo.leerTodos();

    ArchivoTipoAnalisis archivoTipoAnalisis;
    int cantidadTipoAnalisis = archivoTipoAnalisis.cantidadRegistros();
    TipoAnalisis* tiposAnalisis = archivoTipoAnalisis.leerTodos();

    std::map<int, int> conteoPorTipo; // ID TipoAnalisis -> Cantidad

    // Inicializar conteo
    for (int i = 0; i < cantidadTipoAnalisis; i++) {
        if (!tiposAnalisis[i].getEliminado()) {
            conteoPorTipo[tiposAnalisis[i].getID()] = 0;
        }
    }

    // Filtrar y contar
    for (int i = 0; i < cantidadTurnos; i++) {
        if (turnos[i].getEliminado()) continue;

        bool fechaValida = false;
        if (mes == 0) { // Informe anual
            if (turnos[i].getFechaAtencion().getAnio() == anio) {
                fechaValida = true;
            }
        } else { // Informe mensual
            if (turnos[i].getFechaAtencion().getAnio() == anio && 
                turnos[i].getFechaAtencion().getMes() == mes) {
                fechaValida = true;
            }
        }

        if (fechaValida) {
            // Verificar Obra Social del paciente
            int dniPaciente = turnos[i].getDniPaciente();
            bool pacienteDeObraSocial = false;

            for (int p = 0; p < cantidadPacientes; p++) {
                if (pacientes[p].getDNI() == dniPaciente) {
                    if (pacientes[p].getCodigoObraSocial() == idObraSocial) {
                        pacienteDeObraSocial = true;
                    }
                    break;
                }
            }

            if (pacienteDeObraSocial) {
                // Buscar protocolos asociados al turno
                for (int j = 0; j < cantidadProtocolos; j++) {
                    if (protocolos[j].getEliminado()) continue;
                    
                    if (protocolos[j].getIdTurno() == turnos[i].getID()) {
                        // Buscar analisis asociados al protocolo
                        for (int k = 0; k < cantidadAnalisisProtocolo; k++) {
                            if (analisisProtocolos[k].getIdProtocolo() == protocolos[j].getId()) {
                                conteoPorTipo[analisisProtocolos[k].getIdTipoAnalisis()]++;
                            }
                        }
                    }
                }
            }
        }
    }

    // Mostrar resultados
    std::cout << "\n";
    std::cout << std::left << std::setw(30) << "TIPO DE ANALISIS" << std::setw(10) << "CANTIDAD" << "\n";
    std::cout << "----------------------------------------\n";

    int totalAnalisis = 0;
    for (int i = 0; i < cantidadTipoAnalisis; i++) {
        if (!tiposAnalisis[i].getEliminado()) {
            int id = tiposAnalisis[i].getID();
            int cantidad = conteoPorTipo[id];
            if (cantidad > 0) {
                std::cout << std::left << std::setw(30) << tiposAnalisis[i].getNombreAnalisis() 
                          << std::setw(10) << cantidad << "\n";
                totalAnalisis += cantidad;
            }
        }
    }
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(30) << "TOTAL" << std::setw(10) << totalAnalisis << "\n";

    delete[] turnos;
    delete[] pacientes;
    delete[] protocolos;
    delete[] analisisProtocolos;
    delete[] tiposAnalisis;

    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void MenuInformes::informePacientesPorObraSocial() {
    rlutil::cls();
    std::cout << "INFORME - PACIENTES ATENDIDOS POR OBRA SOCIAL\n";
    std::cout << "---------------------------------------------\n";

    int mes, anio;
    Fecha fechaActual;

    std::cout << "Ingrese el anio (0 para el actual): ";
    std::cin >> anio;
    if (anio == 0) anio = fechaActual.getAnio();

    std::cout << "Ingrese el mes: ";
    std::cin >> mes;

    ArchivoTurno archivoTurno;
    int cantidadTurnos = archivoTurno.cantidadRegistros();
    Turno* turnos = archivoTurno.leerTodos();

    ArchivoPaciente archivoPaciente;
    int cantidadPacientes = archivoPaciente.cantidadRegistros();
    Paciente* pacientes = archivoPaciente.leerTodos();

    ArchivoObraSocial archivoObraSocial;
    int cantidadObraSocial = archivoObraSocial.cantidadRegistros();
    ObraSocial* obrasSociales = archivoObraSocial.leerTodos();

    // Matrices dinamicas para contar pacientes unicos
    // dnisPorOS[i] almacenara los DNIs unicos para la Obra Social i
    // contadoresPorOS[i] almacenara la cantidad de pacientes para la Obra Social i
    int** dnisPorOS = new int*[cantidadObraSocial];
    int* contadoresPorOS = new int[cantidadObraSocial];

    // Inicializar
    for (int i = 0; i < cantidadObraSocial; i++) {
        // El maximo de pacientes unicos es el total de pacientes registrados
        if (cantidadPacientes > 0) {
            dnisPorOS[i] = new int[cantidadPacientes];
        } else {
            dnisPorOS[i] = nullptr;
        }
        contadoresPorOS[i] = 0;
    }

    ManagerProtocolo mProtocolo;

    for (int i = 0; i < cantidadTurnos; i++) {
        if (turnos[i].getEliminado()) continue;

        if ((mProtocolo.seleccionarxTurno(turnos[i].getID()).getEstado()) == false) continue;

        if (turnos[i].getFechaAtencion().getAnio() == anio && 
            turnos[i].getFechaAtencion().getMes() == mes) {
            
            int dni = turnos[i].getDniPaciente();
            int idObraSocial = -1;

            // Buscar obra social del paciente
            for (int j = 0; j < cantidadPacientes; j++) {
                if (pacientes[j].getDNI() == dni) {
                    idObraSocial = pacientes[j].getCodigoObraSocial();
                    break;
                }
            }

            if (idObraSocial != -1) {
                // Buscar el indice de la obra social en el array obrasSociales
                int indexOS = -1;
                for (int k = 0; k < cantidadObraSocial; k++) {
                    if (obrasSociales[k].getID() == idObraSocial) {
                        indexOS = k;
                        break;
                    }
                }

                if (indexOS != -1 && dnisPorOS[indexOS] != nullptr) {
                    // Verificar si el DNI ya esta en la lista de esta Obra Social
                    bool existe = false;
                    for (int k = 0; k < contadoresPorOS[indexOS]; k++) {
                        if (dnisPorOS[indexOS][k] == dni) {
                            existe = true;
                            break;
                        }
                    }

                    if (!existe) {
                        dnisPorOS[indexOS][contadoresPorOS[indexOS]] = dni;
                        contadoresPorOS[indexOS]++;
                    }
                }
            }
        }
    }

    // Mostrar resultados
    std::cout << "\n";
    std::cout << std::left << std::setw(30) << "OBRA SOCIAL" << std::setw(10) << "CANTIDAD PACIENTES" << "\n";
    std::cout << "--------------------------------------------------\n";

    int totalPacientes = 0;
    for (int i = 0; i < cantidadObraSocial; i++) {
        if (!obrasSociales[i].getEliminado()) {
            int cantidad = contadoresPorOS[i];
            
            if (cantidad > 0) {
                std::cout << std::left << std::setw(30) << obrasSociales[i].getNombre() 
                          << std::setw(10) << cantidad << "\n";
                totalPacientes += cantidad;
            }
        }
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "TOTAL" << std::setw(10) << totalPacientes << "\n";

    // Liberar memoria
    delete[] turnos;
    delete[] pacientes;
    delete[] obrasSociales;
    
    for (int i = 0; i < cantidadObraSocial; i++) {
        if (dnisPorOS[i] != nullptr) {
            delete[] dnisPorOS[i];
        }
    }
    delete[] dnisPorOS;
    delete[] contadoresPorOS;

    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void MenuInformes::informeFacturacionMensualPorObraSocial() {
    int mes, anio;
    
    std::cout << "Ingrese el mes (1-12): ";
    std::cin >> mes;
    std::cout << "Ingrese el anio: ";
    std::cin >> anio;

    ArchivoTurno archivoTurno;
    ArchivoPaciente archivoPaciente;
    ArchivoObraSocial archivoObraSocial;

    int cantidadTurnos = archivoTurno.cantidadRegistros();
    Turno* turnos = archivoTurno.leerTodos();

    if (turnos == nullptr || cantidadTurnos == 0) {
        std::cout << "No hay turnos registrados.\n";
        std::cin.get();
        return;
    }
    std::map<std::string, float> facturacionPorObraSocial;
    float totalGeneral = 0;

    bool turnoFinalizado = false;
    ManagerProtocolo mProtocolo;
    Protocolo auxProtocolo;

    for (int i = 0; i < cantidadTurnos; i++) {
        if (turnos[i].getEliminado()) continue;

        auxProtocolo = mProtocolo.seleccionarxTurno(turnos[i].getID());
        turnoFinalizado = auxProtocolo.getEstado();

        if (turnoFinalizado == false) continue;

        if (turnos[i].getFechaAtencion().getMes() == mes && turnos[i].getFechaAtencion().getAnio() == anio) {
            int posPaciente = archivoPaciente.getPos(turnos[i].getDniPaciente());
            if (posPaciente == -1) continue;

            Paciente paciente = archivoPaciente.leer(posPaciente);
            
            int posObraSocial = archivoObraSocial.getPos(paciente.getCodigoObraSocial());
            if (posObraSocial == -1) continue;

            ObraSocial obraSocial = archivoObraSocial.leer(posObraSocial);

            facturacionPorObraSocial[obraSocial.getNombre()] += turnos[i].getImporte();
            totalGeneral += turnos[i].getImporte();
        }
    }

    delete[] turnos;

    std::cout << "\n--- Facturacion Mensual por Obra Social (" << mes << "/" << anio << ") ---\n";
    std::cout << std::left << std::setw(30) << "Obra Social" << std::right << std::setw(15) << "Total Facturado" << "\n";
    std::cout << "----------------------------------------------\n";

    for (const auto& par : facturacionPorObraSocial) {
        std::cout << std::left << std::setw(30) << par.first 
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << par.second << "\n";
    }
    
    std::cout << "----------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "TOTAL GENERAL" 
              << std::right << std::setw(15) << std::fixed << std::setprecision(2) << totalGeneral << "\n";

    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void MenuInformes::informeFacturacionMensualTotal() {
    Fecha fechaActual;
    int mes, anio;
    
    std::cout << "Ingrese el mes (0 para actual: " << fechaActual.getMes() << "): ";
    std::cin >> mes;
    if (mes == 0) mes = fechaActual.getMes();

    std::cout << "Ingrese el anio (0 para actual: " << fechaActual.getAnio() << "): ";
    std::cin >> anio;
    if (anio == 0) anio = fechaActual.getAnio();

    ArchivoTurno archivoTurno;
    int cantidadTurnos = archivoTurno.cantidadRegistros();
    Turno* turnos = archivoTurno.leerTodos();

    if (turnos == nullptr || cantidadTurnos == 0) {
        std::cout << "No hay turnos registrados.\n";
        std::cin.get();
        return;
    }

    float totalGeneral = 0;
    int cantidadTurnosMes = 0;
    bool turnoFinalizado = false;
    ManagerProtocolo mProtocolo;
    Protocolo auxProtocolo;

    for (int i = 0; i < cantidadTurnos; i++) {
        if (turnos[i].getEliminado()) continue;

        auxProtocolo = mProtocolo.seleccionarxTurno(turnos[i].getID());
        turnoFinalizado = auxProtocolo.getEstado();

        if (turnoFinalizado == false) continue;

        if (turnos[i].getFechaAtencion().getMes() == mes && turnos[i].getFechaAtencion().getAnio() == anio) {
            totalGeneral += turnos[i].getImporte();
            cantidadTurnosMes++;
        }
    }

    delete[] turnos;

    std::cout << "\n--- Facturacion Mensual Total (" << mes << "/" << anio << ") ---\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "Cantidad de Turnos" 
              << std::right << std::setw(15) << cantidadTurnosMes << "\n";
    std::cout << std::left << std::setw(30) << "TOTAL FACTURADO" 
              << std::right << std::setw(15) << std::fixed << std::setprecision(2) << totalGeneral << "\n";
    std::cout << "----------------------------------------------\n";

    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void MenuInformes::informeAnalisisPorTipo() {
    rlutil::cls();
    std::cout << "INFORME - CANTIDAD DE ANALISIS POR TIPO\n";
    std::cout << "---------------------------------------\n";

    int mes, anio;
    Fecha fechaActual;

    std::cout << "Ingrese el anio (0 para el actual): ";
    std::cin >> anio;
    if (anio == 0) anio = fechaActual.getAnio();

    std::cout << "Ingrese el mes (0 para todo el anio): ";
    std::cin >> mes;

    ArchivoTurno archivoTurno;
    int cantidadTurnos = archivoTurno.cantidadRegistros();
    Turno* turnos = archivoTurno.leerTodos();

    ArchivoProtocolo archivoProtocolo;
    int cantidadProtocolos = archivoProtocolo.cantidadRegistros();
    Protocolo* protocolos = archivoProtocolo.leerTodos();

    ArchivoAnalisisProtocolo archivoAnalisisProtocolo;
    int cantidadAnalisisProtocolo = archivoAnalisisProtocolo.cantidadRegistros();
    AnalisisProtocolo* analisisProtocolos = archivoAnalisisProtocolo.leerTodos();

    ArchivoTipoAnalisis archivoTipoAnalisis;
    int cantidadTipoAnalisis = archivoTipoAnalisis.cantidadRegistros();
    TipoAnalisis* tiposAnalisis = archivoTipoAnalisis.leerTodos();

    std::map<int, int> conteoPorTipo; // ID TipoAnalisis -> Cantidad

    // Inicializar conteo
    for (int i = 0; i < cantidadTipoAnalisis; i++) {
        if (!tiposAnalisis[i].getEliminado()) {
            conteoPorTipo[tiposAnalisis[i].getID()] = 0;
        }
    }

    // Filtrar y contar
    for (int i = 0; i < cantidadTurnos; i++) {
        if (turnos[i].getEliminado()) continue;

        bool fechaValida = false;
        if (mes == 0) { // Informe anual
            if (turnos[i].getFechaAtencion().getAnio() == anio) {
                fechaValida = true;
            }
        } else { // Informe mensual
            if (turnos[i].getFechaAtencion().getAnio() == anio && 
                turnos[i].getFechaAtencion().getMes() == mes) {
                fechaValida = true;
            }
        }

        if (fechaValida) {
            // Buscar protocolos asociados al turno
            for (int j = 0; j < cantidadProtocolos; j++) {
                if (protocolos[j].getEliminado()) continue;
                
                if (protocolos[j].getIdTurno() == turnos[i].getID()) {
                    // Buscar analisis asociados al protocolo
                    for (int k = 0; k < cantidadAnalisisProtocolo; k++) {
                        if (analisisProtocolos[k].getIdProtocolo() == protocolos[j].getId()) {
                            conteoPorTipo[analisisProtocolos[k].getIdTipoAnalisis()]++;
                        }
                    }
                }
            }
        }
    }

    // Mostrar resultados
    std::cout << "\n";
    std::cout << std::left << std::setw(30) << "TIPO DE ANALISIS" << std::setw(10) << "CANTIDAD" << "\n";
    std::cout << "----------------------------------------\n";

    int totalAnalisis = 0;
    for (int i = 0; i < cantidadTipoAnalisis; i++) {
        if (!tiposAnalisis[i].getEliminado()) {
            int id = tiposAnalisis[i].getID();
            int cantidad = conteoPorTipo[id];
            if (cantidad > 0) {
                std::cout << std::left << std::setw(30) << tiposAnalisis[i].getNombreAnalisis() 
                          << std::setw(10) << cantidad << "\n";
                totalAnalisis += cantidad;
            }
        }
    }
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(30) << "TOTAL" << std::setw(10) << totalAnalisis << "\n";

    delete[] turnos;
    delete[] protocolos;
    delete[] analisisProtocolos;
    delete[] tiposAnalisis;

    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}
