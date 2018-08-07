/**
* \file lista.cpp
* \brief Plik implementacji modułu lista
*
* Moduł lista zawiera definicję struktury lista
* oraz funkcje tworzące i obsługujące listę
*/

#include <lista.h>

void stworzListe(ListaTablic *&glowa, komorka **tablica)
{
    glowa=new ListaTablic;
    glowa->nastepna=NULL;
    glowa->poprzednia=NULL;
    glowa->tab=tablica;
}

void dodajElementNaKoniecListy(ListaTablic *glowa, komorka **tablica)
{
    while(!(glowa->nastepna==NULL))
    {
        glowa=glowa->nastepna;
    }
    ListaTablic *nowy= new ListaTablic;
    nowy->nastepna=NULL;
    nowy->poprzednia=glowa;
    glowa->nastepna=nowy;
    nowy->tab=tablica;
}

void usunPierwszyElementListy(ListaTablic *&glowa)
{
    ListaTablic *tmp=glowa;
    glowa=glowa->nastepna;
    glowa->poprzednia=NULL;
    delete tmp;
}

void usunTabliceIListe(ListaTablic *&glowa)
{
    while(!(glowa->nastepna == NULL))
    {
        usunTablice(glowa->tab);
        usunPierwszyElementListy(glowa);
    }
    usunTablice(glowa->tab);
    delete glowa;
}

