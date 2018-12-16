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
int leesGetal();
