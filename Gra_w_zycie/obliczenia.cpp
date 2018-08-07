/**
* \file obliczenia.cpp
* \brief Plik implementacji modułu obliczenia
*
* Moduł obliczenia zawiera funkcje odpowiadające za realizację
* algorytmów oraz definicję struktury definiujacej
* parametry komórki gry w życie
*/

#include <obliczenia.h>
#include <conio.h>
#include <ctime>
#include <lista.h>
#include <interfejs.h>
#include <pliki.h>


int W,K;

/**
 * @brief procedura licząca sąsiadów wszystkich komórek w tablicy
 * @param tab wskaźnik do tablicy komórek
 */
void liczSasiadow(komorka **tab);

/**
 * @brief procedura określająca stan komórek w tablicy w następnej turze
 * @param tabSprawdzana wskaźnik do tablicy komórek aktualnej tury
 * @param tabNastepna wskaźnik do tablicy komórek następnej tury
 */
void nastepnyStan(komorka **tabSprawdzana,komorka **tabNastepna);

/**
 * @brief funckja określająca wybraną opcję przez użytkownika
 * w danym czasie podczas realizowania symulacji
 * @param milisekund jednostka czasu w milisekundach
 * @return kod opcji wybranej przez użytkownika
 */
int opcjePodczasGry(int milisekund);

/**
 * @brief funckja określająca wybraną opcję przez użytkownika
 * podczas pauzy
 * @return kod opcji wybranej przez użytkownika
 */
int opcjePodczasPauzy();

/**
 * @brief funkcja zmieniająca czas wyświetlania tury
 * @param polecenie kod polecenia przyśpieszenia lub spowolnienia
 * @param szybkosc aktualna szybkość zmiany tury
 * @return szybkosc zmiany tury po operacji przyśpieszenia lub spowolnienia
 */
int przyspieszZwolnij(int polecenie, int szybkosc);


void ustawWybranaOpcjaNaPierwsza(int liczbaOpcji,char tab[], int &aktualna)
{
    tab[0]='>';
    for(int i=1;i<liczbaOpcji;i++)
    {
        tab[i]=' ';
    }
    aktualna=0;
}

void przesunOpcjeWGore(char tablicaOpcji [], int &aktualnaOpcja, int liczbaOpcji)
{
    if(aktualnaOpcja==0)
    {
        tablicaOpcji[0]=' ';
        tablicaOpcji[liczbaOpcji-1]='>';
        aktualnaOpcja=liczbaOpcji-1;
    }
    else
    {
        tablicaOpcji[aktualnaOpcja]=' ';
        tablicaOpcji[aktualnaOpcja-1]='>';
        aktualnaOpcja--;
    }
}

void przesunOpcjeWDol(char tablicaOpcji [], int &aktualnaOpcja, int liczbaOpcji)
{
    if(aktualnaOpcja==liczbaOpcji-1)
    {
        tablicaOpcji[liczbaOpcji-1]=' ';
        tablicaOpcji[0]='>';
        aktualnaOpcja=0;
    }
    else
    {
        tablicaOpcji[aktualnaOpcja]=' ';
        tablicaOpcji[aktualnaOpcja+1]='>';
        aktualnaOpcja++;
    }
}

komorka **utworzTablice()
{
    komorka **tab =new komorka *[W];
    for(int i=0;i<W;i++)
    {
        tab[i]=new komorka[K];
    }
    return tab;
}

void usunTablice(komorka **tab)
{
    for(int i=0;i<W;i++)
    {
        delete [] tab[i];
    }
    delete tab;
}

void wypelnijTabliceLosowo(komorka **tab)
{
    srand(time(0));
    for(int i=0;i<W;i++)
    {
        for(int j=0;j<K;j++)
        {
            int a=rand()%2;
            if(a==0)
                tab[i][j].stan =' ';
            else
                tab[i][j].stan ='#';
        }
    }
}

void liczSasiadow(komorka **tab)
{
    int ilosc=0;
    for (int i = 0; i < W; i++)
        {
            for (int j = 0; j < K; j++)
            {
                if (i-1>-1 && j-1>-1 && tab[i - 1][j - 1].stan == '#')
                    ilosc++;
                if (i-1>-1 && tab[i - 1][j].stan == '#')
                    ilosc++;
                if (i-1>-1 && j+1<K && tab[i - 1][j + 1].stan == '#')
                    ilosc++;
                if (j-1>-1 && tab[i][j - 1].stan == '#' )
                    ilosc++;
                if (j+1<K && tab[i][j + 1].stan == '#')
                    ilosc++;
                if (i+1<W && j-1>-1 && tab[i + 1][j - 1].stan == '#')
                    ilosc++;
                if (i+1<W && tab[i + 1][j].stan == '#')
                    ilosc++;
                if (i+1<W && j+1<K && tab[i + 1][j + 1].stan == '#')
                    ilosc++;
                tab[i][j].liczbaSasiadow=ilosc;
                ilosc=0;
            }
        }
}

