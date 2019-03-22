#pragma once
#include "Structure.h"

struct listEl {
	listEl *prev, *next;
	int data;
};


class List : public Structure
{
private:
	unsigned size;
	//Pojedynczy element na liscie
	listEl *head, *tail;
	
public:
	List();
	~List();
	void display() override;
	int readFromFile(); 
	int saveToFile(); 
	int push(int val) override; 
	int push_back(int val);
	int push_selected(listEl *element, int val); 
	int pop() override; 
	int pop_back(); 
	int pop_selected(listEl *element); 
	bool seek(int val) ; 
	int getSize() override { return size; }
	bool generateRandomData(int structureSize, int minIndex, int maxIndex) override;
	int randomValue(int minIndex, int maxIndex) override;

	listEl* convertIndextToEl(int i);

};


