#include "manager/ManagerSecuencia.h"
#include <cstring>


ManagerSecuencia::ManagerSecuencia(){};

Secuencia ManagerSecuencia::cargar(std::string objeto){
    Secuencia* aux = _repo.leerTodos();
    
    int nextIdSecuencia = _repo.cantidadRegistros() + 1;

    Secuencia nuevo(nextIdSecuencia, objeto.c_str(), 0);

    if (aux != nullptr) {
        // Hay datos
        for (int i = 0; i < nextIdSecuencia - 1; i ++) {
            // Revisar si el objeto existe
            if (strcmp(aux[i].getObjeto(), objeto.c_str()) == 0) {  
                nuevo = aux[i];
                break;
            }
        }
    } else {
        // El objeto no existe
        if (_repo.guardar(nuevo)){
            std::cout << "Se ha guardado la secuencia correctamente.\n";
        };
    }

    delete[] aux;

    return nuevo;
}

bool ManagerSecuencia::eliminar(Secuencia secuencia){
    int pos = _repo.getPos(secuencia.getId());

    if (pos == -1) {
        std::cout << "No se ha encontrado la secuencia con ID " << secuencia.getId() << "\n";
        return false;
    }

    if (_repo.eliminar(pos)){
        std::cout << "Se ha eliminado la secuencia correctamente.\n";
        return true;
    };

    std::cout << "No se ha podido eliminar la secuencia.\n";
    return false;
}

bool ManagerSecuencia::actualizar(Secuencia secuencia){
    int pos = _repo.getPos(secuencia.getId());

    if (pos == -1) {
        std::cout << "No se ha encontrado la secuencia con ID " << secuencia.getId() << "\n";
        return false;
    }

    if (_repo.modificar(secuencia, pos)){
        std::cout << "Se ha modificado la secuencia correctamente.\n";
        return true;
    };

    std::cout << "No se ha podido modificar la secuencia.\n";
    return false;
}

int ManagerSecuencia::getNuevoID(Secuencia secuencia){
    Secuencia* aux = _repo.leerTodos();

    if (aux == nullptr){
        return 0;
    }

    int maxId = -1;
    const int CANTIDAD = _repo.cantidadRegistros();

    for (int i = 0; i < CANTIDAD; i++){
        if (strcmp(aux[i].getObjeto(), secuencia.getObjeto()) == 0){
            maxId = aux[i].getIdActual();
            break;
        }
    }

    delete[] aux;

    return maxId + 1;
}