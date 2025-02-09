compile:
	mkdir -p ./src
	g++ -c ./lib/main.cpp -I ./include -o ./src/main.o
	g++ -c ./lib/editor.cpp -I ./include -o ./src/editor.o
	g++ -c ./lib/globals.cpp -I ./include -o ./src/globals.o
	g++ -c ./lib/player.cpp -I ./include -o ./src/player.o
	g++ -c ./lib/worldmap.cpp -I ./include -o ./src/worldmap.o
	g++ -c ./lib/mapeditor.cpp -I ./include -o ./src/mapeditor.o
	g++ ./src/main.o ./src/globals.o ./src/player.o ./src/worldmap.o -o ./src/app -lsfml-graphics -lsfml-window -lsfml-system
	g++ ./src/editor.o ./src/mapeditor.o ./src/player.o ./src/globals.o ./src/worldmap.o -o ./src/editor -lsfml-graphics -lsfml-window -lsfml-system


run:
	./src/app

editor-run:
	./src/editor