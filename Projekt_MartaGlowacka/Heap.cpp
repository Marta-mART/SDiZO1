#include "Heap.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Heap::Heap()
{
	//Ustawiamy flagê dla funkcji szukaj¹cej - nie znaleziono
	found = false;
	tab = nullptr;
	size = 0;
	color = 13;
	name = "KOPIEC";

	//Ustawienie znaków do wyœwietlania kopca
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

Heap::~Heap()
{
	if(tab) delete[] tab;
	tab = nullptr;
	size = 0;
}

void Heap::printHeap(std::string sp, std::string sn, int val)
{
	std::string s;
	//Wyœwietlenie struktury kopca
	if (val < size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printHeap(s + cp, cr, 2 * val + 2);

		s = s.substr(0, sp.length() - 2);

		std::cout << s << sn << tab[val] << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printHeap(s + cp, cl, 2 * val + 1);
	}
}

void Heap::display()
{
	//Prezentacja danych w formie tablicowej
	if (size > 0)
	{
		std::cout << "| ";

		for (int i = 0; i < size; i++)
		{
			std::cout << tab[i] << " | ";
		}

		std::cout << std::endl; 

		// Prezentujemy wyniki w formie drzewa

		//Moj kod nieuzyty, gdyz ladnie pokazuje tylko dla wartosci jednocyfrowych
		//Inaczej, wszystko siê rozje¿d¿a
		//int i, j, k, x;

		//x = (size + 1) / 2; k = 1;
		//for (i = 0; i < size; i++)
		//{
		//	for (j = 1; j <= x - 1; j++) std::cout << " ";
		//	std::cout << tab[i];
		//	for (j = 1; j <= x; j++) std::cout << " ";
		//	if (i + 1 == k)
		//	{
		//		//rosnie co 2
		//		k += (k+1); x /= 2; std::cout << std::endl;
		//	}
		//}

		printHeap("", "", 0);

	}
	else std::cout << "Struktura pusta" << std::endl;
	std::cout << std::endl << std::endl;

}

//1
int Heap::readFromFile()
{
	//Zmienna do wczytywania z pliku
	std::ifstream plik;

	// Otwieranie pliku
	plik.open("struktura.txt", std::ios::in);

	// Gdy blad otwarcia pliku
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(0);
	}

	// W pierwszym wierszu jest rozmiar drzewa
	plik >> size;

	// Stworzenie tablicy do drzewa i wypelnienie jej danymi
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
		
		//Sortowanie danych, tak, aby spelnialy warunek kopca
		sort();
	}

	plik.close();
	return 0;
}

//2
int Heap::saveToFile()
{
	// Zamienna do zapisu w pliku
	std::ofstream plik;

	// Otorzenie pliku do zapisu
	plik.open("struktura_zapis.txt", std::ios::out);

	// Jeœli b³¹d, wyœwietl komunikat
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Pierwsza wartoœæ oznacza rozmiar tablicy
		plik << size << std::endl;

		// Wczytywanie kolejnych wartoœci do pliku.
		for (int i = 0; i < size; i++)
		{
			plik << tab[i] << std::endl;
		}
	}

	// Zamkniêcie strumienia.
	plik.close();

	return 0;
}

//3
int Heap::push(int val)
{
	//Deklarujemy zmienne do mieszczenia syna i jego rodzica
	int son, parent;
	
	//powiêkszenie dynamiczne tablicy
	resizeTab();

	//Ustawiamy indeks syna na ostatnie miejsce w tablicy
	son = (size - 1);

	//Ustawiamy indeks rodzica powy¿szego syna, korzystaj¹c ze wzoru
	parent = (son - 1) / 2;

	//Sprawdzenie warunku kopca - rób, dopóki syn jest w tablicy, a jego wartosc jest < od wstawianej wartosci
	while (son > 0 && tab[parent] < val)
	{
		//Rodzic staje siê teraz synem
		tab[son] = tab[parent];
		//Indeks syna na wczeœniejszego rodzica
		son = parent;
		//A indeks nowego rodzica obliczamy ze wzoru
		parent = (son - 1) / 2;
	}
	//Wstawiamy element w odpowiednim miejscu
	//czyli na miejscu syna
	tab[son] = val;
	return 0;
}

//4
int Heap::pop()
{
	//i, j - indeksy elementów
	//val to value, czyli element kopca
	int i, j, val;
	//liczba elementow to size - 1
	
	//Wykonaj pop, jeœli w ogóle jest rozmiar usiawiony
	if (size)
	{	
		//Pobiera wartosc elementu, ktory jest jako ostatni w tablicy
		val = tab[size-1];

		//Pomniejszenie o 1 tablicy, znika ostatni element
		reduceTab();
		//od teraz size--

		if (size+1 != 1)
		{		

			i = 0; //wskazuje na korzen
			j = 1; //wskazuje na lewe dziecko korzenia

				   //Bedziemy szli w dol kopca
			while (j < size)
			{
				//Je¿eli prawy syn > od lewego, to weŸ  prawego syna
				//Ale sprawdŸ, czy na pewno on istnieje - jego indeks jest mniejszy od size
				if (j + 1 < size && tab[j + 1] > tab[j]) j++;
				//Jeœli warunek kopca spe³niony, wyjdŸ z pêtli
				if (val >= tab[j]) break;
				tab[i] = tab[j];
				//Przechodzimy na wiêkszego syna
				i = j;
				//I wskazujemy lewego syna dla niego
				j = 2 * j + 1;
			}

			//Umieszczamy wartosc w kopcu
			tab[i] = val;
		}//if
		else tab = nullptr;					
		
	}
	else
	{
		throw -1;
		tab = nullptr;
	}
	
	return 0;
}

