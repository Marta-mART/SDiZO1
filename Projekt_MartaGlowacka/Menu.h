#pragma once

class Menu
{
	int structureChoice;
	float average(int numberOfTests);
	void sum(float timeVal);
	void myTestingFunction();
public:
	Menu();
	~Menu();
	int getInput(int numberOfFirstOption, int numberOfLastOption);
	void displayMainMenu();
	void displayStructureMenu(int structureChoice);
	int getIndex();
	int getValue();


	void saveToFile(std::string name, double value, int numberOfTests);
	void displayAdjustedOtions(int structureChoice);
	void test();

};

