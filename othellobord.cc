// pm4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib> //random
#include <ctime>
using namespace std;

int leesGetal() {
	int vorigGetal = -1; //als het getal stopt
	cin.get();
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


//het pointerbord
class grid {
public:
	//het getal dat erin staat
	int data;
	//de verwijzingen
	//windrichtingen voor duidelijkheid
	class grid* noord;
	class grid* noordoost;
	class grid* oost;
	class grid* zuidoost;
	class grid* zuid;
	class grid* zuidwest;
	class grid* west;
	class grid* noordwest;

};

class grid* head; //het begin

//nieuwe pointer aan pointerbord toevoegen
class grid* newItem(int x) {
	class grid* newItem = new grid;
	newItem->data = x;
	newItem->noord = 0;
	newItem->noordoost = 0;
	newItem->oost = 0;
	newItem->zuidoost = 0;
	newItem->zuid = 0;
	newItem->zuidwest = 0;
	newItem->west = 0;
	newItem->noordwest = 0;
	return newItem;
}

//pointerbord afdrukken
void print(int lengte) {
	//pointers om af te lopen
	class grid* tempHor = head;
	class grid* tempVer = head;
	
	//nummers aan de randen
	int teller = 0;
	cout << "  ";
	for (teller = 0; teller < lengte; teller++)
	{
		cout << teller << " ";
		tempHor = tempHor->oost;
	}
	cout << endl;
	//terugzetten
	tempHor = head;
	teller = 0;
	while (tempVer) {
		cout << teller << " ";
		while (tempHor) {
			//zwart
			if (tempHor->data == 1) {
				cout << "Z ";
			}
			//wit
			else if (tempHor->data == 2) {
				cout << "W ";
			}
			//iets anders dus leeg
			else {
				cout << "- ";
			}
			tempHor = tempHor->oost;
		}
		cout << endl;
		tempVer = tempVer->zuid;
		tempHor = tempVer;
		teller++;
	}

	cout << endl;
}

void toevoegenVer() {
	//pointertje om de lijst mee door te lopen
	class grid* vorige = head;
	//de nieuwe pointer
	class grid* nieuwe = newItem(0);

	//als de lijst leeg is wordt dit het eerste item
	if (head == NULL) {
		head = nieuwe;
		return;
	}
	//naar laatste pointer gaan
	while (vorige->zuid){
		vorige = vorige->zuid;
	}
	//nieuwe aanmaken
	vorige->zuid = nieuwe;

	//verbinden met noord
	nieuwe->noord = vorige;
}

void toevoegenRij(class grid* begin) {
	//de nieuwe pointer
	class grid* nieuwe = newItem(0);

	//meest oost
	while (begin->oost) {
		begin = begin->oost;
	}
	//nieuwe aanmaken
	begin->oost = nieuwe;

	//verbinden met west
	nieuwe->west = begin;
}

void verbinden(class grid* boven) {
	
	class grid* beneden = boven->zuid;
	
	//alle kollommen afgaan
	while (beneden) {
		//hulppointers
		class grid* tempBeneden = beneden;
		class grid* tempBoven = boven;

		//voor alle horizontale
		while (tempBoven) {
			//beneden naar boven
			tempBeneden->noord = tempBoven;
			tempBeneden->noordoost = tempBoven->oost;
			tempBeneden->noordwest = tempBoven->west;

			//boven naar beneden
			tempBoven->zuidoost = tempBeneden->oost;
			tempBoven->zuid = tempBeneden;
			tempBoven->zuidwest = tempBeneden->west;

			tempBoven = tempBoven->oost;
			tempBeneden = tempBeneden->oost;
		}
		//reset
		boven = beneden;
		beneden = beneden->zuid;
	}
}

void headVerbinden() {
	//omdat head speciaal is gebruiken we een speciale manier
	head->oost = head->zuidoost->noord;
}

void maakBord(int &lengte) {
	head = 0;
	//voor toevoegenRij
	class grid* tempVer;
	//0 zodat de while loop werkt
	lengte = 0;
	//minimaal 2 dus herhalen totdat 2
	while (lengte < 2 || lengte % 2) {
		cout << "Hoe groot moet het bord? Minimaal 2 en even." << endl;
		lengte = leesGetal();
	}
	 
	for (int i = 0; i < lengte; i++)
	{
		toevoegenVer();
	}
	tempVer = head;
	while (tempVer) {
		for (int k = 1; k < lengte; k++)
		{
			toevoegenRij(tempVer);
		}
		tempVer = tempVer->zuid;
	}
	verbinden(head);
	headVerbinden();	
}

class grid* pointerCo(int xCo, int yCo, int lengte) {
	//coordinaten in het bord
	xCo = xCo % lengte;
	yCo = yCo % lengte;

	//hulp pointer
	class grid* temp = head;
	for (int i = 0; i < yCo; i++)
	{
		temp = temp->zuid;
	}
	for (int i = 0; i < xCo; i++)
	{
		temp = temp->oost;
	}
	return temp;
}

void zetDoen(class grid* locatie, bool beurt) {
	//alle mogelijke opties afgaan en plaatsen als ze kunnen
	//hulp pointer
	class grid* tempLocatie;
	//waarde voor kijken
	int EigenWaarde;
	int TegenWaarde;
	int counter;
	if (beurt) {
		EigenWaarde = 1;
		TegenWaarde = 2;
	}
	else {
		EigenWaarde = 2;
		TegenWaarde = 1;
	}
	//voor elke richting kijken of het een mogelijke zet is
	//commentaar alleen bij noord. De rest werkt hetzelfde
	//noord
	//reset
	counter = 0;
	tempLocatie = locatie;
	//terwijl naar noord geen nulpointer is
	while (tempLocatie->noord)
	{
		//alle andere waarden afgaan
		while (tempLocatie->noord->data == TegenWaarde) {
			tempLocatie = tempLocatie->noord;
			//counter zodat er minimaal 1 TegenWaarde is gevonden
			counter++;
			//afbreken als er een nul pointer is
			if (tempLocatie->noord == 0) {
				break;
			}
		}
		//kijken voor nul pointers
		if (tempLocatie->noord == 0) {
			break;
		}
		//als EigenWaarde en minimaal 1 Tegenwaarde gevonden
		else if (tempLocatie->noord->data == EigenWaarde && counter) {
			//in omgekeerde richting  terug gaan naar het begin punt
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->zuid;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		//afbreken tegen nul pointers
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//noordoost
	while (tempLocatie->noordoost)
	{
		while (tempLocatie->noordoost->data == TegenWaarde) {
			tempLocatie = tempLocatie->noordoost;
			counter++;
			if (tempLocatie->noordoost == 0) {
				break;
			}
		}
		if (tempLocatie->noordoost == 0) {
			break;
		}
		else if (tempLocatie->noordoost->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->zuidwest;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//oost
	while (tempLocatie->oost)
	{
		while (tempLocatie->oost->data == TegenWaarde) {
			tempLocatie = tempLocatie->oost;
			counter++;
			if (tempLocatie->oost == 0) {
				break;
			}
		}
		if (tempLocatie->oost == 0) {
			break;
		}
		else if (tempLocatie->oost->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->west;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//zuidoost
	while (tempLocatie->zuidoost)
	{
		while (tempLocatie->zuidoost->data == TegenWaarde) {
			tempLocatie = tempLocatie->zuidoost;
			counter++;
			if (tempLocatie->zuidoost == 0) {
				break;
			}
		}
		if (tempLocatie->zuidoost == 0) {
			break;
		}
		else if (tempLocatie->zuidoost->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->noordwest;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//zuid
	while (tempLocatie->zuid)
	{
		while (tempLocatie->zuid->data == TegenWaarde) {
			tempLocatie = tempLocatie->zuid;
			counter++;
			if (tempLocatie->zuid == 0) {
				break;
			}
		}
		if (tempLocatie->zuid == 0) {
			break;
		}
		else if (tempLocatie->zuid->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->noord;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//zuidwest
	while (tempLocatie->zuidwest)
	{
		while (tempLocatie->zuidwest->data == TegenWaarde) {
			tempLocatie = tempLocatie->zuidwest;
			counter++;
			if (tempLocatie->zuidwest == 0) {
				break;
			}
		}
		if (tempLocatie->zuidwest == 0) {
			break;
		}
		else if (tempLocatie->zuidwest->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->noordoost;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//west
	while (tempLocatie->west)
	{
		while (tempLocatie->west->data == TegenWaarde) {
			tempLocatie = tempLocatie->west;
			counter++;
			if (tempLocatie->west == 0) {
				break;
			}
		}
		if (tempLocatie->west == 0) {
			break;
		}
		else if (tempLocatie->west->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->oost;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}

	counter = 0;
	tempLocatie = locatie;
	//noordwest
	while (tempLocatie->noordwest)
	{
		while (tempLocatie->noordwest->data == TegenWaarde) {
			tempLocatie = tempLocatie->noordwest;
			counter++;
			if (tempLocatie->noordwest == 0) {
				break;
			}
		}
		if (tempLocatie->noordwest == 0) {
			break;
		}
		else if (tempLocatie->noordwest->data == EigenWaarde && counter) {
			while (tempLocatie != locatie)
			{
				tempLocatie->data = EigenWaarde;
				tempLocatie = tempLocatie->zuidoost;
			}
			tempLocatie->data = EigenWaarde;
			break;
		}
		else {
			break;
		}
	}
}

void veranderData(class grid* temp, int waarde) {
	temp->data = waarde;
}

void beginPositie(int lengte) {
	//het midden
	int co = lengte / 2;
	//wit
	veranderData(pointerCo(co, co, lengte), 2);
	co--;
	veranderData(pointerCo(co, co, lengte), 2);

	//zwart
	veranderData(pointerCo(co+1, co, lengte), 1);
	veranderData(pointerCo(co, co+1, lengte), 1);
}

bool beurtValid(bool beurt, class grid* locatie) {
	//hulp pointer
	class grid* tempLocatie;
	//waarde voor kijken
	int EigenWaarde;
	int TegenWaarde;
	int counter;
	if (beurt) {
		EigenWaarde = 1;
		TegenWaarde = 2;
	}
	else {
		EigenWaarde = 2;
		TegenWaarde = 1;
	}
	//de plek moet leeg zijn
	if (locatie->data != 0) {
		return 0;
	}
	//voor elke richting kijken of het een mogelijke zet is
	//commentaar alleen bij noord. De rest werkt hetzelfde
	//noord
	//reset
	counter = 0;
	tempLocatie = locatie;
	//terwijl naar noord geen nulpointer is
	while (tempLocatie->noord)
	{
		//alle andere waarden afgaan
		while (tempLocatie->noord->data == TegenWaarde) {
			tempLocatie = tempLocatie->noord;
			//counter zodat er minimaal 1 TegenWaarde is gevonden
			counter++;
			//afbreken als er een nul pointer is
			if (tempLocatie->noord == 0) {
				break;
			}
		}
		//kijken voor nul pointers
		if (tempLocatie->noord == 0) {
			break;
		}
		//als EigenWaarde en minimaal 1 Tegenwaarde gevonden
		else if (tempLocatie->noord->data == EigenWaarde && counter) {
			//Deze plek is toegestaan
			return 1;
		}
		//afbreken tegen nul pointers
		else {
			break;
		}
	}

	//oost
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->oost)
	{
		while (tempLocatie->oost->data == TegenWaarde) {
				tempLocatie = tempLocatie->oost;
				counter++;
				if (tempLocatie->oost == 0) {
					break;
				}
		}
		if (tempLocatie->oost == 0) {
			break;
		}
		else if (tempLocatie->oost->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//zuid
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->zuid)
	{
		while (tempLocatie->zuid->data == TegenWaarde) {
				tempLocatie = tempLocatie->zuid;
				counter++;
				if (tempLocatie->zuid == 0) {
					break;
				}
		}
		if (tempLocatie->zuid == 0) {
			break;
		}
		else if (tempLocatie->zuid->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}	
	
	//west
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->west)
	{
		while (tempLocatie->west->data == TegenWaarde) {
			tempLocatie = tempLocatie->west;
			counter++;
			if (tempLocatie->west == 0) {
				break;
			}
		}
		if (tempLocatie->west == 0) {
			break;
		}
		else if (tempLocatie->west->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//noordoost
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->noordoost)
	{
		while (tempLocatie->noordoost->data == TegenWaarde) {
			tempLocatie = tempLocatie->noordoost;
			counter++;
			if (tempLocatie->noordoost == 0) {
				break;
			}
		}
		if (tempLocatie->noordoost == 0) {
			break;
		}
		else if (tempLocatie->noordoost->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//zuidoost
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->zuidoost)
	{
		while (tempLocatie->zuidoost->data == TegenWaarde) {
			tempLocatie = tempLocatie->zuidoost;
			counter++;
			if (tempLocatie->zuidoost == 0) {
				break;
			}
		}
		if (tempLocatie->zuidoost == 0) {
			break;
		}
		else if (tempLocatie->zuidoost->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//zuidwest
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->zuidwest)
	{
		while (tempLocatie->zuidwest->data == TegenWaarde) {
			tempLocatie = tempLocatie->zuidwest;
			counter++;
			if (tempLocatie->zuidwest == 0) {
				break;
			}
		}
		if (tempLocatie->zuidwest == 0) {
			break;
		}
		else if (tempLocatie->zuidwest->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//noordwest
	counter = 0;
	tempLocatie = locatie;
	while (tempLocatie->noordwest)
	{
		while (tempLocatie->noordwest->data == TegenWaarde) {
			tempLocatie = tempLocatie->noordwest;
			counter++;
			if (tempLocatie->noordwest == 0) {
				break;
			}
		}
		if (tempLocatie->noordwest == 0) {
			break;
		}
		else if (tempLocatie->noordwest->data == EigenWaarde && counter) {
			return 1;
		}
		else {
			break;
		}
	}

	//als de beurt niet kan
	return 0;
}

void beurtDoenMens(bool &beurt, int lengte) {
	if (beurt) {
		cout << "Zwart is aan de beurt" << endl;
	}
	else {
		cout << "Wit is aan de beurt" << endl;
	}
	//optie om te selecteren
	cout << "Mogelijke opties zijn:" << endl;
	for (int i = 0; i < lengte; i++)
	{
		for (int k = 0; k < lengte; k++)
		{
			if (beurtValid(beurt, pointerCo(i, k, lengte))) {
				cout <<"X=" << i << " Y=" << k << endl;
			}			
		}
	}
	cout << "Voer de X in van uw optie: ";
	int xCo = leesGetal();
	cout << "Voer de Y in van uw optie: ";
	int yCo = leesGetal();
	if (beurtValid(beurt, pointerCo(xCo, yCo, lengte))) {
		zetDoen(pointerCo(xCo, yCo, lengte), beurt);
		if (beurt) {
			beurt = 0;
		}
		else {
			beurt = 1;
		}
	}
	else {
		cout << "Dat is geen mogelijke zet" << endl;
	}
}

void beurtDoenPC(bool &beurt, int lengte){
	//beurtDoenMens maar dan zonder informatie vragen
	if (beurt) {
		cout << "Zwart deed ";
	}
	else {
		cout << "Wit deed ";
	}
	//random coordinaten
	int xCo = rand();
	int yCo = rand();
	//net zolang random tot er een mogelijke optie is
	while (beurtValid(beurt, pointerCo(xCo, yCo, lengte)) == 0) {
		xCo = rand();
		yCo = rand();
	}
	cout << "X=" << xCo % lengte << " Y=" << yCo % lengte << endl;
	zetDoen(pointerCo(xCo, yCo, lengte), beurt);
	if (beurt) {
		beurt = 0;
	}
	else {
		beurt = 1;
	}

}

int telPunten(int kleur, int lengte) {
	//tellen hoeveel punten
	int counter = 0;
	for (int i = 0; i < lengte; i++)
	{
		for (int k = 0; k < lengte; k++)
		{
			if (pointerCo(i, k, lengte)->data == kleur) {
				counter++;
			}
		}
	}
	return counter;
}

void eindeBepalen(bool beurt, int lengte) {
	//als bord vol is
	bool NulGevonden = false;
	for (int i = 0; i < lengte; i++)
	{
		for (int k = 0; k < lengte; k++)
		{
			//als er een leeg vak is
			if (pointerCo(i, k, lengte)->data == 0) {
				NulGevonden = true;
			}
		}
	}
	if (NulGevonden) {
		if (beurt) {
			cout << "Wit wint omdat zwart niet kan!" << endl;
		}
		else {
			cout << "Zwart wint omdat wit niet kan!" << endl;
		}
	}
	//als bord leeg is
	else {
		//declaratie hier voorkomt onnodig declareren
		int WitPunten = telPunten(2, lengte);
		int ZwartPunten = telPunten(1, lengte);
		if (WitPunten < ZwartPunten) {
			cout << "Zwart wint met " << ZwartPunten <<
				" tegen wit met " << WitPunten << " punten." << endl;
		}
		else if (WitPunten > ZwartPunten) {
			cout << "Wit wint met " << WitPunten <<
				" punten tegen zwart met " << ZwartPunten << " punten." << endl;
		}
		else {
			cout << "Het is gelijkspel. Beide spelers hebben " << ZwartPunten <<
				" punten gehaald." << endl;			
		}
	}
}

void verwijder() {
	//hulp pointer
	class grid* temp = head;
	//naar verste pointer
	while (temp->zuidoost) {
		temp = temp->zuidoost;
	}
	//nog een hulp pointer
	class grid* eentjeTerug = temp->west;
	while (eentjeTerug->noord)
	{
		while (eentjeTerug->west) {
			delete temp->oost;
			delete temp->zuidoost;
			delete temp->zuid;
			delete temp->zuidwest;

			temp->oost = 0;
			temp->zuidoost = 0;
			temp->zuid = 0;
			temp->zuidwest = 0;
			temp = eentjeTerug;
			eentjeTerug = eentjeTerug->west;
		}
		temp = eentjeTerug;
		eentjeTerug = eentjeTerug->noord;
	}
}//verwijder

void spelen(bool beurt, int lengte, bool ZwartPC, bool WitPC) {
	int beurtMogelijk = 1;
	while (beurtMogelijk) {
		//alle mogelijke opties afgaan
		if (beurt && ZwartPC) {
			beurtDoenPC(beurt, lengte);
		}
		else if (beurt == 0 && WitPC) {
			beurtDoenPC(beurt, lengte);
		}
		else if (beurt == 0 && WitPC==0) {
			beurtDoenMens(beurt, lengte);
		}
		else if (beurt && ZwartPC == 0) {
			beurtDoenMens(beurt, lengte);
		}
		
		//mooie opmaak
		cout << endl;
		print(lengte);
		beurtMogelijk = 0;
		for (int i = 0; i < lengte; i++)
		{
			for (int k = 0; k < lengte; k++)
			{
				if (beurtValid(beurt, pointerCo(i, k, lengte))) {
					beurtMogelijk = 1;
				}
			}
		}
	}
	eindeBepalen(beurt, lengte);
	verwijder();
}
void startSpel() {
	int lengte;
	bool beurt = true;
	//wit = 0, zwart = 1;
	bool ZwartPC;
	bool WitPC;
	cout << "Is Zwart een mens[0] of een computer[1]?" << endl;
	cin >> ZwartPC; 
	cout << "Is Wit een mens[0] of een computer[1]?" << endl;
	cin >> WitPC;
	maakBord(lengte);
	beginPositie(lengte);
	print(lengte);
	spelen(beurt, lengte, ZwartPC, WitPC);
}

void hoofdmenu() {
	char menuinput;
	bool loop = true;
	while (loop) {
		cout << "[S]tart spel   [A]fsluiten" << endl;
		cin >> menuinput;
		switch (menuinput) {
		case 's': 
		case 'S': { startSpel(); break; };
		case 'a':
		case 'A': { loop = false; break; };
		default: { cout << "geen geldige input." << endl; break; }
		}//switch
	}
}//hoofdmenu
