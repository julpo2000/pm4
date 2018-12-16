all: othellobord.o hoofd.o
	g++ -Wall -o othello othellobord.o hoofd.o
othellobord.o: oth.cc oth.h
	g++ -Wall -c othellobord.cc
hoofd.o: hoofd.cc oth.h
	g++ -Wall -c hoofd.cc
