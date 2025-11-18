#include "manager/ManagerSecuencia.h"
#include "utils/rlutil.h"
#include <cstring>


ManagerSecuencia::ManagerSecuencia(){};

Secuencia ManagerSecuencia::cargar(std::string objeto){
    Secuencia* aux = _repo.leerTodos();
    
    // ID ultima secuencia guardada + 1
    int nextIdSecuencia = _repo.cantidadRegistros() + 1;

    Secuencia nuevo(nextIdSecuencia, objeto.c_str(), 1);

    if (aux != nullptr) {
        // Hay datos
        for (int i = 0; i < nextIdSecuencia - 1; i ++) {
            // Revisar si el objeto existe
            if (strcmp(aux[i].getObjeto(), objeto.c_str()) == 0) {
                // Existe
                nuevo = aux[i];
                // Sumarle 1 al ultimo ID existente
                nuevo.setIdActual(nuevo.getIdActual() + 1);
                break;
            } else {
                _repo.guardar(nuevo);
            }
        }
    } else {
        // El objeto no existe
        _repo.guardar(nuevo);
    }

    delete[] aux;

    return nuevo;
}

bool ManagerSecuencia::eliminar(Secuencia secuencia){
    int pos = _repo.getPos(secuencia.getId());

    if (pos == -1) {
        std::cout << "No se ha encontrado la secuencia con ID " << secuencia.getId() << ". Presione ENTER para continuar\n";
        rlutil::getkey();
        return false;
    }

    if (_repo.eliminar(pos)){
        std::cout << "Se ha eliminado la secuencia correctamente.\n";
        return true;
    };

    std::cout << "No se ha podido eliminar la secuencia. Presione ENTER para continuar\n";
    rlutil::getkey();
    return false;
}

bool ManagerSecuencia::actualizar(Secuencia secuencia){
    int pos = _repo.getPos(secuencia.getId());

    if (pos == -1) {
        std::cout << "No se ha encontrado la secuencia con ID " << secuencia.getId() << ". Presione ENTER para continuar\n";
        rlutil::getkey();
        return false;
    }

    if (_repo.modificar(secuencia, pos)){
        std::cout << "Se ha modificado la secuencia correctamente.\n";
        return true;
    };

    std::cout << "No se ha podido modificar la secuencia. Presione ENTER para continuar\n";
    rlutil::getkey();
    return false;
}

ArchivoSecuencia ManagerSecuencia::getRepositorio() {
    return _repo;
}
