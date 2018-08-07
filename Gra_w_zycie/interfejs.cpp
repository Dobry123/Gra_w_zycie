/**
* \file interfejs.cpp
* \brief Plik implementacji modułu interfejs
*
* Moduł interfejs zawiera funkcje niezbędne
* do komunikacji z użytkownikiem poprzez konsolę
* tekstową
*/

#include <interfejs.h>
#include <iomanip>
#include <conio.h>
#include <pliki.h>
#include <windows.h>
//#include <cstdlib>
using namespace std;

/// zmienna globalna odpowiadająca za kolor wyświetlanego tekstu w konsoli
HANDLE Kolor;

/// procedura wyświetlająca i obsługująca menu główne
void menu1();

/// procedura wyświetlająca i obsługująca menu ustalenia parametrów początkowych symulacji
void menu2();

/// procedura wyświetlająca i obsługująca menu wczytywania stanu początkowego z pliku
void menuOpcjaWczytanieZPliku();

/// procedura wyświetlająca i obsługująca menu wczytywania stanu początkowego z poziomu konsoli
void menuOpcjaStanPoczatkowyPoziomKonsoli();

/// procedura wyświetlająca i obsługująca menu ustalenia stanu początkowego losowo
void opcjaWypelnijLosowo();

/**
 * @brief  procedura wyświetlająca i obsługująca menu do wybrania momentu wyświetlania symulacji
 * @param tablica wskaźnik do tablicy komórek
 */
void menuPodajMomentWyswietlania(komorka **tablica);

///  procedura wyświetlająca i obsługująca menu do samodzielnego wypełniania tablicy komorek
void opcjaWypelnianieSamodzielne();

/**
 * @brief procedura wyświetlająca tekst z pliku
 * @param nazwaPliku nazwa pliku do odczytu
 */
void wyswietlDaneZPliku(string nazwaPliku);

/// procedura wyświetlająca i obsługująca menu do wczytywania stanu początkowego z pliku
void opcjaWczytanieZPliku();


void kliknijDowolnyAbyPrzejscDalej()
{
    _getch();
}

void czyscEkran()
{
    system("cls");
}

void menuStart()
{
    Kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( Kolor, 10 );
    cout<<"WITAJ W AUTOMACIE KOMORKOWYM"<<endl;
    SetConsoleTextAttribute( Kolor, 14 );
    cout<<"GRA W ZYCIE"<<endl<<endl;
    SetConsoleTextAttribute( Kolor, 7 );
    cout<<"Strzalki - poruszanie sie po menu"<<endl<<"Enter - wybor danej opcji"<<endl<<endl;
    SetConsoleTextAttribute( Kolor, 11 );
    cout<<"Kliknij dowolny przycisk, aby przejsc dalej!"<<endl;
    kliknijDowolnyAbyPrzejscDalej();
    menu1();
}

void menu1()
{
    char tablicaOpcji [4];
    int aktualnaOpcja;
    ustawWybranaOpcjaNaPierwsza(4,tablicaOpcji,aktualnaOpcja);
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==13)) //enter
    {
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 90 );
        cout<<"MENU"<<endl<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[0];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Historia automatow komorkowych"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[1];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Zasady symulacji Gra w Zycie"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[2];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Wlaczam automat komorkowy GRA W ZYCIE"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[3];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Wyjscie"<<endl;
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w górę
                przesunOpcjeWGore(tablicaOpcji,aktualnaOpcja,4);
                break;
            case 80: //strzałka w dół
                przesunOpcjeWDol(tablicaOpcji,aktualnaOpcja,4);
                break;
            }
        }
        else
            wartoscPolecenia=polecenie;
    }
    switch(aktualnaOpcja)
    {
    case 0:
        wyswietlDaneZPliku("historiaAutomatow.txt");
        break;
    case 1:
        wyswietlDaneZPliku("zasady.txt");
        break;
    case 2:
        menu2();
        break;
    case 3:
        koniecDzialaniaProgramu();
        break;
    }
}

void wyswietlDaneZPliku(string nazwaPliku)
{
    czyscEkran();
    int iloscWierszy = licznikWierszyWPliku(nazwaPliku);
    if(iloscWierszy==-1)
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<"Nie udalo sie odczytac danych z pliku"<<endl;
    }
    for(int i=1;i<=iloscWierszy;i++)
    {
        string linia=odczytTekstuZPliku(nazwaPliku,i);
        SetConsoleTextAttribute( Kolor, 7 );
        cout<<linia<<endl;
    }
    SetConsoleTextAttribute( Kolor, 11 );
    cout<<endl<<"WCISNIJ ESC ABY POWROCIC";
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==27)) //ESC
    {
        wartoscPolecenia=getch();
    }
    menu1();

}

