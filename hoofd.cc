//Opdracht 4 Programmeer methoden. Martin Krikke en Julian Poelsma (s2270935 en s2225387)
//Dit programma kan othello met zichzelf of tegen een persoon spelen. 
//Ook kunnen twee personen tegen elkaar spelen.
//Dit programma is gecodeerd met Microsoft Visual Studio. We hebben dus de standaard 
//Visual Studio compiler gebruikt, het werkt echter ook met de g++ compiler (versie 5.4.0).
//Doe alle drie de bestanden in een map en type "make" in de terminal om te compilen.
//Dit levert een programma dat met "./othello" uitgevoerd kan worden.

#include "othellobord.h"
int main()
{
	//infoblokje
	cout <<
		"************************************************************" << endl <<
		"* Dit programma is geschreven door:                        *" << endl <<
		"* Julian Poelsma, s2225387                                 *" << endl <<
		"* Martin Krikke, s2270935                                  *" << endl <<
		"* Wij zijn in 2018 gestart aan de studie Informatica       *" << endl <<
		"* Datum: 18/12/2018                                        *" << endl <<
		"*                                                          *" << endl <<
		"* In dit programma kan othello gespeelt worden.            *" << endl <<
		"************************************************************" << endl << endl;
		
	//random getallen
	srand(time(NULL));
	hoofdmenu();
}
