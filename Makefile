# Nombre del ejecutable
TARGET = sistema_gestion

# Carpetas
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Archivos fuente (.cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Archivos objeto (.o) generados en build/
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -pedantic-errors -I$(INC_DIR)

# Regla por defecto
all: $(BUILD_DIR) $(TARGET)
# Linkeo final
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$(TARGET)

# Compilación de .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar compilados
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean