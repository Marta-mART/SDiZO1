#include "List.h"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

List::List()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
	color = 11;
	name = "LISTA";
}

//1
int List::readFromFile()
{
	//Zmienna do wczytywania z pliku
	ifstream plik;

	// Otwieranie pliku
	plik.open("struktura.txt", ios::in);

	// Gdy blad otwarcia pliku
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(0);
	}

	// W pierwszym wierszu jest rozmiar listy
	int sizeFinal;
	plik >> sizeFinal;

	// Stworzenie  listy i wypelnienie jej danymi, jesli nie byla wczesniej stworzona
	if (head != nullptr && tail != nullptr)
	{
		while (size) pop();
	}
		
	// Plik - wczytywanie danych
	for (int i = 0; i < sizeFinal; i++)
	{
		int value;
		plik >> value;
		push(value);
	}
	
	plik.close();
	return 0;
}

//2
int List::saveToFile()
{
	// Zamienna do zapisu w pliku
	ofstream plik;

	// Otorzenie pliku do zapisu
	plik.open("struktura_zapis.txt", ios::out);

	// Je�li b��d, wy�wietl komunikat
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Pierwsza warto�� oznacza rozmiar tablicy
		plik << size << endl;

		listEl *element = new listEl;
		element = head;

		// Plik - wczytywanie danych
		while(element)
		{
			plik << (element->data) << endl;
			element = element->next;
		}
	}

	// Zamkni�cie strumienia.
	plik.close();

	return 0;
}

void List::display()
{
	listEl *element;
	element = head;

	cout << "Wartosci w liscie: " << endl;

	if (size == 0) cout << "Pusta lista";
	else 	cout << "| ";

	if (size > 0)
	{
		while(element)
		{
			// Wy�wietl warto��, czyli zawartosc pola data elementu
			cout << element->data << " | ";
			// Przypisz wskaznikowi kolejny element na liscie, korzystajac z tego, ze jest on zapisany w polu next
			element = element->next;
		}
	}

	cout << endl << endl;

}

//OPERACJE
//------------------------------------------------------------------------------------------------------

//4
int List::push_back(int val)
{
	// Tworzenie nowego elementu
	listEl *newEl = new listEl;

	// W poprzedniku zapisujemy zawartosc pola tail
	newEl->prev = tail;
	// W nastepniku podajemy nulla
	newEl->next = nullptr;
	// Zapisujemy wartosc podana przez argument
	newEl->data = val;

	// Ogon wskazuje na ostatni - nowododany element
	tail = newEl;

	// Je�li nowy el ma poprzednik, to pole next poprzednika b�dzie
	// wskazywa�o w�a�nie na nowy element
	if (newEl->prev) (newEl->prev)->next = newEl;
	// Je�li nie ma poprzednika, to element by� dodawany do pustej listy
	// W pole head wprowadzamy adres nowego elementu
	else head = newEl;

	// Nowy rozmiar, zwi�kszony o 1
	size++;

	return 0;
}

//3
int List::push(int val)
{
	// Tworzenie nowego elementu
	listEl *newEl = new listEl;

	// W poprzedniku zapisujemy adres zerowy
	newEl->prev = nullptr;
	// W nastepniku dotychczasowa glowe
	newEl->next = head;
	// Zapisujemy wartosc podana przez argument
	newEl->data = val;

	// Now� g�ow� staje si� nowy element
	head = newEl;
	 
	// Je�li nowy el ma nast�pnik, to pole prev nast�pnika b�dzie
	// wskazywa�o w�a�nie na nowy element
	if (newEl->next) (newEl->next)->prev = newEl;
	// Je�li nie ma nast�pnika, to element by� dodawany do pustej listy
	// W pole tail wprowadzamy adres nowego elementu
	else tail = newEl;

	// Nowy rozmiar, zwi�kszony o 1
	size++;

	return 0;
}

//5 i 6
int List::push_selected(listEl *element, int val)
{
	if (element == nullptr) throw -1;
	if (head == element) push(val);
	else
	{
		// Tworzenie nowego elementu
		listEl *newEl = new listEl;

		// Nast�pnik to podany element
		newEl->next = element;
		// Poprzednik nowego to poprzednik wybranego elementu
		newEl->prev = element->prev;
		// Zapisanie wybranej wartosci w polu data
		newEl->data = val;
		
		// Nowy rozmiar, zwi�kszony o 1
		size++;

		// Nastepnik poprzednika wybranego elementu to nowy element
		(element->prev)->next = newEl;
		// Poprzednik elementu wybranego to nowy element
		element->prev = newEl;
	}
	
	return 0;
}

listEl* List::convertIndextToEl(int index)
{
	if (size)
	{
		if (index < size && index >= 0)
		{
			listEl * element = new listEl;
			element = head;

			for (int i = 0; i < index; i++)
			{
				element = element->next;
			}

			return element;
		}
		else return nullptr;
	}
	else return nullptr;
}

//7
int List::pop()
{
	//Usuniecie uzywajac napisanej juz metody
	if (size != 0) pop_selected(head);
	else throw -1;
}

//8
int List::pop_back()
{
	//Usuniecie uzywajac napisanej juz metody
	if (size != 0) pop_selected(tail);
	else throw -1;
	return 0;
}

//9 i 10
int List::pop_selected(listEl *element)
{
	if (size > 0 && element != nullptr)
	{
		// Zmniejszenie rozmiaru listy
		size--;

		// Jesli usuwany element ma nastepnika
		if (element->next) (element->next)->prev = element->prev;
		// Je�li nie ma, znaczy, �e by� ostatni 
		// i teraz ogonem jest jego poprzednik
		else tail = element->prev;

		//Jesli usuwany element ma poprzednika
		if (element->prev) element->prev->next = element->next;
		// Je�li nie ma, znaczy, �e by� pierwszy 
		// i teraz glowa wskazuje na nastepnika elementu usuwanego
		else head = element->next;

		// Usuwamy podany element
		delete element;
	}
	else throw - 1;	

	return 0;
}

//11
bool List::seek(int val)
{
	
	if (size == 0) return false;
	else
	{
		// Realizacja przejscia od glowy
		listEl *element = head;

		while(element)
		{			
			if (element->data == val) return true;
			element = element->next;
		}
		return false;
	}
}


List::~List()
{
	//Jesli rozmiar != 0 usuwaj elementy
	while (size) pop();
}

bool List::generateRandomData(int structureSize, int minIndex, int maxIndex)
{
	//Dodawanie wartosci, uzywajac funkcji randValue
	for (int i = 0; i < structureSize; i++)
	{
		push(randomValue(minIndex, maxIndex));
	}
	return true;
}

int List::randomValue(int minIndex, int maxIndex) {
	return (minIndex + (rand() % (maxIndex - minIndex + 1)));
};
