cc=g++ 
flags=-lSDL2 -lSDL2_ttf -l dl -I ./include/glad/

all:
	@$(cc) ./src/*.cpp ./src/*.c -o main $(flags)
	@./main

me a program:
	@$(cc) ./src/*.cpp ./src/*.c -o main $(flags)