void menu2()
{
    char tablicaOpcji [3];
    int aktualnaOpcja;
    ustawWybranaOpcjaNaPierwsza(3,tablicaOpcji,aktualnaOpcja);
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==13))
    {
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 90 );
        cout<<"Pora na ustalenie stanu poczatkowego symulacji:"<<endl<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[0];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Zrobie to z poziomu konsoli"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[1];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Wczytam z pliku"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[2];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Powrot"<<endl;
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w górę
                przesunOpcjeWGore(tablicaOpcji,aktualnaOpcja,3);
                break;
            case 80: //strzałka w dół
                przesunOpcjeWDol(tablicaOpcji,aktualnaOpcja,3);
                break;
            }
        }
        else
            wartoscPolecenia=polecenie;
    }
    switch(aktualnaOpcja)
    {
    case 1:
        menuOpcjaWczytanieZPliku();
        break;
    case 2:
        menu1();
        break;
    case 0:
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 10 );
        cout<<"Podaj wymiary obszaru symalacji: "<<endl<<endl;
        do
        {
            SetConsoleTextAttribute( Kolor, 14 );
            cout<<"Podaj liczbe wierszy: ";
            SetConsoleTextAttribute( Kolor, 12 );
            cin>>W;
            if( !cin )
            { // wpisano coś, co nie jest liczbą
                cin.clear(); // czyść flagi błędu strumienia
                cin.sync(); // czyść bufor strumienia
            }
            else // wpisano liczbę
                if(W>0)
                   break;
        }while(true);
        do
        {
            SetConsoleTextAttribute( Kolor, 14 );
            cout<<"Podaj liczbe kolumn: ";
            SetConsoleTextAttribute( Kolor, 12 );
            cin>>K;
            if( !cin )
            { // wpisano coś, co nie jest liczbą
                cin.clear(); // czyść flagi błędu strumienia
                cin.sync(); // czyść bufor strumienia
            }
            else // wpisano liczbę
                if(K>0)
                    break;
        }while(true);
        menuOpcjaStanPoczatkowyPoziomKonsoli();
        break;
    }
}

void menuOpcjaWczytanieZPliku()
{
    char tablicaOpcji [2];
    int aktualnaOpcja;
    ustawWybranaOpcjaNaPierwsza(2,tablicaOpcji,aktualnaOpcja);
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==13)) //enter
    {
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[0];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Podam nazwe pliku"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[1];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Powrot"<<endl;
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w górę
                przesunOpcjeWGore(tablicaOpcji,aktualnaOpcja,2);
                break;
            case 80: //strzałka w dół
                przesunOpcjeWDol(tablicaOpcji,aktualnaOpcja,2);
                break;
            }
        }
        else
            wartoscPolecenia=polecenie;
    }
    if(aktualnaOpcja==1)
        menu2();
    else
        opcjaWczytanieZPliku();
}

void opcjaWczytanieZPliku()
{
    string nazwaPliku;
    czyscEkran();
    SetConsoleTextAttribute( Kolor, 15 );
    cout<<"Upewnij sie ze pierwszy wiersz pliku zawiera liczbe wierszy oraz kolumn odzielone spacja."<<endl
       <<"W kolejnych wierszach powinny znajdowac sie wylacznie znaki '1' oraz '0' (inne nie beda liczone)."<<endl
       <<"1 oznacza komorke zywa, zas 0 - komorke martwa."<<endl
      <<"Wiersze moga wystepowac w kolejnych wierszach pliku."<<endl
     <<"Ostatni wiersz nie moze byc pusty lub zawierac tylko spacje."<<endl;
    komunikatProszacyONazwePliku();
    getline(cin,nazwaPliku);
    if(sprawdzeniePoprawnosciNazwyPlikuTekstowego(nazwaPliku) && sprawdzeniePoprawnosciPlikuDoUtworzeniaTablicy(nazwaPliku))
    {
        komorka **tablica;
        tablica=tworzenieTablicyZPliku(nazwaPliku);
        menuPodajMomentWyswietlania(tablica);
    }
    else
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<"Cos poszlo nie tak. Sprawdz czy plik istnieje i czy spelnia okreslowe warunki."<<endl<<endl;
        SetConsoleTextAttribute( Kolor, 11 );
        cout<<"Kliknij dowolny przycisk, aby wrocic.";
        kliknijDowolnyAbyPrzejscDalej();
        menuOpcjaWczytanieZPliku();
    }
}

