#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include "Menu.h"
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "RBTree.h"
#include "Watch.h"

using namespace std;


//Zmienne globalne
	//wskaznik na strukture (polimorfizm)
	Structure *structure;
	//wartosc dodawana do tablicy
	int value;
	//indeks miejsca, na ktorym chcemy wykonac operacje w strukturze
	int i;
	//zmienna pilnujaca, by struktura utworzyla sie raz w funkcji samowywolujacej sie
	bool firstTime;

	//Wskaznik pomocniczy, przydatny przy rzutowaniu
	List *a;
	//Wskaznik pomocniczy, przydatny przy rzutowaniu
	Heap *b;
	//Wskaznik pomocniczy, przydatny przy rzutowaniu
	RBTree *c;

	//ile opcji menu dla kazdej struktury
	//dla array i list
	const unsigned numberOfOptionAL = 14;
	//dla heap i tree
	const unsigned numberOfOptionHT = 8;

	//Tablica z opcjami w menu
	string tabOption[numberOfOptionAL];

	//Zegar
	Watch myClock;

	//Zmienne do liczenia sumy i sredniej do testu jednorazowego
	float suma, srednia;

Menu::Menu()
{
	firstTime = true;
	
	tabOption[0] = "Stworz strukture, wczytujac z pliku";
	tabOption[1] = "Zapis struktury do pliku";
	tabOption[2] = "Dodaj element";
	tabOption[3] = "Usun element";
	tabOption[4] = "Wyszukaj element";
	tabOption[5] = "Generuj dane losowe z przedzialu";
	tabOption[6] = "Rozpocznij test";
	tabOption[7] = "Powrot";

	tabOption[8] = "Dodaj element na koniec";
	tabOption[9] = "Usun element z konca";
	tabOption[10] = "Dodaj element w losowe miejsce";
	tabOption[11] = "Dodaj element w wybrane miejsce";
	tabOption[12] = "Usun element z losowego miejsca";
	tabOption[13] = "Usun wybrany element";
}

Menu::~Menu()
{
}

int Menu::getIndex()
{
	int index = 0;
	// Pobranie indeksu od usera
	std::cout << "Podaj indeks:" << endl;
	cin >> index;

	return index;
}

int Menu::getValue()
{
	int val = 0;
	// Pobranie indeksu od usera
	cout << "Podaj wartosc:" << endl;
	cin >> val;

	return val;
}

int Menu::getInput(int numberOfFirstOption, int numberOfLastOption)
{
	// Pobranie wyboru opcji usera
	int choice;
	cout << "Wybor: ";
	cin >> choice;
	
	// Zabezpieczenie przed podaniem stringa lub numeru opcji, która nie istnieje w menu
	while (!cin || choice > numberOfLastOption || choice < numberOfFirstOption)
	{
		cout << "Nie podano cyfry z przedzialu " << numberOfFirstOption << "-" << numberOfLastOption << ". Podaj prawidlowa wartosc: ";
		cin.clear();
		cin.ignore();
		cin >> choice;
	}

	// Zwraca wybor usera
	return choice;
}

void Menu::displayMainMenu()
{
	system("cls");
	// Zmiana koloru czcionki
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	// Wypisanie tytu³u
	cout << endl;
	cout << "----------------" << endl;
	cout << "STRUKTURY DANYCH" << endl;
	cout << "----------------" << endl;

	// Zmiana koloru czcionki
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	// Wyswietlenie opcji - wybór struktury
	cout << endl << "MENU GLOWNE: \n";
	cout << "-------------------------------\n";
	cout << "1. Tablica \n";
	cout << "2. Lista dwukierunkowa \n";
	cout << "3. Kopiec binarny \n";
	cout << "4. Drzewo czerwono-czarne \n";
	cout << "5. Koniec programu \n";
	cout << "-------------------------------\n";
}

