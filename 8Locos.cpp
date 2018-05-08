#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template <typename T>
class Node {
public:
	T value;
	string Svalue; // numero o letra
	string symbol; // 1 de los 4 simbolos
	
	Node<T> *next;
	
	Node(T value, string Svalue = "", string symbol = "", Node<T> *next = nullptr) {
		this->value = value;
		this->Svalue = Svalue;
		this->symbol = symbol;
		this->next = next;
	}
	
	~Node() {
		next = nullptr;
	}
};

template <typename T>
class List {
	Node<T> *Head;
	T puntaje;
public:
	
	List() {
		Head = nullptr;
		this->puntaje = 0;
	}
	
	bool find(T value, Node<T> **&next, string Svalue = "", string symbol = "") {
		next = &(Head->next);
		while (*next != Head) {
			if ((*next)->value == value and (*next)->Svalue == Svalue and (*next)->symbol == symbol)
				return true;
			next = &(*next)->next;
		}
		return false;
	}
	
	void remove(T value, string Svalue = "", string symbol = "") {
		if (Head != 0) {
			Node<T> **next;
			if (Head->value == value and Head->Svalue == Svalue and Head->symbol == symbol) {
				if (Head->next == Head) {
					delete Head;
					Head = nullptr;
					return;
				}
				Node<T> *ultimo = Head;
				for (; ultimo->next != Head; ultimo = ultimo->next);
				Node<T> *temp = Head->next;
				delete Head;
				Head = temp;
				ultimo->next = Head;
				return;
			}
			if (find(value, next, Svalue, symbol)) {
				Node<T> *temp = (*next)->next;
				delete *next;
				*next = temp;
			}
		}
	}
	
	void insert(T value, string Svalue = "", string symbol = "") {
		//cout<<"Head: "<<Head<<endl;
		if (Head == 0) {
			Head = new Node<T>(value, Svalue, symbol);
			Head->next = Head;
			return;
		}
		
		Node<T> **next = &(Head->next);
		while (*next != Head) {
			next = &(*next)->next;
		}
		*next = new Node<T>(value, Svalue, symbol, *next);
	}
	
	void sort() {
		srand(time(NULL)); // permite generar numeros aleatorios
		
		Node<T> *nodo1 = Head;
		Node<T> *nodo2 = Head;
		for (int NumBarajeos = 0; NumBarajeos < 3; NumBarajeos++) {
			for (int PosCartaBaraja = 1; PosCartaBaraja <= 52; PosCartaBaraja++) {
				for (int PosAdelante = rand() % 51 + 1; PosAdelante > 0; PosAdelante--) {
					nodo2 = nodo2->next;
				}
				int temp1 = nodo1->value;
				string temp2 = nodo1->Svalue;
				string temp3 = nodo1->symbol;
				
				nodo1->value = nodo2->value;
				nodo1->Svalue = nodo2->Svalue;
				nodo1->symbol = nodo2->symbol;
				
				nodo2->value = temp1;
				nodo2->Svalue = temp2;
				nodo2->symbol = temp3;
			}
		}
	}
	
	void sumPuntaje(T puntaje) {
		this->puntaje += puntaje;
	}
	
	void cFind(int cartaSelec) {
		Node<T> *next = Head;
		
		for (; cartaSelec > 1; cartaSelec--) {
			next = next->next;
		}
		remove(next->value, next->Svalue, next->symbol);
	}
	
	bool comprobarMazo() {
		return !!Head;
	}
	
	int getPuntaje() {
		int puntajeTotal = 0;
		puntajeTotal += Head->value;
		for (Node<T> **next = &Head->next; *next != Head; next = &(*next)->next)
			puntajeTotal += (*next)->value;
		return puntajeTotal;
	}
	
	void print() {
		if (Head != nullptr) {
			//cout << endl << "Elementos dentro de la lista" << endl << endl;
			if (Head != 0) {
				cout << endl << "Elementos dentro de la lista" << endl << endl;
				Node<T> *temp = Head;
				do {
					cout << "value: " << temp->value;
					if (temp->Svalue != "" and temp->symbol != "") {
						cout << " Svalue: " << temp->Svalue
							<< " Symbol: " << temp->symbol << endl;
					}
					/*cout << "-> " << temp->next->value << endl;*/
					temp = temp->next;
				} while (temp != Head);
			}
		}
	}
	
	T getValue() {
		return Head->value;
	}
	
	string getSvalue() {
		return Head->Svalue;
	}
	
	string getSymbol() {
		return Head->symbol;
	}
	
	~List() {
		if (Head != 0) {
			Node<T> *temp = Head;
			Node<T> *next;
			Node<T> *ultimo = Head;
			for (; ultimo->next != Head; ultimo = ultimo->next);
			ultimo->next = nullptr;
			do {
				next = temp->next;
				delete temp;
				temp = next;
			} while (temp);
		}
	}
};

