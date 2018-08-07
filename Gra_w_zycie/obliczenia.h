/**
* \file obliczenia.h
* \brief Plik nagłówkowy modułu obliczenia
*
* Moduł obliczenia zawiera funkcje odpowiadające za realizację
* algorytmów oraz definicję struktury definiujacej
* parametry komórki gry w życie
*/

#ifndef OBLICZENIA_H
#define OBLICZENIA_H
#include <iostream>

///informacja o deklaracji zmiennych globalnych w tym module
/// W liczba wierszy obszaru gry
/// K liczba kolumny obszaru gry
extern int W,K;

/**
 * @brief struktura zawierająca parametry komórki gry w życie
 */
struct komorka
{
    /// liczba sąsiadów komórki
    int liczbaSasiadow;
    /// stan komórki
    char stan;
};

/**
 * @brief procedura ustawiająca opcje w menu na pierwszą
 * @param liczbaOpcji liczba opcji menu
 * @param tab tablica zawierająca znak przy wybranej opcji
 * @param aktualna aktualnie wybrana opcja
 */
void ustawWybranaOpcjaNaPierwsza(int liczbaOpcji,char tab[], int &aktualna);

/**
 * @brief procedura przesuwająca opcje w menu w górę
 * @param tablicaOpcji tablica zawierająca znak przy wybranej opcji
 * @param aktualnaOpcja aktualnie wybrana opcja
 * @param liczbaOpcji liczba opcji menu
 */
void przesunOpcjeWGore(char tablicaOpcji [], int &aktualnaOpcja, int liczbaOpcji);

/**
 * @brief procedura przesuwająca opcje w menu w dół
 * @param tablicaOpcji tablica zawierająca znak przy wybranej opcji
 * @param aktualnaOpcja aktualnie wybrana opcja
 * @param liczbaOpcji liczba opcji menu
 */
void przesunOpcjeWDol(char tablicaOpcji [], int &aktualnaOpcja, int liczbaOpcji);

/**
 * @brief funkcja tworząca tablicę komórek o wymiarach określonych przez zmienne globalne
 * @return  wskaźnik do tablicy komórek
 */
komorka **utworzTablice();

/**
 * @brief procedura wypełniająca tablicę danych w sposób losowy
 * @param tab wskaźnik do tablicy komórek
 */
void wypelnijTabliceLosowo(komorka **tab);

/**
 * @brief procedura usuwająca tablicę komórek
 * @param tab wskaźnik do tablicy komórek do usunięcia
 */
void usunTablice(komorka **tab);

/**
 * @brief główny algorytm programu realizujący symualcję gry w życie
 *  oraz obsługę opcji podczas trwania symulacji
 * @param turaWyswietlania tura od której ma być wyświetlana symulacja
 * @param tab wskaźnik do pierwotnej tablicy komórek, od której zaczyna się gra w życie
 */
void symulacjaGry(int turaWyswietlania, komorka **tab);

/**
 * @brief procedura zmieniająca wartości w tablicy komóre
 * oraz obsługująca przyciski wciskane przez użytkownika
 * @param tab wskaźnik do tablicy komórek
 */
void poruszanieSiePoTablicyDoUzupelnienia(komorka **tab);

/**
 * @brief funkcja sprawdzająca poprawiność nazwy pliku tekstowego podanej przez użytkownika
 * @param nazwa nazwa pliku tekstowego
 * @return informacja logiczna czy nazwa pliku jest poprawna
 */
bool sprawdzeniePoprawnosciNazwyPlikuTekstowego(std::string nazwa);

#endif // OBLICZENIA_H
