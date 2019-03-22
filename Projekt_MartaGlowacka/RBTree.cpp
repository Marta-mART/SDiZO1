#include "RBTree.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <fstream>

RBTree::RBTree()
{
	//Ustawienie znaków do wyœwietlania kopca
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	tab = nullptr;
	color = 10;
	name = "DRZEWO CZERWONO-CZARNE";
	size= 0; 

   //Inicjacja stra¿nika
	S.color = 'B';
	S.up = &S;
	S.left = &S;
	S.right = &S;

	//Korzen (wskaŸnik) wskazuje na stra¿nika
	//Czyli wpisujemy w t¹ zmienn¹ adres stra¿nika
	root = &S;
}


//Rotacja  w lewo wzgl wêz³a A
void RBTree::rotL(Node * A)
{
	//Wêze³ syna i ojca
	Node * son, *p;

	//Prawy syn A
	son = A->right;

	//Je¿eli syn jest ró¿ny od stra¿nika
	if (son != &S)
	{
		//p to rodzic A
		p = A->up;
		
		//Wykonanie przypisañ tak, aby wêz³y wskoczy³y na inne miejsca
		A->right = son->left;
		if (A->right != &S) A->right->up = A;

		//Lewemu synowi A przypisz A (poddrzewo ju¿ siê zgadza)
		//Ustawione na górze
		son->left = A;
		//Rodzic A staje siê teraz rodzicem nowego "A"
		son->up = p;
		//A jest teraz pod swoim by³ym synem
		A->up = son;

		//Jeœli rodzic ró¿ny od stra¿nika
		if (p != &S)
		{
			//Przypisz rodzicowi, ¿eby wskazywa³ na swojego nowego syna
			//Przypisz z dobrej strony
			if (p->left == A) p->left = son; else p->right = son;
		}
		//Je¿eli rodzica A nie by³o, to son jest korzeniem
		else root = son;
	}
}

//Rotacja  w prawo wzgl wêz³a A
void RBTree::rotR(Node * A)
{
	//Inicjaliazcja - dziecko A
	Node *son, *p;

	son = A->left;
	if (son != &S)
	{
		p = A->up;
		A->left = son->right;
		if (A->left != &S) A->left->up = A;

		son->right = A;
		son->up = p;
		A->up = son;

		if (p != &S)
		{
			if (p->left == A) p->left = son; else p->right = son;
		}
		else root = son;
	}

}

void RBTree::deleteAll(Node * w)
{
	//Je¿eli wêze³ nie jest stra¿nikiem
	if (w != &S)
	{
		//Usuniecie lewego poddrzewa
		deleteAll(w->left);
		//Usuniecie prawego poddrzewa
		deleteAll(w->right);
		//Usuniecie wezla
		if(w) delete w;
	}
}

void RBTree::printTree(std::string sp, std::string sn, Node * p)
{
	//Wyswietlenie struktury drzewa czerwono-czarnego
	std::string t;

	if (p != &S)
	{
		t = sp;
		if (sn == cr) t[t.length() - 2] = ' ';
		printTree(t + cp, cr, p->right);

		t = t.substr(0, sp.length() - 2);
		std::cout << t << sn << p->color << ":" << p->data << std::endl;

		t = sp;
		if (sn == cl) t[t.length() - 2] = ' ';
		printTree(t + cp, cl, p->left);
	}
}

/*void RBTree::resizeTab(int val)
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
		for (int i = 0; i < newSize; i++)
		{
			newTab[i] = tab[i];
		}
		newTab[newSize-1] = val;

		// Zwolnienie z pamiêci starej tablicy,
		// wskaŸnik tab wskazuje teraz na miejsce, w którym jest zalokowana nowa tablica
		size = newSize;
		tab = newTab;
		newTab = nullptr;
		delete newTab;
	}

}

void RBTree::reduceTab()
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
	if (tab) delete[] tab;
	size = newSize;
	tab = newTab;
}*/


