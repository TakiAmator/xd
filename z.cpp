#include <iostream>

using namespace std;

// Klasa K1 reprezentuje pewien rodzaj kontenera na dwa stringi.
class K1
{
    string *p1;  // Wskaźnik na dynamicznie alokowaną tablicę stringów o rozmiarze 2.

public:

    // Konstruktor domyślny, alokuje pamięć dla dwóch stringów i ustawia je na "Brak".
    K1() : p1(new string[2]{"Brak", "Brak"}){}

    // Konstruktor przyjmujący dwa argumenty, ustawiający wartości stringów na podane argumenty.
    K1(string a, string b) : p1(new string[2]{a, b}){}

    // Konstruktor kopiujący, alokuje nową pamięć i kopiuje wartości stringów z obiektu K.
    K1(const K1 &K)
    {
        p1 = new string[2]{K.p1[0], K.p1[1]};
    }

    // Przeciążony operator <<, umożliwiający wydrukowanie obiektu na strumień wyjścia.
    friend ostream &operator<<(ostream &out, const K1 &K);

    // Metoda wypisz, wypisuje zawartość obiektu na strumień wyjścia.
    ostream &wypisz(ostream &out) const
    {
        return out << *p1 << " " << *(p1+1) << endl;
    }

    // Funkcja zwracająca referencję do jednego z elementów stringa w tablicy.
    string &P(int i)
    {
        return p1[i];
    }

    // Przeciążony operator przypisania, przypisuje wartości z obiektu K do obiektu.
    K1 &operator=(const K1 &K)
    {
        p1[0] = K.p1[0];
        p1[1] = K.p1[1];

        return *this;
    }
};

// Przeciążony operator << dla obiektu K1, wykorzystuje metodę wypisz.
ostream &operator<<(ostream &out, const K1 &K)
{
    return K.wypisz(out);
}

// Klasa K2 zawiera obiekt klasy K1, tworząc tym samym zagnieżdżoną strukturę.
class K2
{
    K1 dane;  // Obiekt klasy K1 wewnątrz klasy K2.

public:
    // Konstruktor domyślny, inicjalizuje obiekt klasy K1.
    K2() : dane(){}

    // Konstruktor przyjmujący dwa argumenty, inicjalizuje obiekt klasy K1 danymi argumentami.
    K2(string a, string b) : dane(a, b){}

    // Przeciążony operator << dla obiektu K2, wykorzystuje metodę wypisz obiektu K1.
    friend ostream &operator<<(ostream &out, const K2 &K);

    // Metoda wypisz, wypisuje zawartość obiektu na strumień wyjścia.
    ostream &wypisz(ostream &out) const
    {
        return out << dane << endl;
    }

    // Przeciążony operator indeksowania, umożliwia dostęp do elementów obiektu klasy K1.
    string &operator[](int i)
    {
        return dane.P(i);
    }
};

// Przeciążony operator << dla obiektu K2, wykorzystuje metodę wypisz.
ostream &operator<<(ostream &out, const K2 &K)
{
    return K.wypisz(out);
}

int main()
{
    // Tworzenie obiektów klasy K2 i korzystanie z różnych konstruktorów.
    K2 o1, o2;
    const K2 *wsk1 = new K2("Ala", "Ola");
    const K2 o3(*wsk1);

    // Wydrukowanie zawartości obiektów na ekran.
    cout << "o2 : " << o2 << endl;
    cout << "o3 : " << o3 << endl;
    cout << "***********" << endl;

    // Zwolnienie pamięci zaalokowanej dla obiektu wsk1.
    delete wsk1;
    wsk1 = 0;

    // Ponowne zaalokowanie pamięci i przypisanie obiektu o3 do o2.
    wsk1 = new K2(o3);
    o2 = *wsk1;
    cout << "o1 : " << o1 << endl;
    cout << "o2 : " << o2 << endl;
    cout << "***********" << endl;

    // Zwolnienie pamięci zaalokowanej dla obiektu wsk1.
    delete wsk1;
    wsk1 = 0;

    // Przypisanie nowego obiektu K2 do o1 i modyfikacja jego elementów.
    o1 = K2("Ewa", "Iza");
    cout << o1[0] << ", " << o1[1] << endl;
    o1[1] = "Jan";
    cout << o1[0] << ", " << o1[1] << endl;

    return 0;
}
