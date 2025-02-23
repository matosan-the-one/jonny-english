cc=g++ -w
files=./src/player.cpp

all:
	@$(cc) ./src/main.cpp -o ./main -lSDL2
	@./main

me a sandwich: jonny.cpp
	@$(cc) jonny.cpp -o jonny -lSDL2
