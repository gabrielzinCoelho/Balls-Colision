all: compile link

compile:
	g++ -Isrc/include -c ball.cpp
	g++ -Isrc/include -c stateBalls.cpp
	g++ -Isrc/include -c gameState.cpp
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o ball.o stateBalls.o gameState.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system