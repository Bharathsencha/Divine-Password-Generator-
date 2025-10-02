# Makefile for Password Generator with raylib
# Works on both Linux and Windows (with MinGW)

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows settings
    CXX = g++
    TARGET = password_gen.exe
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    RM = del /Q
    RMDIR = rmdir /S /Q
else
    # Linux settings
    CXX = g++
    TARGET = password_gen
    LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
    RMDIR = rm -rf
endif

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SOURCES = main.cpp gui.cpp generator.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = gui.h generator.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
	@echo Build complete: $(TARGET)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	if exist *.o $(RM) *.o
	if exist $(TARGET) $(RM) $(TARGET)
else
	$(RM) $(OBJECTS) $(TARGET)
endif
	@echo Clean complete

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Help message
help:
	@echo Available targets:
	@echo   make          - Build the project
	@echo   make clean    - Remove build artifacts
	@echo   make rebuild  - Clean and build
	@echo   make run      - Build and run the program
	@echo   make help     - Show this help message

.PHONY: all clean rebuild run help