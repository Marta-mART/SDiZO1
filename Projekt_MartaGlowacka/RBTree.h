#pragma once
#include "Structure.h"
#include <string>

const int sizeMax = 100000;

struct Node
{
	Node *up, *left, *right;
	int data;
	char color;
};

class RBTree : public Structure
{
private:
	std::string cr, cl, cp; // �a�cuchy do znak�w ramek
	unsigned size; //liczba wezlow
	Node S; //Stra�nik
	Node *root; //Wska�nik na korzen

	//Tablica kluczy
	int *tab;
	//Dodatkowe prywatne metody - rotacje
	//Rotacja w lewo wzgl�dem w�z�a A
	void rotL(Node *A);
	//Rotacja w prawo wzgl�dem w�z�a A
	void rotR(Node *A);
	//Funkcja do usuwania ca�ego drzewa, korzysta z niej destruktor
	void deleteAll(Node *w);

	void printTree(std::string sp, std::string sn, Node * p);

	//zmiana rozmiaru o 1 mniej
	//void resizeTab(int val);
	//void reduceTab();

	//Dwie cz�sci algorytmu DSW
	void DSWalgorithmBalancing();
	void DSWalgorithmBackbone();

	//zwraca nastepnika
	Node *successor(Node * A);
	Node *minRBT(Node * r);

	void popNode(Node * X);

	Node * RBTree::seekNode(int val);

public:
	RBTree();
	~RBTree();

	void display(); //Wypisuje drzewo
	int readFromFile(); //Wczytuje dane do pliku
	int saveToFile(); //Zapisuje dane do pliku
	int push(int val) override; //Wstawia w�ze� o zadanej warto�ci
	int pop() override; //Usuwa w�ze� z pocz�tku / zadanej wartosci
	bool seek(int val); //Wyszukuje w�ze� o zadanej warto�ci
	int getSize() override { return size; }
	bool generateRandomData(int structureSize, int minIndex, int maxIndex) override;
	int randomValue(int minIndex, int maxIndex) override;
	void balance();
};

