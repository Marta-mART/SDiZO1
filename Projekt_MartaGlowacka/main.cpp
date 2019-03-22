#include <iostream>
#include <windows.h>
#include "Menu.h"
#include <ctime>
using namespace std;

//Marta G�owacka 234999

int main()
{
	srand(time(NULL));

	// Utworzenie klasy Menu oraz utworzenie pocz�tkowego menu
	Menu mainMenu;
	// Wybor opcji w menu wskazywanej przez uzytkownika
	int structureChoice;

	// P�tla jest wykonywana dop�ki user nie wci�nie przycisku wyjscia, czyli 5
	do
	{
		// Wy�wietlenie menu g��wnego
		mainMenu.displayMainMenu();

		// Wczytanie wyboru usera z menu		
		structureChoice = mainMenu.getInput(1, 5);
			
		// Kolejne menu: wybrana struktura
		//(zabezpieczenie przez wyj�tkiem)
		if (structureChoice != 5) mainMenu.displayStructureMenu(structureChoice);
		

	} while (structureChoice != 5);

	system("PAUSE");
	return EXIT_SUCCESS;
}