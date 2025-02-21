cc=g++ -w

all:
	@$(cc) jonny.cpp -o jonny -lSDL2
	@./jonny
