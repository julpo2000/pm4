// pm4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
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

/*
void hoofdmenu()
{
	bool again = true;
	while (again) {
		cout << "s[c]hoon, c[u]rsor, [r]andom, [n]ul, [i]nlezen, w[e]gschrijven, [w]ijzigen, [q]stoppen, [b]eschrijving, [p]rinten" << endl;
		char menuinput = cin.get();
		switch (menuinput) {
		case 'c': { test(); break; }
		case 'q': {again = false; break; }
		default: { break; }
		}//switch
		cin.get(); //Als er op enter wordt gedrukt gaat hij terug naar het hoofdmenu
	}

	//int hoofdmenu();
	//hoofdmenu();
}//hoofdmenu
*/

//het pointerboord
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
void print() {
	//pointers om af te lopen
	class grid* tempHor = head;
	class grid* tempVer = head;
	while (tempVer) {
		while (tempHor) {
			cout << tempHor->data << " ";
			tempHor = tempHor->oost;
		}
		cout << endl;
		tempVer = tempVer->zuid;
		tempHor = tempVer;
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
	while (beneden->zuid) {
		//hulppointers
		class grid* tempBeneden = beneden;
		class grid* tempBoven = boven;

		//voor alle horizontale
		while (tempBoven->oost) {
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
		boven = beneden;
		beneden = beneden->zuid;
	}
	
	
}

void maakBord() {
	head = 0;
	//voor toevoegenRij
	class grid* tempVer;
	cout << "Hoe groot moet het bord? Minimaal 2." << endl;
	int lengte = leesGetal();
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
	print();
	
}

int main()
{
	//hoofdmenu();
	maakBord();
	head->zuidoost->zuidoost->noordoost->data = 5;
	cout << head->zuidoost->zuidoost->noordoost->data << endl;
	print();
}
