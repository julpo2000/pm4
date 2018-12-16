#include "pch.h"
#include <iostream>
using namespace std;

class oth{
private:
	
	//bordvakje* ingang;
	//bordvakje* maakrij();
	//bordvakje* ganaar();
	bool speler1, speler2; //mens of pc
	bool beurt;
	int aantalzetten;

public:
	int lengte;
	void lengteAanpassen();
	void print();
	void toevoegenVer();
	void toevoegenRij(class grid* begin);
	void verbinden(class grid* boven)
	void maakBord();
	void hoofdmenu();
	//othellobord(); //8 bij 8 of 0 bij 0
	void beginpositie();
	void verwijder();
	void gegevensvragen();
	void ritsen(); //bordvakje* boven, bordvakje* onder
	void doezet(); //vakje in coordinaten
	bool isgeldigezet();
	void computerzet();
	bool geldigezet();
	int klaar();
	void menszet();
	
	
}; //oth	
class grid{
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
	
int leesGetal();
int main();
