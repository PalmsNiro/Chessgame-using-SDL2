# Compiler und Flags
CXX = g++
CXXFLAGS = -I libraries/include -I src
LDFLAGS = -L libraries/lib -lmingw32 -lSDL2main -lSDL2

# Ziel und Quell-Dateien
TARGET = main
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:src/%.cpp=src/%.o)

# Standardregel
all: $(TARGET)

# Regel zum Erzeugen des Ziels
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

# Regel zum Erzeugen der Objekt-Dateien
src/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Regel zum Aufräumen
clean:
	@echo "Cleaning up..."
	@if [ -f $(TARGET).exe ]; then rm $(TARGET).exe; fi
# @if [ -f main.o ]; then rm main.o; fi
	@if ls src/*.o > /dev/null 2>&1; then rm src/*.o; fi
	@echo "Clean done."

# Phony targets (diese werden immer ausgeführt, auch wenn eine Datei gleichen Namens existiert)
.PHONY: all clean
