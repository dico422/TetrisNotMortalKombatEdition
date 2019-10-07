main.out: Tetris.o jogoTetris.o Menu.o
	g++ Tetris.o jogoTetris.o Menu.o  -lglut -lGLU -lGL
	rm *.o

Tetris.o:
	g++ -c Tetris.cpp

jogoTetris.o:
	g++ -c jogoTetris.cpp
	
Menu.o:
	g++ -c Menu.cpp
