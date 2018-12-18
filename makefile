all: othellobord.o hoofd.o
	g++ -g -Wall -o othello othellobord.o hoofd.o
othellobord.o: othellobord.cc othellobord.h
	g++ -g -Wall -c othellobord.cc
hoofd.o: hoofd.cc othellobord.h
	g++ -g -Wall -c hoofd.cc
