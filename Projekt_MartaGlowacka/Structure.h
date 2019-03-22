#pragma once
#include <string>

class Structure
{
	//Rozmiar stuktury, zmienna stworzona po to, by funkcja int getSize by³a wirtualna
	unsigned size;

protected:
	//Kolor ustawiany w menu strukturze
	int color;
	//Nazwa ustawiana w menu strukturze
	std::string name;
public:
	Structure();
	virtual ~Structure();

	virtual void display() = 0; //dla wszystkich struktur = dws
	virtual int readFromFile() = 0; //dws
	virtual int saveToFile() = 0; //dws
	virtual int push(int val) = 0; //dws
	virtual int pop() = 0; //dws
	virtual bool seek(int val) = 0; //dws
	virtual int push_selected(int index, int val) { return 0; }; // tab
	virtual int pop_selected(int index) { return 0; }; //listy i tab
	virtual int push_back(int val) { return 0; };//listy i tab
	virtual int pop_back() { return 0; }; //listy i tab
	virtual bool generateRandomData(int structureSize, int minIndex, int maxIndex) = 0; //dws
	virtual int getSize() { return size; }
	virtual int getColor() {return color; }
	virtual std::string getName() { return name; }
	virtual int randomValue(int minIndex, int maxIndex) = 0;

};



