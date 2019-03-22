#pragma once
#include "Structure.h"

class Heap : public Structure
{
private:
	unsigned size;
	int *tab;
	//Flaga dla funkcji rekurencyjnej wyszukuj¹cej
	bool found;

	//Znaczniki do wyœwietlania kopca
	std::string s;
	std::string cr, cl, cp;

	//Prywatne metody
	void resizeTab();
	void reduceTab();
	void sort();
	void swap(int &a, int &b);

	//Rekurencyjna funkcja do wyœwietlania
	void printHeap(std::string sp, std::string sn, int val);

	//funkcja rekurencyjna do szukania wartosci
	bool seekRek(int i, int val);
public:
	Heap();
	~Heap();
	void display();
	int readFromFile(); 
	int saveToFile(); 
	int push(int val) override; 
	int pop() override; 
	bool seek(int val);
	int getSize() override { return size; }
	bool generateRandomData(int structureSize, int minIndex, int maxIndex) override;
	int randomValue(int minIndex, int maxIndex) override;

};

