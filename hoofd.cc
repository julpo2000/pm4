#include "oth.h"
#include <iostream>
//random
#include <cstdlib> 
#include <ctime>
using namespace std;

int leesGetal() {
	int vorigGetal = -1; //als het getal stopt
	int input = cin.get();
	while (input != 10) //tot enter
	{
		if (input > 47 && input < 58) { //als getal
			int inputGetal = input - '0';
			if (vorigGetal == -1) { //als er geen getal voorstond
				vorigGetal = inputGetal;
			}
			else { //als er wel een getal voorstond
				vorigGetal = vorigGetal * 10 + inputGetal;
			}
		}
		input = cin.get();
	}
	return vorigGetal; //geef getal terug
	vorigGetal = -1;
}//inputNumber

int main(){
	//infoblokje
	cout <<
		"************************************************************" << endl <<
		"* Dit programma is geschreven door:                        *" << endl <<
		"* Julian Poelsma, s2225387                                 *" << endl <<
		"* Martin Krikke, s2270935                                  *" << endl <<
		"* Wij zijn in 2018 gestart aan de studie Informatica       *" << endl <<
		"* Datum: 12/11/2018                                        *" << endl <<
		"*                                                          *" << endl <<
		"* In dit programma kan othello gespeeld worden.            *" << endl <<
		"************************************************************" << endl << endl;
		
	//random getallen
	srand(time(NULL));
	oth o;
	//o.lengteAanpassen();
} //main
