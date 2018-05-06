#include <iostream>
#include <time.h>

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
    Node<T> *Head = nullptr;
public:

    List() {
        Head = nullptr;
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

    void firstInsert(T value, string Svalue = "", string symbol = "") {
        Head = new Node<T>(value, Svalue, symbol);
        Head->next = Head;
        return;
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
        srand(time(0)); // permite generar numeros aleatorios

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

    void print() {
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

int main() {
    int numJugadores;
    cout << "Ingrese el numero de jugadores: ";
    cin >> numJugadores;
    while (numJugadores < 2 or numJugadores > 4) {
        cout << "El juego es de 2 a 4 jugadores, ingrese otro numero: ";
        cin >> numJugadores;
    }
    List<int> *Baraja = new List<int>;
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

    List<int> *Jugadores = new List<int>[numJugadores];

    int i = rand() % 3 + 1;
    List<int> Jtemp = Jugadores[0];
    Jugadores[0] = Jugadores[i];
    Jugadores[i] = Jtemp;

    int numCartasR = (numJugadores == 2) ? 7 : 8;

    // Paso 1

    for (int i = 0; i < numJugadores; i++) {
        Jugadores[i].firstInsert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
        Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
    }

    for (int j = 0; j < numCartasR; j++) {
        for (int i = 0; i < numJugadores; i++) {
            Jugadores[i].insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
            Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
        }
    }

    //Paso 3


    delete Jugadores,Baraja;
    return 0;
}