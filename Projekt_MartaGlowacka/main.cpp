#include <iostream>
#include <windows.h>
#include "Menu.h"
#include <ctime>
using namespace std;

//Marta G³owacka 234999

int main()
{
	srand(time(NULL));

	// Utworzenie klasy Menu oraz utworzenie pocz¹tkowego menu
	Menu mainMenu;
	// Wybor opcji w menu wskazywanej przez uzytkownika
	int structureChoice;

	// Pêtla jest wykonywana dopóki user nie wciœnie przycisku wyjscia, czyli 5
	do
	{
		// Wyœwietlenie menu g³ównego
		mainMenu.displayMainMenu();

		// Wczytanie wyboru usera z menu		
		structureChoice = mainMenu.getInput(1, 5);
			
		// Kolejne menu: wybrana struktura
		//(zabezpieczenie przez wyj¹tkiem)
		if (structureChoice != 5) mainMenu.displayStructureMenu(structureChoice);
		

	} while (structureChoice != 5);

	system("PAUSE");
	return EXIT_SUCCESS;
}