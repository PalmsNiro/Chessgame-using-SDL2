# Compiler und Flags
CXX = g++
CXXFLAGS = -I libraries/include -I src/includes
LDFLAGS = -L libraries/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Ziel und Quell-Dateien
TARGET = main
SOURCES = src/main.cpp src/Chessboard.cpp src/Piece.cpp src/Pawn.cpp src/Rook.cpp src/Bishop.cpp src/Knight.cpp src/Queen.cpp src/King.cpp src/Game.cpp src/Utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Standardregel
all: $(TARGET)

# Regel zum Erzeugen des Ziels
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

# Regeln zum Erzeugen der Objekt-Dateien
src/main.o: src/main.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Chessboard.o: src/Chessboard.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Piece.o: src/Piece.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Pawn.o: src/Pawn.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Rook.o: src/Rook.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Bishop.o: src/Bishop.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Knight.o: src/Knight.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Queen.o: src/Queen.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/King.o: src/King.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Game.o: src/Game.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

src/Utils.o: src/Utils.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Regel zum Aufräumen
clean:
	@echo "Cleaning up..."
	@if [ -f $(TARGET).exe ]; then rm $(TARGET).exe; fi
	@if [ -f src/main.o ]; then rm src/main.o; fi
	@if [ -f src/Chessboard.o ]; then rm src/Chessboard.o; fi
	@if [ -f src/Piece.o ]; then rm src/Piece.o; fi
	@if [ -f src/Pawn.o ]; then rm src/Pawn.o; fi
	@if [ -f src/Rook.o ]; then rm src/Rook.o; fi
	@if [ -f src/Bishop.o ]; then rm src/Bishop.o; fi
	@if [ -f src/Knight.o ]; then rm src/Knight.o; fi
	@if [ -f src/Queen.o ]; then rm src/Queen.o; fi
	@if [ -f src/King.o ]; then rm src/King.o; fi
	@if [ -f src/Game.o ]; then rm src/Game.o; fi
	@if [ -f src/Utils.o ]; then rm src/Utils.o; fi
	@echo "Clean done."

# Phony targets (diese werden immer ausgeführt, auch wenn eine Datei gleichen Namens existiert)
.PHONY: all clean
