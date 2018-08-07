/**
* \file lista.h
* \brief Plik nagłówkowy modułu lista
*
* Moduł lista zawiera definicję struktury lista
* oraz funkcje tworzące i obsługujące listę
*/

#ifndef LISTA_H
#define LISTA_H
#include <obliczenia.h>

/**
 * @brief Struktura przechowująca kolejne tablice komórek gry w życie
 */
struct ListaTablic
{
    /// wskaźnik do tablicy komórek gry w życie
    komorka **tab;
    /// wskaźnik do następnego elementu listy
    ListaTablic *nastepna;
    /// wskaźnik do poprzedniego elementu listy
    ListaTablic *poprzednia;
};

/**
 * @brief procedura tworząca listę
 * @param glowa wskaźnik do elementu który stanie się przerwszym elementem listy
 * @param tablica wskaźnik do tablicy komórek gry w życie, która będzie danymi
 * tworzonego elementu listy
 */
void stworzListe(ListaTablic *&glowa, komorka **tablica);

/**
 * @brief procedura dodająca element na koniec listy
 * @param glowa wskaźnik do pierwszego elementu listy
 * @param tablica wskaźnik do tablicy komórek gry w życie, która będzie danymi
 * tworzonego elementu listy
 */
void dodajElementNaKoniecListy(ListaTablic *glowa, komorka **tablica);

/**
 * @brief procedura usuwająca pierwszy element listy
 * @param glowa wskaźnik do pierwszego elementu listy
 */
void usunPierwszyElementListy(ListaTablic *&glowa);

/**
 * @brief procedura usuwająca całą listę wraz z danymi w elementach
 * @param glowa wskaźnik do pierwszego elementu listy
 */
void usunTabliceIListe(ListaTablic *&glowa);


#endif // LISTA_H