void nums_al(int n, int a[]) {
	int sinrep[52];
	for (int i = 0; i < 52; i++) {
		sinrep[i] = i;
	}
	random_shuffle(sinrep, sinrep + 52);
	
	for (int i = 0; i < n; i++) {
		a[i] = sinrep[i];
		
	}
}

void crear_baraja(int n, List<int> *&baraja) { ///tam baraja
	srand(time(NULL));
	int a[n];
	nums_al(n, a);
	for (int i = 0; i < n; i++) {
		int x = i % 13 + 1;
		string Svalue = (x == 1) ? "A" : (x == 11) ? "J" : (x == 12) ? "Q" : (x == 13) ? "K" : to_string(
																										 x); //El numero de la carta
		string symbol = (a[i] < 13) ? "Espadas" : (a[i] < 26) ? "Corazones" : (a[i] < 39) ? "Rombo" : "Trebol";
		//cout<<"valores a ingresar: "<<x<<" "<<Svalue<<" "<<symbol<<endl;
		baraja->insert(x, Svalue, symbol);
	}
	baraja->sort();
}

int main() {
	int indiceJugador = 0;
	int numJugadores;
	
	cout << "Ingrese el numero de jugadores: ";
	cin >> numJugadores;
	while (numJugadores < 2 or numJugadores > 4) {
		cout << "El juego es de 2 a 4 jugadores, ingrese otro numero: ";
		cin >> numJugadores;
	}
	List<int> *Baraja = new List<int>;
	
	crear_baraja(52, Baraja);
	Baraja->print();
	cout << "repartiendo cartas" << endl;
	
	/// CREANDO JUGADORES
	
	List<int> *array_jug[numJugadores];
	for (int i = 0; i < numJugadores; i++)
		array_jug[i] = new List<int>();
	
	///end
	
	int num_cartas;
	if (numJugadores > 2)num_cartas = 8; else num_cartas = 7;
	
	
	for (int j = 0; j < num_cartas; j++) {
		for (int i = 0; i < numJugadores; i++) {
			array_jug[i]->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
			Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
		}
	}
	// PASO 3
	List<int> *pilaDescarte = new List<int>;
	while (Baraja->getValue() == 8) {
		Baraja->sort();
	}
	pilaDescarte->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
	Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
	
	// PASO 4
	// Si sale un ocho, se usa como comodin y se pasa de turno
	
	/*for (int i = 0; i < numJugadores; i++) {
	cout << "jugador" << i << ": " << endl;
	array_jug[i]->print();
	}*/
	array_jug[indiceJugador]->print();
	
	cout << "carta en la pila de descarte: " << pilaDescarte->getSvalue() << " " << pilaDescarte->getSymbol() << endl;
	
	for (int i = 0; i < 52; i++) {
		int x = i % 13 + 1;
		string Svalue = (x == 1) ? "A" : (x == 11) ? "J" : (x == 12) ? "Q" : (x == 13) ? "K" : to_string(
																										 x); //El numero de la carta
		
		string symbol = (i < 13) ? "Espadas" : (i < 26) ? "Corazones" : (i < 39) ? "Rombo"
			: "Trebol"; //El simbolo de la carta
		Baraja->insert(x, Svalue, symbol);
	}
	
	//    Baraja->print();
	Baraja->sort();
	//cout << "\n\nLista barajeada\n";
	//Baraja->print();
	
	indiceJugador--;
	if (indiceJugador < 0) indiceJugador += 3;
	int cartaSelec;
	
	cout << "Seleccione una carta o presione 0 para sacar una carta de la baraja:" << endl;
	cin >> cartaSelec;
	if (cartaSelec == 0) {
		array_jug[indiceJugador]->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
		Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
	} else {
		array_jug[indiceJugador]->cFind(cartaSelec);
	}
	
	// PASO 7
	bool vacio = array_jug[indiceJugador]->comprobarMazo();
	int puntajeTotal;
	if(!vacio)
	{
		for(int i=0;i<numJugadores;i++)
		{
			if(i==indiceJugador) continue;
			puntajeTotal+=array_jug[i]->getPuntaje();
		}
	}
	
	cout << "Tu baraja" << endl;
	array_jug[indiceJugador]->print();
	
	cout << "Mano de cada jugador\n\n";
	
	for (int i = 0; i < numJugadores; i++) {
		cout << "jugador" << i << ": " << endl;
		array_jug[i]->print();
	}
	for (int i = 0; i < numJugadores; i++) {
		delete array_jug[i];
	}
	delete pilaDescarte, Baraja;
	return 0;
}
