/**
* \file pliki.cpp
* \brief Plik implementacji modułu pliki
*
* Moduł pliki zawiera funkcje związanymi z zapisem
* i odczytem danych z plików
*/

#include <pliki.h>
#include <fstream>


int licznikWierszyWPliku(std::string nazwaPliku)
{
    int liczbaWierszy=0;
    std::ifstream odczyt(nazwaPliku.c_str());
    if(odczyt.good()==1)
    {
        while(!odczyt.eof())
        {
            getline(odczyt,nazwaPliku);
            liczbaWierszy++;
        }
    }
    else
    {
        odczyt.close();
        return -1;
    }
    odczyt.close();
    return liczbaWierszy;
}

std::string odczytTekstuZPliku(std::string nazwaPliku, int ktoraLinia)
{
    std::string linia;
    std::ifstream odczyt(nazwaPliku.c_str());
    if(odczyt.good()==1)
    {
        while(ktoraLinia!=0)
        {
            getline(odczyt,linia);
            ktoraLinia--;
        }
    }
    odczyt.close();
    return linia;
}

bool sprawdzeniePoprawnosciPlikuDoUtworzeniaTablicy(std::string nazwaPliku)
{
    int licznik=0;
    std::string linia;
    std::ifstream odczyt(nazwaPliku.c_str());
    if(odczyt.good()==1)
    {
        odczyt>>W;
        if( !odczyt )
        { // wpisano coś, co nie jest liczbą
            return false;
        }
        odczyt>>K;
        if( !odczyt )
        { // wpisano coś, co nie jest liczbą
            return false;
        }
        while(!odczyt.eof())
        {
            odczyt>>linia;
            for(int i=0;i<linia.size();i++)
            {
                if(linia[i]=='1' || linia[i]=='0')
                    licznik++;
            }
        }
        if(licznik==(W*K)) //sprawdzenie czy ilość opisanych komórek jest równa ilości zadeklarowanych komórek na początku pliku
        {
            odczyt.close();
            return true;
        }
        else
        {
            odczyt.close();
            return false;
         }
    }
    else
    {
        odczyt.close();
        return false;
    }
}


komorka **tworzenieTablicyZPliku(std::string nazwaPliku)
{
    komorka **tablica;
    std::string linia;
    std::ifstream odczyt(nazwaPliku.c_str());
    odczyt>>W;
    odczyt>>K;
    tablica=utworzTablice();
    int aktx=0,akty=0;
    while(!odczyt.eof())
    {
        odczyt>>linia;
        for(int i=0;i<linia.size();i++)
        {
            if(linia[i]=='1' || linia[i]=='0')
            {
                if(linia[i]=='1')
                    tablica[aktx][akty].stan='#';
                else
                    tablica[aktx][akty].stan=' ';
            }
            if(akty==K-1)
            {
                aktx++;
                akty=0;
            }
            else
                akty++;
        }
    }
    return tablica;
}

void zapisDoPliku(komorka **tablica, std::string nazwaPliku)
{

    std::ofstream zapis(nazwaPliku.c_str());
    zapis<<W<<" "<<K<<std::endl;
    for(int i=0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            if(tablica[i][j].stan == '#')
                zapis<<"1";
            else
                zapis<<"0";
        }
        if(i!=W-1)
            zapis<<std::endl;
    }
    zapis.close();
}
