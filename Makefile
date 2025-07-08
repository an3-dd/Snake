all: main

main: main.cpp
	g++ main.cpp Board.cpp Game.cpp Apple.cpp Snake.cpp Menu.cpp Scriba.cpp -lncursesw -o main