void RBTree::DSWalgorithmBackbone()
{
	//Tworzenie krêgos³upa
	Node * tmp = root;

	//Przeprowadzamy rotacje zgodnie z algorytmem
	while (tmp)
	{
		if (tmp->left != &S)
		{
			rotR(tmp);		 //n pozostaje enem
			tmp = tmp->up;
			return;
		}
		else if (tmp->right != &S)
		{
			tmp = tmp->right;
		}			
		else tmp = nullptr;
	}	
}

void RBTree::DSWalgorithmBalancing()
{
	//Zaczynamy od korzenia
	Node *tmp = root;

	//Wyliczamy m
	int base = (int)floor((log2(size + 1)));
	int m = pow(2, base) - 1;

	//Bêdzie liczba wez³ów - m rotacji w lewo
	int numberOfRotations = size - m;
	for (int i = 0; i < numberOfRotations; i++)
	{
		rotL(tmp);
		tmp = tmp->up->right;
	}

	//Potem przeprowadzamy rotacje w prawo (m rotacji) poczynaj¹c od korzenia
	while (m > 1)
	{
		m = m / 2;
		tmp = root;
		for (int i = 0; i < m; i++)
		{
			rotL(tmp);
			tmp = tmp->up->right;
		}		
	}

}


RBTree::~RBTree()
{
	//Usuwamy wêz³y funkcj¹ rekurencyjn¹
	//Za pocz¹tek dajemy korzeñ
	deleteAll(root);
	size = 0;
}

//Wywoluje funkcje rekurencyjna
void RBTree::display()
{
	printTree("","", root);
}

int RBTree::readFromFile()
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

	// W pierwszym wierszu jest rozmiar tablicy
	int sizeFinal;
	plik >> sizeFinal;

	//Jeœli by³a wczeœniej stworzona, usuwamy, ¿eby nie marnowaæ pamiêci
	if (tab != nullptr)
	{
		throw 3;
	}
	
	tab = new int[sizeMax];

	if (!tab)
	{
		throw 1;
	}
	else
	{
		// Plik - wczytywanie danych
		for (int i = 0; i < sizeFinal; i++)
		{
			plik >> tab[i];
			push(tab[i]);			
		}

		//DSW

		//Rozprostowanie
		DSWalgorithmBackbone();	
		//Balansowanie
		DSWalgorithmBalancing();

	}
		
	return 0;
}

int RBTree::saveToFile()
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