void Menu::saveToFile(std::string name, double value, int numberOfTests)
{
	// Zamienna do zapisu w pliku
	ofstream plik;

	// Otorzenie pliku do zapisu
	plik.open(name, ios::app | ios::out);

	// Jeœli b³¹d, wyœwietl komunikat
	if (plik.bad() || plik.fail())
	{
		exit(-1);
	}
	else
	{
		plik << value << endl;
	}

	// Zamkniêcie strumienia.
	plik.close();
	plik.clear();

}

void Menu::displayAdjustedOtions(int structureChoice)
{
	// Zmiana koloru czcionki
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	// Wyswietlenie opcji - wybór struktury
	cout << endl << "WYBIERZ OPERACJE: \n";
	cout << "-------------------------------\n";
	
	int sizeOfOptions = ((structureChoice == 1 || structureChoice == 2) ? numberOfOptionAL : numberOfOptionHT);

	//Wyœwietlenie opcji meny zapisanych w tablicy
	for (int i = 0; i < sizeOfOptions; i++)
	{
		cout << i + 1 << ". ";
		cout << tabOption[i];
				

		if (structureChoice == 1 || structureChoice == 2)
		{
			if (i == 2) cout << " na poczatek";
			if (i == 3) cout << " z poczatku";
			if (i == 7)
			{
				cout << endl << endl;
				cout << "DODATKOWE FUNKCJE DLA TABLICY LUB LISTY:" << endl;
			}
		}
		cout << endl;
			
	}

	cout << "-------------------------------\n";
}

