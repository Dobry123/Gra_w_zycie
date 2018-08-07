/**
* \file pliki.h
* \brief Plik nagłówkowy modułu pliki
*
* Moduł pliki zawiera funkcje związanymi z zapisem
* i odczytem danych z plików
*/

#ifndef PLIKI_H
#define PLIKI_H
#include <obliczenia.h>

/**
 * @brief funkcja odczytująca linię tekstu z pliku
 * @param nazwaPliku nazwa pliku do odczytu
 * @param ktoraLinia linia, która ma być odczytana
 * @return linia tekstu
 */
std::string odczytTekstuZPliku(std::string nazwaPliku, int ktoraLinia);

/**
 * @brief funkcja licząca wiersze w pliku
 * @param nazwaPliku nazwa pliku do odczytu
 * @return ilość wierszy w pliku
 */
int licznikWierszyWPliku(std::string nazwaPliku);

/**
 * @brief funkcja sprawdzająca poprawność pliku tekstowego, z którego będzie
 * utworzona tablica do gry w życie
 * @param nazwaPliku nazwa pliku do odczytu
 * @return informacja logiczna o poprawności pliku tekstowego
 */
bool sprawdzeniePoprawnosciPlikuDoUtworzeniaTablicy(std::string nazwaPliku);

/**
 * @brief funkcja tworząca tablicę komórek z danych odczytanych z pliku
 * @param nazwaPliku nazwa pliku, z którego będzie utworzona tablica
 * @return wskaźnik do utworzonej tablicy komórek
 */
komorka **tworzenieTablicyZPliku(std::string nazwaPliku);

/**
 * @brief procedura zapisująca stan symulacji gry w życie do pliku
 * @param tablica wskaźnik do tablicy komórek do zapisu
 * @param nazwaPliku nazwa pliku do zapisu
 */
void zapisDoPliku(komorka **tablica, std::string nazwaPliku);

#endif // PLIKI_H
