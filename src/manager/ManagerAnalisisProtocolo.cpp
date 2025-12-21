#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerProtocolo.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "Protocolo.h"
#include "AnalisisProtocolo.h"
#include "utils/Fecha.h"
#include "utils/ManagerFecha.h"
#include "archivo/ArchivoTurno.h"
#include "manager/ManagerPaciente.h"
#include "manager/ManagerTurno.h"


ManagerAnalisisProtocolo::ManagerAnalisisProtocolo(){};

bool ManagerAnalisisProtocolo::comprobar(int idProtocolo, int idTipoAnalisis) {
    AnalisisProtocolo regAnalisisProtocolo;
    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();

    if (cantidadAnalisisProtocolo == 0) {
        std::cout << "\nRegistro vacio.\n" << std::endl;
        return false;
    }

    if (idProtocolo == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (regAnalisisProtocolo.getIdProtocolo() == idProtocolo && regAnalisisProtocolo.getIdTipoAnalisis()==idTipoAnalisis) {
            return true;
        }
    }
    return false;
}

bool ManagerAnalisisProtocolo::cargar(int idProtocolo) {
    std::cin.ignore(100, '\n');

    ManagerProtocolo mProtocolo;
    ManagerTipoAnalisis mTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    TipoAnalisis regTipoAnalisis;
    AnalisisProtocolo regAnalisisProtocolo;
    bool analisisCargados = false;

    char opc;

    std::cout << "\nAnalisis disponibles para agregar al protocolo \n" << std::endl;
    mTipoAnalisis.mostrarTodos();

    while (true) {
        int idTipoAnalisis;

        std::cout << "\nCARGAR ID del analisis (0 para terminar): ";
        std::cin >> idTipoAnalisis;

        if (idTipoAnalisis == 0) {
            if (analisisCargados) {
                return true;
            } else {
                return false;
            }
        }

        if (mTipoAnalisis.comprobar(idTipoAnalisis)) {
            regTipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);
        } else {
            continue;
        }

        if (mAnalisisProtocolo.comprobar(idProtocolo,idTipoAnalisis)) {
            std::cout << "\n\tYa se encuentra cargado este analisis al Protocolo\n";
            analisisCargados = true;
            continue;
        }


        //Comprobar que no este cargado

        std::cout << "CONFIRMAR: agregar " << regTipoAnalisis.getNombreAnalisis() << " al Protocolo? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            regAnalisisProtocolo.setIdProtocolo(idProtocolo);
            regAnalisisProtocolo.setIdTipoAnalisis(regTipoAnalisis.getID());
            regAnalisisProtocolo.setPrecioSolicitud(regTipoAnalisis.getPrecio());

            if (_repo.guardar(regAnalisisProtocolo)){
                std::cout << "\n\tEl Analisis se ha agregado correctamente.\n";
                analisisCargados = true;

                //Buscar el turno del Protocolo y actualizar el importe
                ManagerTurno mTurno;

                if (mTurno.actualizarImporte(regAnalisisProtocolo)) {
                    std::cout << "\tSe modifico el importe en el turno";
                }
                else {
                    std::cout << "\tNo se modifico el importe en el turno";
                }
            } else {
                std::cout << "Ocurrio un error al intentar agregar el analisis.\n";
            }
        }
    }
}

void ManagerAnalisisProtocolo::mostrarTodos(int idProtocolo) {
    ManagerTipoAnalisis mTipoAnalisis;
    ManagerProtocolo mProtocolo;
    AnalisisProtocolo regAnalisisProtocolo;
    Protocolo protocolo = mProtocolo.seleccionar(idProtocolo);
    TipoAnalisis regTipoAnalisis;

    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();
    int resultadoDias = -1;
    int precioProtocolo = 0;
    std::string estadoProtocolo = (protocolo.getEstado())? "FINALIZADO" : "PENDIENTE";

    //MOSTRAR LOS ESTUDIOS CARGADOS EN EL PROTOCOLO

    std::cout << "\n\tID\tTipo\t\tTiempo estimado\tPrecio solicitud\n";

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (idProtocolo==regAnalisisProtocolo.getIdProtocolo()) {
            regTipoAnalisis = regAnalisisProtocolo.getTipoAnalisis();

            std::cout << "\t" << regTipoAnalisis.getID() << "\t" ;
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t     ";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "$ " << regAnalisisProtocolo.getPrecioSolicitud() << "\n";

            precioProtocolo += regTipoAnalisis.getPrecio();

            if (regTipoAnalisis.getTiempoResultado() > resultadoDias) {
                resultadoDias = regTipoAnalisis.getTiempoResultado();
            }
        }
    }

    std::cout << "\n\tPrecio del Protocolo: $" << precioProtocolo;
    std::cout << "\n\tEstado: " << estadoProtocolo << std::endl;

    ManagerTurno mTurno;
    ManagerPaciente mPaciente;
    Turno regTurno;

    //BUSCAR AL PACIENTE: mediante el DNI del paciente en el archivo turno
    int posicionTurno;
    int dniPaciente;

    posicionTurno = mTurno.getRepositorio().getPos(protocolo.getIdTurno());
    dniPaciente = mTurno.getRepositorio().leer(posicionTurno).getDniPaciente();

    //CALCULAR EL PRECIO PARA EL PACIENTE DEL PROTOCOLO: chequear la obra social mediante el objeto Paciente

    int posicionPaciente;
    Paciente regPaciente;
    int cobertura;
    std::string nombreObraSocial;

    posicionPaciente = mPaciente.getRepositorio().getPos(dniPaciente);
    regPaciente = mPaciente.getRepositorio().leer(posicionPaciente);
    cobertura = regPaciente.getObraSocial().getCobertura();
    nombreObraSocial = regPaciente.getObraSocial().getNombre();

    float precioPaciente = precioProtocolo * (100 - cobertura) / 100;

    //Fechas
    ManagerFecha mFecha;
    Fecha fechaTurno;
    Fecha fechaResultados;

    regTurno = mTurno.getRepositorio().leer(posicionTurno);
    fechaTurno = regTurno.getFechaAtencion();
    fechaResultados = mFecha.sumarDias(fechaTurno, resultadoDias);

    if (protocolo.getEstado()) {
        std::cout << "\n\tCOBERTURA: " << nombreObraSocial << " (" << cobertura << "%)" ;
        std::cout << "\n\tPRECIO FINAL: $" << precioPaciente ;
        std::cout << "\n\tFECHA DEL TURNO: " ;
        std::cout << fechaTurno.to_str();
        std::cout << "\n\tRESULTADOS en " << resultadoDias << " dia(s)" ;
        std::cout << "\n\tDISPONIBLE PARA RETIRAR: ";
        std::cout << fechaResultados.to_str() << std::endl;
    } else {
        std::cout << "\n\tCOBERTURA: " << precioPaciente ;
        std::cout << "\n\tPRECIO ESTIMADO (SOLICITUD): $" << precioPaciente ;
        std::cout << "\n\tFECHA DEL TURNO: " ;
        std::cout << fechaTurno.to_str();
        std::cout << "\n\tRESULTADOS en " << resultadoDias << " dia(s)" ;
        std::cout << "\n\tDISPONIBLE PARA RETIRAR: ";
        std::cout << fechaResultados.to_str() << std::endl;
    }
}

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}