void Menu::displayStructureMenu(int structureChoice)
{
		//Tworzenie struktury - jeden raz - zale¿nie od wyboru usera ustawiamy wskaznik
		//Wskaznik klasy bazowej alokuje miejsce na strukture wybranego typu
		if (firstTime)
		{
			this->structureChoice = structureChoice;
			// Zale¿ne od indeksu podanego przez usera, tworzymy 
			//tablice
			if (structureChoice == 1) structure = new Array();
			//liste
			else if (structureChoice == 2) structure = new List();
			//kopiec
			else if (structureChoice == 3) structure = new Heap();
			//drzewo czerwono-czarne
			else if (structureChoice == 4) structure = new RBTree();

			firstTime = false;
		}

		//wybor usera w nowym menu, dla struktury
		int choice = 0;	
	
		// Zmiana koloru czcionki
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), structure->getColor());

		system("cls");
		// Wypisanie tytu³u
		cout << endl;
		cout << "--------------------------" << endl;
		cout << structure->getName() << endl;
		cout << "--------------------------" << endl;

		//Wyswietlenie odpowiednich opcji, zaleznie od wybranej struktury
		displayAdjustedOtions(structureChoice);
				
		// Zmiana koloru czcionki
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), structure->getColor());

		// Wyœwietlanie tablicy
		structure->display();

		// Zmiana koloru czcionki
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


		// Pobieranie ze strumieia wejscia wybor usera
		// Dla tablicy i listy jest wiecej opcji w menu
		if(structureChoice == 1 || structureChoice == 2) choice = getInput(1, numberOfOptionAL);
		else if(structureChoice == 3 || structureChoice == 4) choice = getInput(1, numberOfOptionHT);

		//Ustawienie prezycji wyswietlania liczb - przydatne do mierzenia czasu
		cout.precision(2);

		switch (choice)
		{
			case 1: // TWORZENIE
				{ 
					try
					{
						structure->readFromFile();
						cout << "\nUtworzono strukture";
					}
					catch (int exception)
					{
						if(exception == 1) cout << "Blad tworzenia struktury. Podano zly plik." << endl;
						if(exception == 3) cout << "Nie mozna wczytac ponownie pliku." << endl;
					}
					
					Sleep(1000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 2: //ZAPIS DO PLIKU
				{
					try
					{
						structure->saveToFile();
						cout << "Nastapi zapis danych do pliku. " << endl;
					}
					catch (int exception)
					{
						if(exception == 1) cout << "Blad otwarcia pliku do zapisu. " << endl;
					}
				
					Sleep(2000); 		
					displayStructureMenu(structureChoice);
				}
				break;
			case 3: //DODAJ ELEMENT NA POCZ
				{
					try
					{
						value = getValue();

						// Wgraj czas pocz¹tkowy
						myClock.start();

						structure->push(value);
							
						// Wgraj czas koñcowy
						myClock.stop();

						if (structureChoice == 4)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							c = dynamic_cast<RBTree*>(structure);
							c->balance();
							c = nullptr;
						}

						std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";

						cout << "Dodawanie watosci." << endl;
					}
					catch (int exception)
					{
						if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 9: //DODAJ EL NA KONIEC
				{		
					try
					{
						value = getValue();
						// Wgraj czas pocz¹tkowy
						myClock.start();
						
						structure->push_back(value);

						// Wgraj czas koñcowy
						myClock.stop();
						
						std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						cout << "Dodawanie wartosci na koniec" << endl;
					}
					catch (int exception) 
					{
						if(exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
					}
					
					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 11: //DODAJ ELEMENT W LOSOWE MIEJSCE
				{
					try
					{ 
						//Losowanie wartosci
						value = getValue();
						i = rand() % (structure->getSize() + 1);
						if (structureChoice == 1)
						{
							// Wgraj czas pocz¹tkowy
							myClock.start();

							structure->push_selected(i, value);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						}
						else if (structureChoice == 2)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							a = dynamic_cast<List*>(structure);

							// Wgraj czas pocz¹tkowy
							myClock.start();

							a->push_selected(a->convertIndextToEl(i), value);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
							//Powstaly wskaznik wyzerowac, zeby dwa wskazniki nie wskazywaly na to samo miejsce w pamieci
						
							a = nullptr;
						}

						cout << "Dodawanie wartosci w miejsce o indeksie " << i << endl;
					}
					catch (int exception)
					{
						if (exception == -1) cout << "Blad tworzenia nowej struktury!" << endl;
					}
					
					Sleep(2000);
					displayStructureMenu(structureChoice);
					
				}
				break;
			case 12: //DODAJ ELEMENT W WYBRANE MIEJSCE
				{
					try
					{
						i = getIndex();
						value = getValue();
						if (structureChoice == 1)
						{
							// Wgraj czas pocz¹tkowy
							myClock.start();

							structure->push_selected(i, value);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						}
						else if (structureChoice == 2)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							a = dynamic_cast<List*>(structure);

							// Wgraj czas pocz¹tkowy
							myClock.start();

							a->push_selected(a->convertIndextToEl(i), value);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";

							//Powstaly wskaznik wyzerowac, zeby dwa wskazniki nie wskazywaly na to samo miejsce w pamieci
							
							a = nullptr;
						}
						cout << "Dodawanie wartosci w miejsce o indeksie " << i << endl;
					}
					catch (int exception)
					{
						if (exception == -1) cout << "Blad - podane zla wartosc!" << endl;
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);

				}
				break;
			case 4: //USUN ELEMENT POCZATEK
				{
					try
					{
						// Wgraj czas pocz¹tkowy
						myClock.start();

						structure->pop();

						if (structureChoice == 4)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							c = dynamic_cast<RBTree*>(structure);
							c->balance();
							c = nullptr;
						}

						// Wgraj czas koñcowy
						myClock.stop();

						std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						cout << "Usuwanie wartosci" << endl;
					}
					catch (int exception)
					{
						if (exception == -1) cout << "Nie mozna usunac. Struktura jest pusta. " << endl;
						else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 10: //USUN ELEMENT KONIEC
				{
					try
					{
						// Wgraj czas pocz¹tkowy
						myClock.start();

						structure->pop_back();

						// Wgraj czas koñcowy
						myClock.stop();

						std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						cout << "Usuwanie wartosci z konca" << endl;
					}
					catch (int exception)
					{
						if (exception == -1) cout << "Nie mozna usunac. Struktura jest pusta. " << endl;
						else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
					
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 13: //USUN LOSOWY ELEMENT
				{
					try
					{
						//Inicjacja losowania indeksu do usuniêcia
						srand(time(NULL));
						i = rand() % (structure->getSize() + 1);

						if (structureChoice == 1)
						{
							// Wgraj czas pocz¹tkowy
							myClock.start();

							structure->pop_selected(i);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						}
						else if (structureChoice == 2)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							a = dynamic_cast<List*>(structure);

							// Wgraj czas pocz¹tkowy
							myClock.start();

							a->pop_selected(a->convertIndextToEl(i));

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
							//Powstaly wskaznik wyzerowac, zeby dwa wskazniki nie wskazywaly na to samo miejsce w pamieci
							
							a = nullptr;
						}
						cout << "Nastapi usuniecie ze struktury wartosci pod indeksem: " << i << endl;
					}
					catch (int exception)
					{
						if(exception == -1) cout << "Nie mozna usunac. Struktura jest pusta. " << endl;
						else if(exception == 2) cout << "Nie ma takiego indeksu w struktury." << endl;
						else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
					}
					
					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 14: //USUN WYBRANY ELEMENT
				{
					try
					{
						i = getIndex();
						if (structureChoice == 1)
						{
							// Wgraj czas pocz¹tkowy
							myClock.start();

							structure->pop_selected(i);

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
						}
						else if (structureChoice == 2)
						{
							// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
							a = dynamic_cast<List*>(structure);

							// Wgraj czas pocz¹tkowy
							myClock.start();

							a->pop_selected(a->convertIndextToEl(i));

							// Wgraj czas koñcowy
							myClock.stop();

							std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
							//Powstaly wskaznik wyzerowac, zeby dwa wskazniki nie wskazywaly na to samo miejsce w pamieci
							
							
						}
						cout << "Nastapi usuniecie ze struktury wartosci pod indeksem: " << i << endl;
					}
					catch (int exception)
					{
						if (exception == -1) cout << "Nie mozna usunac. " << endl;
						else if (exception == 2) cout << "Nie ma takiego indeksu w struktury." << endl;
						else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl; 
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);
				}
				break;
			case 5: //WYSZUKIWANIE
				{					
					value = getValue();
						
					// Wgraj czas pocz¹tkowy
					myClock.start();															

							if (structure->seek(value))
							{
								// Wgraj czas koñcowy
								myClock.stop();

								std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
								std::cout << "Znaleziono wartosc w strukturze" << endl;
							}
							else
							{
								// Wgraj czas koñcowy
								myClock.stop();

								std::cout << "Minal czas: " << std::fixed << myClock.timeSpan() * 1000000 << " mikrosekund. \n";
								std::cout << "Nie znaleziono takiej wartosci w strukturze" << endl;
							}
															

					Sleep(2000);
					displayStructureMenu(structureChoice);
					
				}
				break;
			case 6: //GENEROWANIE DANYCH
				{					
					if(structure) delete structure;
					if(structureChoice == 1) structure = new Array();
					else if (structureChoice == 2) structure = new List();
					else if (structureChoice == 3) structure = new Heap();
					else if (structureChoice == 4) structure = new RBTree();
					else structure = 0;

					int minIndex, maxIndex, howMany;
					//Generowanie danych
					cout << "Podaj, ile liczb chcesz wygenerowac." << endl;
					howMany = getValue();
					cout << "Najmniejsza liczba losowana." << endl;
					minIndex = getValue();
					cout << "Najwieksza liczba losowana." << endl;
					maxIndex = getValue();

					structure->generateRandomData(howMany, minIndex, maxIndex);

					if (structureChoice == 4)
					{
						// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
						c = dynamic_cast<RBTree*>(structure);
						c->balance();
						c = nullptr;
					}

					Sleep(2000);
					displayStructureMenu(structureChoice);
				}		
				break;
			case 7: //TESTOWANIE
			{
				test();
				Sleep(2000);
				displayStructureMenu(structureChoice);
			}//case 7
			break;
			case 8: //POWROT
				{
					system("cls");
					delete structure;
					structure = nullptr;
					firstTime = true;
					
				}
				break;
			default: //To nigdy nie powinno siê wyœwietliæ ze wzglêdu na dodatkowe zabezpieczenie wprowadzania opcji menu
				cout << "Podano wartosc niezgodna z przedzialem menu" << endl;
				break;
		} 

		//Wywolanie jawne destruktora dla tablicy, aby po wejsiu z menu tablicy nie byla dalej w pamieci
		//tab->~Array();

}


void Menu::test()
{
	Structure *structureTest;
	//Test
	//if (structure) delete structure;
	int minIndex, maxIndex, howMany, numberOfTests, operation;

	cout << "Podaj, ile testow chcesz wykonac." << endl;
	numberOfTests = getValue();

	cout << "Ktora operacje chcesz przeprowadzic? - podaj numer." << endl;
	//funkcja do wczytywania operacji - nr operacji musi byc w odpowiednim przedziale
	if (structureChoice == 1 || structureChoice == 2) operation = getInput(3, numberOfOptionAL);
	if (structureChoice == 3 || structureChoice == 4) operation = getInput(3, numberOfOptionHT);
	cout << "Podaj, ile liczb chcesz, zeby wczesniej znajdowalo sie w strukturze." << endl;
	howMany = getInput(0,INT_MAX);

	cout << "Najmniejsza liczba mogaca znajdowac sie w strukturze." << endl;
	minIndex = getValue();
	cout << "Najwieksza liczba mogaca znajdowac sie w strukturze." << endl;
	maxIndex = getValue();
	
	//Konieczne usuniecie pliku, zeby dane nie byly dolaczane do starej sesji
	remove("czasy.txt");
	//Generowanie danych
	for (int i = 0; i < numberOfTests; i++)
	{
		if (structureChoice == 1) structureTest = new Array();
		else if (structureChoice == 2) structureTest = new List();
		else if (structureChoice == 3) structureTest = new Heap();
		else if (structureChoice == 4)  structureTest = new RBTree();
		else structureTest = nullptr;

		//Generowanie danych do struktury, za kazdym razem innych - w kazdym tescie
		structureTest->generateRandomData(howMany, minIndex, maxIndex);
		//Losowanie liczby do wlozenia

		//losowy numer do szukania lub wstawienia
		int randomValueToDo = structureTest->randomValue(minIndex, maxIndex);

		//case powrot or generacja danych - reakcja
		switch (operation)
		{
		case 3: //PUSH
		{
			// Wgraj czas pocz¹tkowy
			myClock.start();

			//funkcja ta pushuje 1 element wczesniej wylosowany
			structureTest->push(randomValueToDo);

			if (structureChoice == 4)
			{
				// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
				c = dynamic_cast<RBTree*>(structure);
				c->balance();
				c = nullptr;
			}

			// Wgraj czas koñcowy
			myClock.stop();

			sum(myClock.timeSpan() * 1000000);

			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);
			if (structureTest) delete structureTest;
		}//koniec case 3 - push
		break;
		case 9: //PUSHBACK
		{
			// Wgraj czas pocz¹tkowy
			myClock.start();

			structureTest->push_back(value);
			
			// Wgraj czas koñcowy
			myClock.stop();

			sum(myClock.timeSpan() * 1000000);
			
			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;
		}
		break;
		case 4: //POP
		{			
			try
			{
				// Wgraj czas pocz¹tkowy
				myClock.start();
				structureTest->pop();
				
				if (structureChoice == 4)
				{
					// Konieczne rzutowanie wskaznika, gdyz specjalna metoda jest wywolana jest tylko dla listy
					c = dynamic_cast<RBTree*>(structure);
					c->balance();
					c = nullptr;
				}

				// Wgraj czas koñcowy
				myClock.stop();

				sum(myClock.timeSpan() * 1000000);
			}			
			catch (int exception)
			{
				if (exception == -1) cout << "Nie mozna usunac. Struktura jest pusta. " << endl;
				else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;
			}			

			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;

		}
		break;
		case 10: //POPBACK
		{
			
			try
			{
				// Wgraj czas pocz¹tkowy
				myClock.start();

				//funkcja ta pushuje 1 element wczesniej wylosowany
				structureTest->pop_back();

				// Wgraj czas koñcowy
				myClock.stop();

				sum(myClock.timeSpan() * 1000000);

			}
			catch (int exception)
			{
				if (exception == -1) cout << "Nie mozna usunac. Struktura jest pusta. " << endl;
				else if (exception == 1) cout << "Blad tworzenia nowej struktury!" << endl;

			}
			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;
		}
		break;
		case 5: //WYSZUKIWANIE
		{
			// Wgraj czas pocz¹tkowy
			myClock.start();

			//funkcja ta pushuje 1 element wczesniej wylosowany
			structureTest->seek(randomValueToDo);

			// Wgraj czas koñcowy
			myClock.stop();

			sum(myClock.timeSpan() * 1000000);

			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;
		}
		break;
		case 6:
		case 7:
		case 8:
		{
			cout << "Nie mozna wykonac testu dla tej operacji - nie mamy takich zalozen" << endl;
		}
		break;
		case 11:
		case 12: //	WSTAWIANIE W LOSOWE/WYBRANE MIEJSCE
		{
			// Wgraj czas pocz¹tkowy
			myClock.start();

			//Wylosowanie miejsca, w ktore cos wstawimy
			i = rand() % (structureTest->getSize() + 1);

			//funkcja ta pushuje 1 element wczesniej wylosowany w losowe miejsce
			structureTest->push_selected(i, randomValueToDo);

			// Wgraj czas koñcowy
			myClock.stop();

			sum(myClock.timeSpan() * 1000000);

			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;
		}
		break;
		case 13:
		case 14: //	USUWANIE Z LOSOWEGO/WYBRANEGO MIEJSCA
		{
			// Wgraj czas pocz¹tkowy
			myClock.start();

			//Wylosowanie miejsca, w ktore cos wstawimy
			i = rand() % (structureTest->getSize() + 1);

			//funkcja ta pushuje 1 element wczesniej wylosowany w losowe miejsce
			structureTest->pop_selected(i);

			// Wgraj czas koñcowy
			myClock.stop();

			sum(myClock.timeSpan() * 1000000);

			//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
			saveToFile("czasy.txt", myClock.timeSpan() * 1000000, numberOfTests);

			if (structureTest) delete structureTest;
		}
		break;
		}//switch
	}//for

	cout<< "Czas sredni: " << fixed << (float)average(numberOfTests) << endl;
	Sleep(2000);
	cout << "Wykonano! Zapisano czasy w pliku lub usunieto plik, jesli nie dalo sie przeprowadzic takiej operacji. " << endl;
	Sleep(1000);

	//Zapisanie do pliku czasy.txt kolejnych czasow w mikrosekundach
	saveToFile("pomiary.txt", average(numberOfTests), numberOfTests);
	saveToFile("pomiary.txt", 0, numberOfTests);

	srednia = 0; suma = 0;
}//koniec testu

void Menu::myTestingFunction()
{
	int hm[] = { 100,500,1000,2000 };
	int tabOper[] = { 3,4,5,9,10,12,13 };
	int min[] = { 1, 100 };
	int max[] = { 1000, 20000 };

	for (int i = 0; i < 7; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 4; j++)
			{
				//test(tabOper[i], hm[j], min[k], max[k]);
			}
		}
	}
}

float Menu::average(int numberOfTests)
{
	if (numberOfTests)
	{
		srednia = suma / (float)numberOfTests;
		return srednia;
	}
	else return 0;
}

void Menu::sum(float timeVal)
{
	suma += timeVal;
}