bool Heap::seek(int val)
{
	found = false;
	if(seekRek(0,val)) return true;
	return false;
}


//5
bool Heap::seekRek(int i, int val)
{	
	//Nie ma czego szukac
	if (size == 0) return false;

	//Jeœli znaleŸliœmy, to koñczymy funkcjê (ale ona jest rekurencyjna), wiêc wykorzystujemy jeszcze flagê, ¿eby
	//nie pojsc dalej w funkcji
	if (tab[i] == val) {
		found = true;
		return true;
		
	}
	//Je¿eli dany element jest mniejszy od szukanej wartosci, to tutaj juz nie szukaj
	//(wroci do miejsca gdzie funkcja rekurencyjna byla wywolana, a nie calkiem zakonczy dzialanie wyszukiwania)
	else if (tab[i] < val) return false;

	//Lewy syn
	int left = 2 * i + 1;

	//Je¿eli lewy syn wiêkszy ni¿ rozmiar, to ju¿ na pewno go nie ma
	if (left >= size) return false;

	//Je¿eli kopiec istnieje i jeszcze nie znaleziono wartosci, to szukaj w lewym poddrzewie
	if (size && !found) i = seekRek(left, val);
	//Nie znaleziono w lewym poddrzewie:
	else return false;

	//Je¿eli nie znaleziono wczeœniej
	//Prawy syn
	if (!found)
	{
		int right = left + 1;

		//Je¿eli prawy syn nie istnieje, to zakoncz szukanie tutaj
		if (right >= size) return false;
		else
		{
			//Jeœli istnieje, to szukaj w jego poddrzewie... i wywo³aj rekurencyjnie znów funkcje dla jego synów itd.
			if (size && !found) right = seekRek(right, val);
		}
	}
		
}

//6
bool Heap::generateRandomData(int structureSize, int minIndex, int maxIndex)
{
	//Dodawanie wartosci, uzywajac funkcji randValue
	for (int i = 0; i < structureSize; i++)
	{
		//Dodaj wylosowan¹ wartoœæ
		push(randomValue(minIndex, maxIndex));
	}
	return true;
}

int Heap::randomValue(int minIndex, int maxIndex)
{
	return (minIndex + (rand() % (maxIndex - minIndex + 1)));
}

// Zmniejszenie o 1 rozmiaru tablicy
void Heap::reduceTab()
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
		//Przekopiowanie wartoœci do nowej tablicy, pocz¹wszy od indeksu 1, pomijamy ostatni element
		for (int i = 0; i < newSize; i++)
		{
			newTab[i] = tab[i];
		}

	}

	// Tablica wskazuje teraz na nowe miejsce w pamiêci
	if(tab) delete[] tab;
	size = newSize;
	tab = newTab;
}

//Powiêkszenie dynamiczne tablicy
void Heap::resizeTab()
{
	// Nowy rozmiar, zwiêkszony o 1
	int newSize = size + 1;

	// Zmiana rozmiaru tablicy dynamicznej 
	int* newTab = new int[newSize];

	// Jesli pojawi siê b³¹d, wyœwietl komunikat
	if (newTab == nullptr)
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Kopiowanie wartoœci po indeksie
		for (int i = 0; i < size; i++)
		{
			newTab[i] = tab[i];
		}

		// Zwolnienie z pamiêci starej tablicy,
		// wskaŸnik tab wskazuje teraz na miejsce, w którym jest zalokowana nowa tablica
		if(tab) delete[] tab;
		size = newSize;
		tab = newTab;
		newTab = nullptr;
		delete newTab;

	}

}

//Funkcja sortujaca nieuporz¹dkowane dane, tak, aby spe³nia³y warunek kopca
void Heap::sort()
{
	//i - indeks petli i tablicy
	//son - pozycja liscia
	//parent - pozycja rodzica
	//x - zmienna pomconicza, do zapamietania elementu
	int i, son, parent, x;

	//Kolejne elementy wstawiane do kopca, 0 element pomijamy, bo zostanie
	//i tak tam gdzie byl
	for (i = 1; i <= size-1; i++)
	{
		//Syn i jego rodzic - indeksy
		son = i; parent = son / 2;
		//Zapamietuje wstawiany element - jego wartosc
		x = tab[i];
		//Pêtla wykonuje siê, a¿ nie osi¹gniemy korzenia kopca
		//lub nie znagdziemy przodka wiêkszego od elementu zapamiêtanego z tablicy nieuporzadkowanej
		while ((parent >= 0) && (tab[parent] < x))
		{
			// Rodzic na miejsce dziecka
			tab[son] = tab[parent];
			//I mamy nowego rodzica dla niego
			son = parent; parent = son / 2;

			//Petla musi sie przerwac, dopiero gdy osiagniemy korzen
			//a nie moglibysmy dac warunku w while parent>0, bo na pocz¹tku w 
			//son nie zapisa³oby siê 0 - a potrzebne jako indeks tablicy
			if (parent == 0 && son == 0) break;
		}
		//Zapisanie elementu zapamietanego
		tab[son] = x;
	}
}

void Heap::swap(int &a, int &b)
{
	int x; //zmienna pomocnicza
	x = a;
	a = b;
	b = x;
}

