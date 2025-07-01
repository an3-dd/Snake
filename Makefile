all: main

main: main.cpp
	g++ -Wall main.cpp Board.cpp Game.cpp Apple.cpp Snake.cpp Menu.cpp Scriba.cpp -lncursesw -o main