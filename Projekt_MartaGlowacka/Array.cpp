#include "Array.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


using namespace std;

Array::Array()
{
	tab = nullptr;
	size = 0;
	color = 12;
	name = "TABLICA";
}

//1
int Array::readFromFile()
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

	// W pierwszym wierszu jest rozmiar tablicy
	plik >> size; 

	// Stworzenie tablicy i wypelnienie jej danymi

	if (tab != nullptr)
	{
		delete[] tab;
		tab = nullptr;
	}

	tab = new int[size];

	if (!tab)
	{
		throw 1;
	}
	else
	{
		// Plik - wczytywanie danych
		for (int i = 0; i < size; i++)
		{
			plik >> tab[i];
		}
	}
	
	plik.close();
	return 0;
}

//2
int Array::saveToFile()
{
	// Zamienna do zapisu w pliku
	ofstream plik;

	// Otorzenie pliku do zapisu
	plik.open("struktura_zapis.txt", ios::out);

	// Jeœli b³¹d, wyœwietl komunikat
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Pierwsza wartoœæ oznacza rozmiar tablicy
		plik << size << endl;

		// Wczytywanie kolejnych wartoœci do pliku.
		for (int i = 0; i < size; i++)
		{
			plik << tab[i] << endl;
		}
	}

	// Zamkniêcie strumienia.
	plik.close();

	return 0;
}

void Array::display()
{

	cout << "Wartosci w tablicy: " << endl;

	if (size == 0) cout << "Pusta tablica";
	else 	cout << "| ";

	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			cout << tab[i] << " | "; 
		}
	}

	cout << endl << endl;

}

//9
int Array::push_back(int val)
{
	// Nowy rozmiar, zwiêkszony o 1
	int newSize = size + 1;

	// Zmiana rozmiaru tablicy dynamicznej 
	int* newTab = new (nothrow)int[newSize];

	// Jesli pojawi siê b³¹d, wyœwietl komunikat
	if (newTab == nullptr)
	{
		throw 1;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < newSize - 1; i++)
		{
			newTab[i] = tab[i];
		}

		// Zwolnienie z pamiêci starej tablicy,
		// wskaŸnik tab wskazuje teraz na miejsce, w którym jest zalokowana nowa tablica
		delete[] tab;
		size = newSize;
		tab = newTab;

		// Wczytanie  wartosci na nowe miejsce tablicy
		tab[size - 1] = val;

		return 0;
	}
}

//3
int Array::push(int val)
{
	// Nowy rozmiar, zwiêkszony o 1
	int newSize = size + 1;

	// Zmiana rozmiaru tablicy dynamicznej 
	int* newTab = new (nothrow)int[newSize];

	// Jesli pojawi siê b³¹d, wyœwietl komunikat
	if (newTab == nullptr)
	{
		throw 1;
		exit(-1);
	}
	else
	{
			// Wczytanie  wartosci na 1. miejsce tablicy
			newTab[0] = val;
						
			// Kopiowanie wartoœci po indeksie
			for (int i = 1; i < size + 1; i++)
			{
				newTab[i] = tab[i - 1];
			}

			// Zwolnienie z pamiêci starej tablicy,
			// wskaŸnik tab wskazuje teraz na miejsce, w którym jest zalokowana nowa tablica
			delete[] tab;
			size = newSize;
			tab = newTab;
			newTab = nullptr;
			delete newTab;

			return 0;
		}

}

//11 12
int Array::push_selected(int index, int val)
{
	// Nowy rozmiar, zwiêkszony o 1
	int newSize = size + 1;

	// Zmiana rozmiaru tablicy dynamicznej 
	int* newTab = new (nothrow)int[newSize];

	// Jesli pojawi siê b³¹d, wyœwietl komunikat
	if (newTab == nullptr)
	{
		return 1;
		exit(-1);
	}
	else
	{
		// Zabezpieczenie i sprytne wybrniecie, gdy user poda zly indeks tablicy
		if (index < 0)
		{
			push(val);
		}
		else if (index > size)
		{
			push_back(val);
		}
		else
		{
			// Kopiowanie wartoœci przed indeksem
			for (int i = 0; i < index; i++)
			{
				newTab[i] = tab[i];
			}

			// Wczytanie  wartosci na nowe miejsce tablicy
			newTab[index] = val;

			// Kopiowanie wartoœci po indeksie
			for (int i = index + 1; i < size + 1; i++)
			{
				newTab[i] = tab[i - 1];
			}

			// Zwolnienie z pamiêci starej tablicy,
			// wskaŸnik tab wskazuje teraz na miejsce, w którym jest zalokowana nowa tablica
			delete[] tab;
			size = newSize;
			tab = newTab;
				
			return 0;
		}
		

	}
}

//4
int Array::pop()
{
	if (size == 0)
	{
		throw -1;
	}
	else
	{
			// Zmniejszenie o 1 rozmiaru tablicy
			int newSize = size - 1;

			// Alokacja nowej tablicy z mniejszym rozmiarem.
			int *newTab = new int[newSize];

			//Sprawdzenie powodzenia dzia³ania
			if (newTab == nullptr)
			{
				throw 1;
				exit(-1);
			}
			else
			{
				//Przekopiowanie wartoœci do nowej tablicy, pocz¹wszy od indeksu 1
				for (int i = 0; i < newSize; i++)
				{
					newTab[i] = tab[i+1];
				}

			}

			// Tablica wskazuje teraz na nowe miejsce w pamiêci
			delete[] tab;
			size = newSize;
			tab = newTab;
		
			return 0;
	}
}

//10
int Array::pop_back()
{
	//Usuniecie uzywajac napisanej juz metody
	pop_selected(size-1);
	return 0;
}

//13 14
int Array::pop_selected(int index)
{
	if (size == 0)
	{
		throw -1;
	}
	else
	{
		if (index > size || index < 0)
		{
			throw 2;
		}
		else
		{
			// Zmniejszenie o 1 rozmiaru tablicy
			int newSize = size- 1;

			// Alokacja nowej tablicy z mniejszym rozmiarem.
			int *newTab = new int[newSize];

			//Sprawdzenie powodzenia dzia³ania
			if (newTab == nullptr)
			{
				throw 1;
				exit(-1);
			}
			else
			{
				
				for (int i = 0; i < index; i++)
				{
					newTab[i] = tab[i];
				}


				for (int i = index; i < newSize; i++)
				{
					newTab[i] = tab[i + 1];
				}
			}
			delete[] tab;
			size = newSize;
			tab = newTab;

			return 0;
		}
	}
}

//5
bool Array::seek(int val)
{
	if (size == 0) return false;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (tab[i] == val) return true;
		}
		return false;
	}
}

Array::~Array()
{
	if (tab) delete[] tab;
	tab = nullptr;
	size = 0;
}


bool Array::generateRandomData(int structureSize, int minIndex, int maxIndex)
{
	//Dodawanie wartosci, uzywajac funkcji randValue
	for (int i = 0; i < structureSize; i++)
	{
		push(randomValue(minIndex, maxIndex));
	}
	return true;
}

int Array::randomValue(int minIndex, int maxIndex) {
	return (minIndex + (rand() % (maxIndex - minIndex + 1)));
};