int RBTree::push(int val)
{
	Node *newNode, *uncle;

	//Tworzymy nowy wêze³
	newNode = new Node;
	//Inicjujemy go danymi
	newNode->left = &S;
	newNode->right = &S;
	newNode->up = root;
	newNode->data = val;
		
	//Sprawdzamy, czy powy¿szy element jest stra¿nikiem - czyli drzewo jest puste
	//Jeœli tak, to znaczy, ¿e wstawiamy korzen
	if (newNode->up == &S)
	{
		root = newNode;
	}
	//Je¿eli ju¿ jest korzeñ, czyli wstawiamy element poni¿ej korzenia, to:
	else
	{
		while (true)
		{
			//Wstawiamy do drzewa RB procedur¹ wstawiania do drzewa BST
			if (val < newNode->up->data)
			{
				if (newNode->up->left == &S)
				{
					//nowy wêz³e³ zastêpuje lewy liœæ
					newNode->up->left = newNode;
					break;
				}
				newNode->up = newNode->up->left;
			}

			else if (val > newNode->up->data)
			{
				if (newNode->up->right == &S)
				{
					newNode->up->right = newNode;
					break;
				}
				newNode->up = newNode->up->right;
			}

			else
			{
				delete newNode;
				return 0;
			}
		}//while


		//Kolorujemy wêze³ na czerwono
		newNode->color = 'R';
		//i sprawdzamy
		while ((newNode != root) && (newNode->up->color == 'R'))
		{
			//Jeœli rodzic nowego ma taki sam kolor jak wujek
			if (newNode->up == newNode->up->up->left)
			{
				uncle = newNode->up->up->right;

				//------------------1---------------------------------
				//Jeœli wujek ma kolor czerwony
				if (uncle->color == 'R')
				{
					//Ustaw rodzica i wujka na czarnych
					newNode->up->color = 'B';
					uncle->color = 'B';
					//A dziadka nowego na czerwono
					newNode->up->up->color = 'R';
					//Przejdz na dziadka i sprawdz warunki dla niego
					//¯eby drzewo dalej spe³nia³o warunki drzewa B i R
					newNode = newNode->up->up;
					continue;
				}

				//-----------------2----------------------------------
				//Je¿eli nowy jest lewym synem swojego rodzica, który ma dziadka
				if (newNode == newNode->up->right)
				{
					//przypisz newNodowi rodzica (potrzebne do rotacji, bo robimy wzglêdem rodzica)
					newNode = newNode->up;
					//Zastosuj rotacjê w lewo
					rotL(newNode);
				}

				//-----------------3----------------------------------
				//Je¿eli nowy jest lewym synem swojego rodzica, który ma dziadka
				//Pozmieniaj kolory na odpowiednie
				//aby zachowac warunek drzewa BR
				newNode->up->color = 'B';
				newNode->up->up->color = 'R';
				//Zrób rotacjê wzglêdem dziadka
				rotR(newNode->up->up);

				//WyjdŸ z pêtli - skoñczy³eœ operacje zmieniania
				//Warunki drzewa BR siê zgadzaj¹
				break;
			}
			else
			{
				//Rozpatrzenie przypadków analogicznych
				//tzw. lustrzanych

				//Teraz wujek znajduje siê z prawej strony nowego wêz³a
				//patrz¹c od do³u
				uncle = newNode->up->up->right;

				//------------------1---------------------------------
				//Jeœli wujek ma kolor czerwony
				if (uncle->color == 'R')
				{
					//Ustaw rodzica i wujka na czarnych
					newNode->up->color = 'B';
					uncle->color = 'B';
					//A dziadka nowego na czerwono
					newNode->up->up->color = 'R';
					//Przejdz na dziadka i sprawdz warunki dla niego
					//¯eby drzewo dalej spe³nia³o warunki drzewa B i R
					newNode = newNode->up->up;
					continue;
				}

				//-----------------2----------------------------------
				//Je¿eli nowy jest prawym synem swojego rodzica, który ma dziadka
				if (newNode == newNode->up->left)
				{
					//przypisz newNodowi rodzica (potrzebne do rotacji, bo robimy wzglêdem rodzica)
					newNode = newNode->up;
					//Zastosuj rotacjê w prawo
					rotR(newNode);
				}

				//-----------------3----------------------------------
				//Je¿eli nowy jest prawym synem swojego rodzica, który ma dziadka
				//Pozmieniaj kolory na odpowiednie
				//aby zachowac warunek drzewa BR
				newNode->up->color = 'B';
				newNode->up->up->color = 'R';
				//Zrób rotacjê wzglêdem dziadka
				rotL(newNode->up->up);

				//WyjdŸ z pêtli - skoñczy³eœ operacje zmieniania
				//Warunki drzewa BR siê zgadzaj¹
				break;
			}
			//Jeœli wêze³ okaza³ siê korzeniem, to pokolorujmy go na czarno

		}//while korzen

		root->color = 'B';

	}//else

	size++;
	return 0;
}

int RBTree::pop()
{
	if(size) popNode(root);
	else throw - 1;
}


// Wyszukuje najmniejszy wêze³ w poddrzewie
// o korzeniu r
Node * RBTree::minRBT(Node * r)
{
	if (r != &S)
		while (r->left != &S) r = r->left;
	return r;
}

// Zwraca nastêpnik A
Node *RBTree::successor(Node * p)
{
	Node * r;

	if (p != &S)
	{
		if (p->right != &S) return minRBT(p->right);
		else
		{
			r = p->up;
			while ((r != &S) && (p == r->right))
			{
				p = r;
				r = r->up;
			}
			return r;
		}
	}
	return &S;
}

