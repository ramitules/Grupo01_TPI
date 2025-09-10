CXX = g++

CXXFLAGS = -std=c++14 -Wall -pedantic -pedantic-errors -Iinclude

# Carpetas de código
SRC_DIRS = .

SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = Ejecutable

# Regla por defecto: compilar y linkear
all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(OUTPUT)

# Regla generica: de .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUT) $(OBJECTS)