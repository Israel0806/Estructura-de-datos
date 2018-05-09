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

    bool remove(T value, string Svalue = "", string symbol = "") {
        if (Head != 0) {
            Node<T> **next;
            if (Head->value == value and Head->Svalue == Svalue and Head->symbol == symbol) {
                if (Head->next == Head) {
                    delete Head;
                    Head = nullptr;
                    return true;
                }
                Node<T> *ultimo = Head;
                for (; ultimo->next != Head; ultimo = ultimo->next);
                Node<T> *temp = Head->next;
                delete Head;
                Head = temp;
                ultimo->next = Head;
                return true;
            }
            if (find(value, next, Svalue, symbol)) {
                Node<T> *temp = (*next)->next;
                delete *next;
                *next = temp;
                return true;
            }
        }
        return false;
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
                for (int PosAdelante = rand()%51 + 1; PosAdelante > 0; PosAdelante--) {
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

    bool cFind(int cartaSelec) {
        Node<T> *next = Head;

        for (; cartaSelec > 1; cartaSelec--) {
            next = next->next;
        }
        return remove(next->value, next->Svalue, next->symbol);
    }

    bool comprobarMazo() {
        return !!Head;
    }

    int getValorCartas() {
        int puntajeTotal = 0;
        puntajeTotal += Head->value;
        for (Node<T> **next = &Head->next; *next != Head; next = &(*next)->next)
            puntajeTotal += (*next)->value;
        return puntajeTotal;
    }

    void add_puntaje(int x)
    {
        puntaje += x;
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
    void RepartirBaraja(int num_cartas, List<T>*& Baraja) {
        for (int j = 0; j < num_cartas; j++) {
            Baraja->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
            Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());

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
        baraja->insert((x == 8) ? 50 : (x > 10) ? 10 : x, Svalue, symbol);
    }
    baraja->sort();
}

int main() {
    int numJugadores;
    int PuntajeGanador[3] = {100, 150, 200};
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

    /// *******************************************CREANDO JUGADORES

    List<int> *array_jug[numJugadores];
    for (int i = 0; i < numJugadores; i++)
        array_jug[i] = new List<int>();

    ///********************************************end

    int num_cartas;
    if (numJugadores > 2)num_cartas = 8; else num_cartas = 7;

    ///***********************REPARTIR CARTAS

    int jugadorActual = 0;
    int puntajeTotal, puntajes[numJugadores];
    for (int j = 0; j < num_cartas; j++) {
        for (int i = 0; i < numJugadores; i++) {
            array_jug[i]->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
            Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
        }
    }
    /// ********************************PASO 3
    List<int> *pilaDescarte = new List<int>;
    while (Baraja->getValue() == 8) {
        Baraja->sort();
    }
    /// ******************************End PASO 3

    pilaDescarte->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
    Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
    bool terminar_juego = 1;
    while (terminar_juego) { //////////while general
        /// *********************************CAMBIO JUGADOR
        jugadorActual--;
        if (jugadorActual < 0) jugadorActual += numJugadores - 1;
        array_jug[jugadorActual]->print();
        /// ************************PASO 4

        cout << "BARAJA JUGADOR: " << jugadorActual + 1 << endl;
        array_jug[jugadorActual]->print();
        cout << endl;
        cout << "///////////////////////////////////////////////////////////" << endl;
        cout << "carta en la pila de descarte: " << pilaDescarte->getSvalue() << " " << pilaDescarte->getSymbol()
             << endl;


        /// ************************Paso 5 y 6
        int cartaSelec;
        bool cartaValida = 0;
        while (cartaValida == 0) {
            cout << "Seleccione una carta o presione 0 para sacar una carta de la baraja:" << endl;
            cin >> cartaSelec;
            if (cartaSelec == 0) {
                cout << "BARAJA*******************************************************************************\n";
                if (Baraja->comprobarMazo() == 0) {
                    cartaValida = 1;
                    continue;
                }
                array_jug[jugadorActual]->insert(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
                cartaValida = Baraja->remove(Baraja->getValue(), Baraja->getSvalue(), Baraja->getSymbol());
            } else {
                cartaValida = array_jug[jugadorActual]->cFind(cartaSelec);//////
            }
        }

        /// ***********************PASO 7
        
        if (Baraja->comprobarMazo()) {
            int menorPuntajePos, menorPuntaje = array_jug[0]->getValorCartas();
            puntajes[0] = menorPuntaje;
            menorPuntajePos = 0;
            puntajeTotal += array_jug[0]->getValorCartas();
            for (int i = 1; i < numJugadores; i++) {
                puntajeTotal += array_jug[0]->getValorCartas();
                puntajes[i] = array_jug[i]->getValorCartas(); ///puntaje de cada jugador
                if (menorPuntaje > array_jug[i]->getValorCartas()) {
                    menorPuntaje = array_jug[i]->getValorCartas();
                    menorPuntajePos = i;
                }
            }
            if((array_jug[jugadorActual]->getValorCartas() > PuntajeGanador[numJugadores])) terminar_juego=0;
            array_jug[menorPuntajePos]->add_puntaje(puntajeTotal);
        }
        int puntaje_tot=0;
        if(array_jug[jugadorActual]->comprobarMazo() == 0)
        {
            for (int i = 0; i < numJugadores; i++) {
                puntaje_tot += array_jug[i]->getValorCartas(); ///puntaje de cada jugador
            }
            //array_jug[jugadorActual]->add_puntaje() = puntaje_tot;
            cout<<"PUNTAJE DEL JUGADOR SIN CARTAS: "<<puntaje_tot<<endl;
            delete Baraja;
            for (int i = 0; i < numJugadores; i++) {
                delete array_jug[i];
            }
            for (int i=0;i<numJugadores;i++){
                array_jug[i]->RepartirBaraja(num_cartas,Baraja);
            }
            crear_baraja(52, Baraja);

            if(array_jug[jugadorActual]->getValorCartas() > PuntajeGanador[numJugadores]) terminar_juego=0;

        }
        /*else if(array_jug[jugadorActual]->comprobarMazo())
        {
            puntajeTotal =  ;
        }*/
    }
    /// ***************************delete everything
    for (int i = 0; i < numJugadores; i++) {
        delete array_jug[i];
    }
    delete pilaDescarte, Baraja;
    return 0;
}
