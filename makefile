all: oth.o hoofd.o
	g++ -Wall -o othello oth.o hoofd.o
oth.o: oth.cc oth.h
	g++ -Wall -c oth.cc
hoofd.o: hoofd.cc oth.h
	g++ -Wall -c hoofd.cc
