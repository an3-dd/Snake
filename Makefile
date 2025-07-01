all: main

main: main.cpp
	g++ -Wall main.cpp Board.cpp Game.cpp Apple.cpp Snake.cpp -lncursesw -o main