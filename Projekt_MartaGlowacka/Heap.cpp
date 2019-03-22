#include "Heap.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Heap::Heap()
{
	//Ustawiamy flag� dla funkcji szukaj�cej - nie znaleziono
	found = false;
	tab = nullptr;
	size = 0;
	color = 13;
	name = "KOPIEC";

	//Ustawienie znak�w do wy�wietlania kopca
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
	//Wy�wietlenie struktury kopca
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
		//Inaczej, wszystko si� rozje�d�a
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

	// Je�li b��d, wy�wietl komunikat
	if (plik.bad() || plik.fail())
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Pierwsza warto�� oznacza rozmiar tablicy
		plik << size << std::endl;

		// Wczytywanie kolejnych warto�ci do pliku.
		for (int i = 0; i < size; i++)
		{
			plik << tab[i] << std::endl;
		}
	}

	// Zamkni�cie strumienia.
	plik.close();

	return 0;
}

//3
int Heap::push(int val)
{
	//Deklarujemy zmienne do mieszczenia syna i jego rodzica
	int son, parent;
	
	//powi�kszenie dynamiczne tablicy
	resizeTab();

	//Ustawiamy indeks syna na ostatnie miejsce w tablicy
	son = (size - 1);

	//Ustawiamy indeks rodzica powy�szego syna, korzystaj�c ze wzoru
	parent = (son - 1) / 2;

	//Sprawdzenie warunku kopca - r�b, dop�ki syn jest w tablicy, a jego wartosc jest < od wstawianej wartosci
	while (son > 0 && tab[parent] < val)
	{
		//Rodzic staje si� teraz synem
		tab[son] = tab[parent];
		//Indeks syna na wcze�niejszego rodzica
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
	//i, j - indeksy element�w
	//val to value, czyli element kopca
	int i, j, val;
	//liczba elementow to size - 1
	
	//Wykonaj pop, je�li w og�le jest rozmiar usiawiony
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
				//Je�eli prawy syn > od lewego, to we�  prawego syna
				//Ale sprawd�, czy na pewno on istnieje - jego indeks jest mniejszy od size
				if (j + 1 < size && tab[j + 1] > tab[j]) j++;
				//Je�li warunek kopca spe�niony, wyjd� z p�tli
				if (val >= tab[j]) break;
				tab[i] = tab[j];
				//Przechodzimy na wi�kszego syna
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

	//Je�li znale�li�my, to ko�czymy funkcj� (ale ona jest rekurencyjna), wi�c wykorzystujemy jeszcze flag�, �eby
	//nie pojsc dalej w funkcji
	if (tab[i] == val) {
		found = true;
		return true;
		
	}
	//Je�eli dany element jest mniejszy od szukanej wartosci, to tutaj juz nie szukaj
	//(wroci do miejsca gdzie funkcja rekurencyjna byla wywolana, a nie calkiem zakonczy dzialanie wyszukiwania)
	else if (tab[i] < val) return false;

	//Lewy syn
	int left = 2 * i + 1;

	//Je�eli lewy syn wi�kszy ni� rozmiar, to ju� na pewno go nie ma
	if (left >= size) return false;

	//Je�eli kopiec istnieje i jeszcze nie znaleziono wartosci, to szukaj w lewym poddrzewie
	if (size && !found) i = seekRek(left, val);
	//Nie znaleziono w lewym poddrzewie:
	else return false;

	//Je�eli nie znaleziono wcze�niej
	//Prawy syn
	if (!found)
	{
		int right = left + 1;

		//Je�eli prawy syn nie istnieje, to zakoncz szukanie tutaj
		if (right >= size) return false;
		else
		{
			//Je�li istnieje, to szukaj w jego poddrzewie... i wywo�aj rekurencyjnie zn�w funkcje dla jego syn�w itd.
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
		//Dodaj wylosowan� warto��
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

	//Sprawdzenie powodzenia dzia�ania
	if (newTab == nullptr)
	{
		throw 1;
		exit(-1);
	}
	else
	{
		//Przekopiowanie warto�ci do nowej tablicy, pocz�wszy od indeksu 1, pomijamy ostatni element
		for (int i = 0; i < newSize; i++)
		{
			newTab[i] = tab[i];
		}

	}

	// Tablica wskazuje teraz na nowe miejsce w pami�ci
	if(tab) delete[] tab;
	size = newSize;
	tab = newTab;
}

//Powi�kszenie dynamiczne tablicy
void Heap::resizeTab()
{
	// Nowy rozmiar, zwi�kszony o 1
	int newSize = size + 1;

	// Zmiana rozmiaru tablicy dynamicznej 
	int* newTab = new int[newSize];

	// Jesli pojawi si� b��d, wy�wietl komunikat
	if (newTab == nullptr)
	{
		throw 1;
		exit(-1);
	}
	else
	{
		// Kopiowanie warto�ci po indeksie
		for (int i = 0; i < size; i++)
		{
			newTab[i] = tab[i];
		}

		// Zwolnienie z pami�ci starej tablicy,
		// wska�nik tab wskazuje teraz na miejsce, w kt�rym jest zalokowana nowa tablica
		if(tab) delete[] tab;
		size = newSize;
		tab = newTab;
		newTab = nullptr;
		delete newTab;

	}

}

//Funkcja sortujaca nieuporz�dkowane dane, tak, aby spe�nia�y warunek kopca
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
		//P�tla wykonuje si�, a� nie osi�gniemy korzenia kopca
		//lub nie znagdziemy przodka wi�kszego od elementu zapami�tanego z tablicy nieuporzadkowanej
		while ((parent >= 0) && (tab[parent] < x))
		{
			// Rodzic na miejsce dziecka
			tab[son] = tab[parent];
			//I mamy nowego rodzica dla niego
			son = parent; parent = son / 2;

			//Petla musi sie przerwac, dopiero gdy osiagniemy korzen
			//a nie moglibysmy dac warunku w while parent>0, bo na pocz�tku w 
			//son nie zapisa�oby si� 0 - a potrzebne jako indeks tablicy
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

