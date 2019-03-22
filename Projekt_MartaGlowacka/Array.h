#pragma once
#include "Structure.h"

class Array : public Structure
{
private:
	unsigned size;
	int *tab;

public:
	Array();
	~Array();
	void display() override;
	int readFromFile();
	int saveToFile(); 
	int push(int val) override; 
	int push_back(int val); 
	int push_selected(int index, int val);
	int pop() override; 
	int pop_back(); 
	int pop_selected(int index); 
	bool seek(int val); 
	int getSize() override { return size; }
	bool generateRandomData(int structureSize, int minIndex, int maxIndex) override;
	int randomValue(int minIndex, int maxIndex) override;
};

