/**
* \file interfejs.h
* \brief Plik nagłówkowy modułu interfejs
*
* Moduł interfejs zawiera funkcje niezbędne
* do komunikacji z użytkownikiem poprzez konsolę
* tekstową
*/


#ifndef INTERFEJS_H
#define INTERFEJS_H
#include <obliczenia.h>

/// \brief procedura czyszcząca tekst w konsoli
void czyscEkran();

/// \brief procedura czekająca na wciśnięcie dowolnego przycisku
void kliknijDowolnyAbyPrzejscDalej();

/// \brief procedura wyświetlająca i obsługująca menu startowe
void menuStart();

/**
 * @brief procedura wyświetlająca grę oraz możliwe opcje podczas gry
 * @param tab wskaźnik do tablicy komórek gry w życie
 * @param tura tura gry
 * @param pauza informacja czy gra została spauzowana
 * @param liczbaPozostalychCofniec ilość cofnięć możliwych do wykonania
 * @param mozliwoscCofania informacja czy jest możliwe cofanie tury
 */
void wyswietlGre(komorka **tab,int tura, bool pauza, int liczbaPozostalychCofniec,bool mozliwoscCofania);

/**
 * @brief procedura wyświetlająca tablicę, którą wypełnia użytkownik
 * @param tab wskaźnik do tablicy zawierającej dane gry
 * @param aktx aktualna pozycja na współrzędnej X wybieranego pola w tablicy
 * @param akty aktualna pozycja na współrzędnej Y wybieranego pola w tablicy
 */
void wyswietlTabliceDoUzupelniania(komorka **tab,int aktx,int akty);


/// @brief procedura wyświetlajaca komunikaty końcowe
void koniecDzialaniaProgramu();

/// \brief procedura wyświetlająca komunikat proszący o nazwę pliku
void komunikatProszacyONazwePliku();

/// \brief procedura wyświetlająca komunikat informujący o pomyślnym zapisaniu danych do pliku
void komunikatZapisZakonczonySukcesem();

/// \brief procedura wyświetlająca komunikat informujący o niepomyślnym zapisaniu danych do pliku
void komunikatZapisZakonczonyNiepowodzeniem();

#endif // INTERFEJS_H