void nastepnyStan(komorka **tabSprawdzana,komorka **tabNastepna)
{
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < K; j++)
        {
            if (tabSprawdzana[i][j].stan == ' ' && tabSprawdzana[i][j].liczbaSasiadow == 3)
                tabNastepna[i][j].stan = '#';
            else
                if (tabSprawdzana[i][j].stan == '#' &&( tabSprawdzana[i][j].liczbaSasiadow == 2 || tabSprawdzana[i][j].liczbaSasiadow == 3))
                    tabNastepna[i][j].stan='#';
                else
                    tabNastepna[i][j].stan = ' ';
        }
    }
}



void symulacjaGry(int turaWyswietlania, komorka **tab)
{
    bool czyPauza=false,wyjscieZSymualcji=false,mozliwoscCofania=false;
    int szybkosc=1000;
    int aktualnaTura=1, liczbaCofniec=3, iloscPozostalychCofniec=3, iloscProbZapisuDoPliku=0;
    ListaTablic *glowa;
    stworzListe(glowa,tab);
    ListaTablic *aktualny=glowa;
    while(true)
    {
        if(aktualnaTura>=turaWyswietlania)
        {
            czyscEkran();
            wyswietlGre(aktualny->tab,aktualnaTura,czyPauza,iloscPozostalychCofniec,mozliwoscCofania);
            int polecenie=opcjePodczasGry(szybkosc);
            switch(polecenie)
            {
            case 1: //Tryb pauzy
                czyscEkran();
                czyPauza=true;
                polecenie=0;
                while(polecenie!=1 && polecenie!=3) // wyświetlanie gry spauzowanej, aż nie nastąpi odpauzowanie lub wyjście
                {
                    czyscEkran();
                    wyswietlGre(aktualny->tab,aktualnaTura,czyPauza,iloscPozostalychCofniec,mozliwoscCofania);
                    polecenie=opcjePodczasPauzy();
                    switch(polecenie)
                    {
                    case 1: // Odpauzowanie
                        czyPauza=false;
                        break;
                    case 2: // Cofnij stan gry
                        if(iloscPozostalychCofniec>0&& mozliwoscCofania==true)
                        {
                            aktualny=aktualny->poprzednia;
                            iloscPozostalychCofniec--;
                            aktualnaTura--;
                        }
                        break;
                    case 3: // Wyjście
                        wyjscieZSymualcji=true;
                        break;
                    case 4: //Zapis stanu do pliku
                        czyscEkran();
                        komunikatProszacyONazwePliku();
                        std::string nazwaPliku;
                        getline(std::cin,nazwaPliku);
                        if(iloscProbZapisuDoPliku==0) //przy pierwszej próbie zapisu występują błędy, więc robię to wtedy dwa razy
                        {
                            getline(std::cin,nazwaPliku);
                            iloscProbZapisuDoPliku++;
                        }
                        if(sprawdzeniePoprawnosciNazwyPlikuTekstowego(nazwaPliku)==true)
                        {
                            zapisDoPliku(aktualny->tab, nazwaPliku);
                            czyscEkran();
                            komunikatZapisZakonczonySukcesem();
                        }
                        else
                        {
                            czyscEkran();
                            komunikatZapisZakonczonyNiepowodzeniem();
                        }
                        kliknijDowolnyAbyPrzejscDalej();
                        break;
                    }
                }
                break;
            case 2: // Wyjście
                wyjscieZSymualcji=true;
                break;
            case 3: //przyspiesz
            case 4: // zwolnij
                szybkosc=przyspieszZwolnij(polecenie,szybkosc);
                break;
            }
        }
        if(wyjscieZSymualcji==true)
            break;
        if(iloscPozostalychCofniec<3) //gra została cofnięta
        {
            aktualny=aktualny->nastepna; //następuje wyświetlanie stanów przed cofnięciem
            aktualnaTura++;
            iloscPozostalychCofniec++;
        }
        else
        {
            aktualnaTura++;
            if(aktualnaTura>3) //stawienie możliwości cofania gry
                    mozliwoscCofania=true;
            liczSasiadow(aktualny->tab);
            dodajElementNaKoniecListy(glowa,utworzTablice()); //tworzenie nowej tablicy komórek
            nastepnyStan(aktualny->tab,aktualny->nastepna->tab); //ustalenie stanu komórek w nowej tablicy komórek
            if(aktualnaTura>liczbaCofniec+1) //usuwanie tablic komórek, do których nie będzie już dostępu
            {
               usunTablice(glowa->tab);
               usunPierwszyElementListy(glowa);
            }
            aktualny=aktualny->nastepna;
        }
    }
    usunTabliceIListe(glowa);
    koniecDzialaniaProgramu();
}



