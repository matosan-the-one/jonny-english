cc=g++ 
flags=-lSDL2 -l dl -I ./include/glad/

all:
	@$(cc) ./src/*.cpp ./src/*.c -o main $(flags)
	@./main

me a program:
	@$(cc) ./src/*.cpp -o main $(flags)
