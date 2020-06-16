CC=g++ 
CPPFLAGS=-g -O3 -Wall -std=c++14

gratacels: main.o Solucionador.o Solucio.o Candidats.o
	$(CC) -o gratacels main.o Solucionador.o Solucio.o Candidats.o
main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp
Solucionador.o: Solucionador.cpp Solucionador.h
	$(CC) $(CPPFLAGS) -c Solucionador.cpp
Solucio.o: Solucio.cpp Solucio.h
	$(CC) $(CPPFLAGS) -c Solucio.cpp
Candidats.o: Candidats.cpp Candidats.h
	$(CC) $(CPPFLAGS) -c Candidats.cpp
