cc=g++ -w

all:
	@$(cc) jonny.cpp -o jonny -lSDL2
	@./jonny

me a sandwich: jonny.cpp
	@$(cc) jonny.cpp -o jonny -lSDL2