void menuOpcjaStanPoczatkowyPoziomKonsoli()
{
    char tablicaOpcji [3];
    int aktualnaOpcja;
    ustawWybranaOpcjaNaPierwsza(3,tablicaOpcji,aktualnaOpcja);
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==13)) //enter
    {
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[0];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Wypelnij losowo"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[1];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Sam zdecyduje o stanie poczatkowym"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[2];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Powrot"<<endl;
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w górę
                przesunOpcjeWGore(tablicaOpcji,aktualnaOpcja,3);
                break;
            case 80: //strzałka w dół
                przesunOpcjeWDol(tablicaOpcji,aktualnaOpcja,3);
                break;
            }
        }
        else
            wartoscPolecenia=polecenie;
    }
    switch(aktualnaOpcja)
    {
    case 0:
        opcjaWypelnijLosowo();
        break;
    case 1:
        opcjaWypelnianieSamodzielne();
        break;
    case 2:
        menu2();
        break;
    }
}

void opcjaWypelnijLosowo()
{
    komorka **tablica=utworzTablice();
    wypelnijTabliceLosowo(tablica);
    menuPodajMomentWyswietlania(tablica);
}

void wyswietlGre(komorka **tab,int tura, bool pauza, int liczbaPozostalychCofniec,bool mozliwoscCofania)
{
    if(pauza == true)
    {
        if(mozliwoscCofania==false)
        {
            SetConsoleTextAttribute( Kolor, 11 );
            cout<<"PAUZA \t Tura: "<<tura<<" \t P wznowienie \t\t Z zapisz stan do pliku \t C cofnij(0) \t ESC aby wyjsc"<<endl;
        }
        else
        {
            SetConsoleTextAttribute( Kolor, 11 );
            cout<<"PAUZA \t Tura: "<<tura<<" \t P wznowienie \t\t Z zapisz stan do pliku \t C cofnij("<<liczbaPozostalychCofniec
             <<") \t ESC aby wyjsc"<<endl;
        }
    }
    else
    {
        SetConsoleTextAttribute( Kolor, 11 );
        cout<<"Tura: "<<tura<<" \t P pauza \t F przyspiesz \t S zwolnij \t ESC aby wyjsc"<<endl;
    }
    for(int i=0;i<K+2;i++) //rysowanie ramki
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<"<";
    }
    cout<<endl;
    for(int i=0;i<W;i++)
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<"|"; //rysowanie ramki
        for(int j=0;j<K;j++)
        {
            SetConsoleTextAttribute( Kolor, 10 );
            cout<<setw(2)<<tab[i][j].stan; //rysowanie komórki
        }
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<"|"<<endl; //rysowanie ramki
    }
    for(int i=0;i<K+2;i++) //rysowanie ramki
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<">";
    }
}

void menuPodajMomentWyswietlania(komorka **tablica)
{
    int tura=1;
    char tablicaOpcji [2];
    int aktualnaOpcja;
    ustawWybranaOpcjaNaPierwsza(2,tablicaOpcji,aktualnaOpcja);
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==13)) //enter
    {
        czyscEkran();
        SetConsoleTextAttribute( Kolor, 90 );
        cout<<"Podaj ture od ktorej ma byc wyswietlana symulacja:"<<endl<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[0];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Zacznij od poczatku"<<endl;
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<tablicaOpcji[1];
        SetConsoleTextAttribute( Kolor, 14 );
        cout<<" Zacznij od pewnego momentu"<<endl;
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w górę
                przesunOpcjeWGore(tablicaOpcji,aktualnaOpcja,2);
                break;
            case 80: //strzałka w dół
                przesunOpcjeWDol(tablicaOpcji,aktualnaOpcja,2);
                break;
            }
        }
        else
            wartoscPolecenia=polecenie;
    }
    if(aktualnaOpcja==0)
        symulacjaGry(tura,tablica);
    else
    {
        czyscEkran();
        do
        {
            SetConsoleTextAttribute( Kolor, 10 );
            cout<<"Tura od ktorej zacznie sie wyswietlanie to: ";
            SetConsoleTextAttribute( Kolor, 15 );
            cin>>tura;
            if( !cin )
            { // wpisano coś, co nie jest liczbą
                cin.clear(); // czyść flagi błędu strumienia
                cin.sync(); // czyść bufor strumienia
            }
            else // wpisano liczbę
                if(tura>0)
                    break;
        }while(true);
        symulacjaGry(tura,tablica);
    }
}

