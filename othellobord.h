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
	int telPunten();
	int lengte;
	void toevoegenVer();
	void toevoegenRij();
	void verbinden();
	void headVerbinden();
	void veranderData();
	//othellobord(); //8 bij 8 of 0 bij 0
	//void verwijder();
	void zetDoen();
	bool beurtValid();
	void beurtDoenMens();
	void beurtDoenPC();
	void hoofdmenu();
	void eindeBepalen();	
	
}; //oth	
class grid{
public:
	//het getal dat erin staat
	int data;
	class grid* head; //het begin
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
	//nieuwe pointer aan pointerbord toevoegen
	class grid* newItem(int x);
	class grid* pointerCo();

};//grid
	
int leesGetal();
int main();
void hoofdmenu();
void print(int lengte);
void maakBord(int &lengte);
void beginPositie(int lengte);
void spelen(bool beurt, int lengte, bool ZwartPC, bool WitPC);

