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
    src/Analisis.cpp
    src/Enfermero.cpp
    src/Paciente.cpp
    src/Persona.cpp
    src/Secuencia.cpp
    src/TipoAnalisis.cpp
    src/Turno.cpp
    src/menu/Menu.cpp
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
