FILE ?= main
OBJS = build/ChessBoard.o build/Bitboard.o build/UCIHandler.o build/LegalMoves.o

all: directories bin/$(FILE)

bin/$(FILE): $(OBJS) src/$(FILE).cpp
	g++ $(OBJS) src/$(FILE).cpp -o bin/$(FILE)

build/%.o: src/%.cpp src/include/%.h
	g++ -c $< -o $@

run: bin/$(FILE)
	./bin/$(FILE)

clean:
	del /F /Q bin\$(FILE) build\*.o

directories:
	if not exist bin mkdir bin
	if not exist build mkdir build
