cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(ProyectoC++ VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir la carpeta include (y subcarpetas)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Lista de .cpp
set(SOURCES
    main.cpp
    src/analisis.cpp
    src/Enfermero.cpp
    src/paciente.cpp
    src/Persona.cpp
    src/Secuencia.cpp
    src/tipoAnalisis.cpp
    src/turno.cpp
    src/ObraSocial.cpp
    src/menu/Menu.cpp
    src/menu/MenuAnalisis.cpp
    src/menu/MenuEnfermero.cpp
    src/menu/MenuPaciente.cpp
    src/menu/MenuPrincipal.cpp
    src/menu/MenuTipoAnalisis.cpp
    src/menu/MenuTurno.cpp
    src/menu/listados/MenuListados.cpp
    src/menu/listados/ListadosAnalisis.cpp
    src/menu/listados/ListadosObrasSociales.cpp
    src/menu/listados/ListadosPacientes.cpp
    src/menu/listados/ListadosTurnos.cpp
    src/menu/consultas/MenuConsultas.cpp
    src/menu/consultas/ConsultasAnalisis.cpp
    src/menu/consultas/ConsultasPacientes.cpp
    src/menu/consultas/ConsultasTurnos.cpp
    src/menu/informes/MenuInformes.cpp
    src/utils/Fecha.cpp
    src/utils/Hora.cpp
)

# Crear ejecutable
add_executable(sistema_gestion ${SOURCES})

# Opciones del compilador (equivalente a -Wall -pedantic -pedantic-errors)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sistema_gestion PRIVATE -Wall -pedantic -pedantic-errors)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(sistema_gestion PRIVATE /W4 /permissive-)
endif()