void opcjaWypelnianieSamodzielne()
{
    komorka **tablica=utworzTablice();
    for(int i=0;i<W;i++)
        for(int j=0;j<K;j++)
            tablica[i][j].stan=' ';
    czyscEkran();
    poruszanieSiePoTablicyDoUzupelnienia(tablica);
    menuPodajMomentWyswietlania(tablica);
}

void wyswietlTabliceDoUzupelniania(komorka **tab, int aktx, int akty)
{
    SetConsoleTextAttribute( Kolor, 11 );
    cout<<"Strzalki - poruszanie \t\t ENTER - zmien wartosc \t L wylosuj \t ESC - zatwierdz i wyjdz"<<endl;
    SetConsoleTextAttribute( Kolor, 12 );
    for(int i=0;i<K+2;i++) //rysowanie ramki
        cout<<setw(2)<<"<";
    cout<<endl;
    for(int i=0;i<W;i++)
    {
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<"|"; //rysowanie ramki
        for(int j=0;j<K;j++)
        {
            if(i==aktx && j==akty)
            {
                if(tab[i][j].stan==' ')
                {
                    SetConsoleTextAttribute( Kolor, 14 );
                    cout<<setw(2)<<'^'; //rysowanie znaku do ożywnienia komórki
                }
                else
                {
                    SetConsoleTextAttribute( Kolor, 13);
                    cout<<setw(2)<<'v'; //rysowanie znaku do uśmiercenia komórki
                }
            }
            else
            {
                SetConsoleTextAttribute( Kolor, 10 );
                cout<<setw(2)<<tab[i][j].stan; //rysowanie komórki
            }
        }
        SetConsoleTextAttribute( Kolor, 12 );
        cout<<setw(2)<<"|"<<endl; //rysowanie ramki
    }
    SetConsoleTextAttribute( Kolor, 12 ); //rysowanie ramki
    for(int i=0;i<K+2;i++)
        cout<<setw(2)<<">";
}

void komunikatProszacyONazwePliku()
{
    SetConsoleTextAttribute( Kolor, 10 );
    cout<<"Podaj nazwie pliku tekstowego (PAMIETAJ O ROZSZERZENIU .txt): "<<endl;
    SetConsoleTextAttribute( Kolor, 14 );
}

void komunikatZapisZakonczonySukcesem()
{
    SetConsoleTextAttribute( Kolor, 10 );
    cout<<"Udalo sie zapisac stan symulacji do pliku!"<<endl;
    SetConsoleTextAttribute( Kolor, 11 );
    cout<<"Wcisnij dowolny przycisk, aby powrocic!";
}

void komunikatZapisZakonczonyNiepowodzeniem()
{
    SetConsoleTextAttribute( Kolor, 12 );
    cout<<"Nie udalo sie zapisac stan symulacji do pliku!"<<endl<<"Sprawdz poprawnosc nazwy pliku."<<endl<<endl;
    SetConsoleTextAttribute( Kolor, 11 );
    cout<<"Wcisnij dowolny przycisk, aby powrocic!";
}

void koniecDzialaniaProgramu()
{
    czyscEkran();
    SetConsoleTextAttribute( Kolor, 10 );
    cout<<"Dziekuje za skorzystanie z programu."<<endl;
    SetConsoleTextAttribute( Kolor, 7 );
    cout<<"Program zostal stworzony jako projekt na zaliczenia przedmiotu:"<<endl<<"Zasady programowania "
          "strukturalnego II na wydziale Mechatroniki Politechniki Warszawskiej"<<endl
        <<"Autorem jest: Mateusz Szczygielski"<<endl<<endl<<endl;

    SetConsoleTextAttribute( Kolor, 14 );
    cout<<"Aby jeszcze raz uruchomic program wcisnij ENTER"<<endl<<"Kazdy inny przycisk zamyka okno";
    char przycisk;
    przycisk=getch();
    if(przycisk == 13) // enter
        menu1();
    cout<<endl<<endl<<endl;
}
