compile:
	g++ -c ./lib/main.cpp -I ./include -o ./src/main.o
	g++ ./src/main.o -o ./src/app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./src/app