int opcjePodczasGry(int milisekund)
{
    clock_t koniec;
    koniec = clock() + milisekund * CLOCKS_PER_SEC/1000;
    while (clock() < koniec) //odliczanie czasu
    {
        if(_kbhit()==1) //następiło wciśnięcie klawisza
        {
            char znak=_getch();
            switch(znak)
            {
            case 'p':
            case 'P':
                return 1; //kod pauzy
            case 27:
                return 2; //kod wyjścia
            case 'f':
            case 'F':
                return 3; //kod przyśpieszenia
            case 's':
            case 'S':
                return 4; //kod spowolnienia
            }
        }
    }
    return 0; //żaden przycisk kluczowy nie został wciśnięty
}

int opcjePodczasPauzy()
{
    while(true)
    {
        if(_kbhit()==1)
        {
            char przycisk=_getch();
            switch(przycisk)
            {
            case 'p':
            case 'P':
                return 1; //kod odpauzowania
            case 'c':
            case 'C':
                return 2; //kod cofnięcia
            case 27:
                return 3; //kod wyjścia
            case 'z':
            case 'Z':
                return 4; //kod zapisu do pliku

            }
        }
    }
}

int przyspieszZwolnij(int polecenie, int szybkosc)
{
    if(polecenie == 3)
    {
        if(szybkosc>81)
            szybkosc-=460;
    }
    else
        if(szybkosc<2400)
            szybkosc+=460;
    return szybkosc;
}

void poruszanieSiePoTablicyDoUzupelnienia(komorka **tab)
{
    int aktx=0,akty=0;
    char polecenie='a';
    int wartoscPolecenia =1;
    while(!(wartoscPolecenia==27))
    {
        czyscEkran();
        wyswietlTabliceDoUzupelniania(tab,aktx,akty);
        polecenie=getch();
        if(polecenie==-32) //znak specjalny
        {
            polecenie=getch(); //wczytanie znaku specjalnego
            wartoscPolecenia=polecenie;
            switch(wartoscPolecenia)
            {
            case 72: //strzałka w gore
                if(aktx==0)
                    aktx=W-1;
                else
                    aktx--;
                break;
            case 80: //strzałka w dol
                if(aktx==W-1)
                    aktx=0;
                else
                    aktx++;
                break;
            case 77: //strzałka w prawo
                if(akty==K-1)
                    akty=0;
                else
                    akty++;
                break;
            case 75: //strzałka w lewo
                if(akty==0)
                    akty=K-1;
                else
                    akty--;
                break;

            }
        }
        else
        {
            wartoscPolecenia=polecenie;
            if(polecenie==13) //enter
                if(tab[aktx][akty].stan==' ')
                   tab[aktx][akty].stan='#';
                else
                 tab[aktx][akty].stan=' ';
            else if(polecenie == 'L' || polecenie == 'l') //wypełnienie losowe tablicy
                wypelnijTabliceLosowo(tab);
        }
    }
}

bool sprawdzeniePoprawnosciNazwyPlikuTekstowego(std::string nazwa)
{
    for(int i=0;i<nazwa.size()-4;i++)
    {
        if(nazwa[i]=='/' || nazwa[i]==92 || nazwa[i]==':' || nazwa[i]=='*' || nazwa[i]=='?'
                 || nazwa[i]=='"' || nazwa[i]=='<' || nazwa[i]=='>' || nazwa[i]=='|') //występowanie nieprawidłowych znaków w nazwie pliku
            return false;
    }
    if(nazwa[nazwa.size()-4]=='.')
        if(nazwa[nazwa.size()-3]=='t')
            if(nazwa[nazwa.size()-2]=='x')
                if(nazwa[nazwa.size()-1]=='t') //nazwa pliku musi kończyć się .txt
                    return true;
    return false;
}