//Usuwanie wêz³a
void RBTree::popNode(Node * nodeToRemove)
{
	//Przypadek 1. Brat wêz³a A* (wêze³ C) jest czerwony.
	//Przypadek 2. Brat wêz³a A* (wêze³ C) jest czarny i posiada czarnych synów (wêz³y D i E).
	//Przypadek 3. Brat wêz³a A* (wêze³ C) jest czarny, lewy syn wêz³a C jest czerwony, prawy syn wêz³a C jest czarny.
	//Przypadek 4. Brat wêz³a A* (wêze³ C) jest czarny, a jego prawy syn jest czerwony.

	Node * W, *son, *Z;

	//Usuwany wêze³ usuwany nie posiada lewego syna
	//Na jego miejsce idzie syn prawy
	if ((nodeToRemove->left == &S) || (nodeToRemove->right == &S)) son = nodeToRemove;
	else son = successor(nodeToRemove);

	if (son->left != &S) Z = son->left;
	else Z = son->right;

	Z->up = son->up;

	if (son->up == &S) root = Z;
	else if (son == son->up->left) son->up->left = Z;
	else son->up->right = Z;

	if (son != nodeToRemove) nodeToRemove->data = son->data;

	// Naprawa struktury drzewa czerwono-czarnego
	if (son->color == 'B')  
		while ((Z != root) && (Z->color == 'B'))
			if (Z == Z->up->left)
			{
				W = Z->up->right;

				if (W->color == 'R')
				{  
					// Przypadek 1
					W->color = 'B';
					Z->up->color = 'R';
					rotL(Z->up);
					W = Z->up->right;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{ 
					// Przypadek 2
					W->color = 'R';
					Z = Z->up;
					continue;
				}

				if (W->right->color == 'B')
				{  
					// Przypadek 3
					W->left->color = 'B';
					W->color = 'R';
					rotR(W);
					W = Z->up->right;
				}

				W->color = Z->up->color; // Przypadek 4
				Z->up->color = 'B';
				W->right->color = 'B';
				rotL(Z->up);
				Z = root;         // pêtal siê zakoñczy
			}
			else
			{   // Przypadki lustrzane
				W = Z->up->left;

				if (W->color == 'R')

				{   // Przypadek 1
					W->color = 'B';
					Z->up->color = 'R';
					rotR(Z->up);
					W = Z->up->left;
				}

				if ((W->left->color == 'B') && (W->right->color == 'B'))
				{        
					// Przypadek 2
					W->color = 'R';
					Z = Z->up;
					continue;
				}

				if (W->left->color == 'B')
				{           
					// Przypadek 3
					W->right->color = 'B';
					W->color = 'R';
					rotL(W);
					W = Z->up->left;
				}

				W->color = Z->up->color;  // Przypadek 4
				Z->up->color = 'B';
				W->left->color = 'B';
				rotR(Z->up);
				Z = root;         // zakoñczenie pêtli
			}

	Z->color = 'B';

	delete son;
	size--;
}

bool RBTree::seek(int val)
{
	//Je¿eli jest w czym szukaæ
	if (size) 
	{
		//Jeœli funkcja szukaj¹ca wêz³a, zwróci wyszukany, to return true
		if(seekNode(val)) return true;
		//jeœli nie zwróci (zwóci nulla), to nie znaleziono wartosci
		else return false;
	}
	else return false;
}

// Wyszukuje wêze³ o warosci val
Node * RBTree::seekNode(int val)
{
	Node * nodeToFind;

	//Zaczynamy szukanie od korzenia
	nodeToFind = root;

	//Szukaj, dopóki nie znajdziesz albo natrafisz na stra¿nika
	while ((nodeToFind != &S) && (nodeToFind->data != val))
		if (val < nodeToFind->data) nodeToFind = nodeToFind->left;
		else nodeToFind = nodeToFind->right;
		if (nodeToFind == &S) return nullptr;
		return nodeToFind;
}

bool RBTree::generateRandomData(int structureSize, int minIndex, int maxIndex)
{
	//Dodawanie wartosci, uzywajac funkcji randValue
	for (int i = 0; i < structureSize; i++)
	{
		//Dodaj wylosowan¹ wartoœæ
		push(randomValue(minIndex, maxIndex));
	}
	return true;
}

int RBTree::randomValue(int minIndex, int maxIndex)
{
	return (minIndex + (rand() % (maxIndex - minIndex + 1)));
}

void RBTree::balance()
{
	//DSW
	//Rozprostowanie
	for(int i=0; i< size; i++)
	DSWalgorithmBackbone();
	//Balansowanie
	DSWalgorithmBalancing();

}
