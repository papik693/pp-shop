#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <conio.h>
using json = nlohmann::json;
using namespace std;

int wartosc_zamowienia=0;
int wybor_w_menu=1, ilosc_porcji, numer_do_usuniecia, wybor_podsumowania;
int numerStolika;
string miastoDostawy;
string ulicaDostawy;
int numerMieszkaniaDostawy;
int godzinaDostawy;
int condition = 0;
string imie;
int formaDostarczenia;
ifstream plik("menu.json");
ifstream plik2("zamowienie.json");
json menu = json::parse(plik);
json zamowienie = json::parse(plik2);

// try
// {
//     json zamowienie = json::parse(plik2);
// }
// catch (json::parse_error& exception)
// {
//     cerr << "parse error! Popraw plik zamowienie!" << endl;
//     cout << "Naciśnij dowolny klawisz aby wyjść...";
//     getch();
//     exit(1);
// }
// try
// {
//     json menu = json::parse(plik);
// }
// catch (json::parse_error& exception)
// {
//     cerr << "parse error! Popraw plik menu!" << endl;
//     cout << "Naciśnij dowolny klawisz aby wyjść...";
//     getch();
//     exit(1);
// }



void stolik()
{
    int condition = 0;
    cout << "Przy jakim numerze stolika zamierzasz usiasc?" << endl;
    while (condition != 1)
    {
        cout << "Stoliki sa tylko do numeru 25" << endl;
        cin >> numerStolika;
        if (numerStolika > 25 || numerStolika < 1)
        {
            cout << "Nie ma takie stolika" << endl;
        }
        else
        {
            condition = 1;
        }
    }
}

void dostawa()
{   
    cout << "Jeśli chcesz dostawę to po co tu przychodzisz? Wystarczyło zadzwonić...." << endl;
    int condition = 0;
    cout << "Prosze podac miasto dostawy" << endl;
    cin >> miastoDostawy;
    cout << "Podaj ulice na jaka ma byc otrzymana dostawa" << endl;
    cin >> ulicaDostawy;
    cout << "i na koniec prosze podac numer domu/mieszkania" << endl;
    cin >> numerMieszkaniaDostawy;
    while (condition != 1)
    {
        cout << "Prosze podac godzine na jaka ma byc (dostawa tylko na dzis od godziny 5 do godziny 22)" << endl;
        cin >> godzinaDostawy;
        if (godzinaDostawy < 5 || godzinaDostawy > 22)
        {
            cout << "Nie dzialamy o tej godzinie" << endl;
        }
        else
        {
            condition = 1;
        }
    }
}
void przywitanie(){ 
    cout << "Restauracja pod Dwoma Krasnoludami" << endl;
    cout << "Denerim, Dzielnica Rynkowa, ul.Rynkowa 15 Ferelden." << endl;
    cout << "Wlasciciel Flavius Minervalis" << endl;
    cout << "Podaj swoje imie:";
    cin >> imie;
    imie[0] = toupper(imie[0]);
    cout << "Witaj " << imie << endl;
    cout << "Danie jesz na miejscu czy dostawa?" << endl;

    while (condition != 1)
    {
        cout << "Wpisz 1. Jesli na miejscu, 2.Jezeli dostawa." << endl;
        cin >> formaDostarczenia;
        switch (formaDostarczenia)
        {
        case 1:
            stolik();
            condition = 1;
            break;
        case 2:
            dostawa();
            condition = 1;
            break;
        default:
            cout << "Nie ma takiego wyboru" << endl;
            condition = 0;
            break;
        }
    }
}

void wyswietl_menu(json menu){
    cout << "*** MENU ***" << endl;
    int j = 0;
    for (auto i : menu["Dania"]){
        cout << j+1 << ". " << menu["Dania"][j]["nazwa"].get<string>() << ", cena: " << menu["Dania"][j]["cena"] << endl;
        cout << "Składniki: " << menu["Dania"][j]["skladniki"].get<string>() << endl << endl;
        j++;
    }
}
void wyswietl_zamowienie(){
    int j = 0, wartosc_zamowienia=0;
    for (auto i : zamowienie["Zamowienie"]){
        cout << j+1 << ". " << zamowienie["Zamowienie"][j]["nazwa"].get<string>() << ", cena: " << zamowienie["Zamowienie"][j]["cena"] << endl;
        wartosc_zamowienia = wartosc_zamowienia + zamowienie["Zamowienie"][j]["cena"].get<int>();
        j++;
    }
    cout << "Calkowita wartosc zamowienia wynosi: " << wartosc_zamowienia << endl;
}

void usun_z_zamowienia(int numer_do_usuniecia){
    numer_do_usuniecia = numer_do_usuniecia-1; // aby wyrównać do indeksu w tabeli
    zamowienie["Zamowienie"].erase(zamowienie["Zamowienie"].begin() + numer_do_usuniecia);
}

void dodaj_do_zamowienia(int wybor_w_menu){
    wybor_w_menu = wybor_w_menu-1; // aby wyrównać do indeksu w tabeli
    cout << "Ile porcji?: ";
    cin >> ilosc_porcji;
    for (int i=0;i<ilosc_porcji;i++){
        zamowienie["Zamowienie"].push_back(menu["Dania"][wybor_w_menu]);
    }
}

void kompletowanie_zamowienia() {
    while (wybor_w_menu != 0){
        wyswietl_menu(menu);
        cout << "Ktore danie wybierasz(numerek)? Chyba ze wolisz przejsc do podsumowania - wtedy nacisnij 0. Aby wyswietlic zamowienie wcisnij 100 lub aby usunac pozycje z obecnego zamowienia wcisnij 200" << endl << "Twoj wybor: "; 
        cin >> wybor_w_menu;
        switch (wybor_w_menu)
        {
        case 0:
            cout << "Wyjscie z zamowien" << endl;
            break;
        case 1:
            dodaj_do_zamowienia(wybor_w_menu);
            break;
        case 2:
            dodaj_do_zamowienia(wybor_w_menu);
            break;
        case 3:
            dodaj_do_zamowienia(wybor_w_menu);
            break;
        case 4:
            dodaj_do_zamowienia(wybor_w_menu);
            break;
        case 100:
            cout << "Twoje obecne zamowienie to:" << endl;
            wyswietl_zamowienie();
            cout << "Czy chcesz przejsc do podsumowania? Jesli tak wciśnij 0, aby wyświetlic menu wybierz dowolna liczbe" << endl << "Twoj wybor: ";
            cin >> wybor_w_menu;
            break;
        case 200:
            cout << "Twoje obecne zamowienie to:" << endl;
            wyswietl_zamowienie();
            cout << "Która pozycje chcesz usunać?" << endl;
            cin >> numer_do_usuniecia;
            usun_z_zamowienia(numer_do_usuniecia);
            break;
        default:
            cout << "Nie ma takiej pozycji. Wybierz inny numer" << endl;
            break;
        }   
    }
}

void podsumowanie_zamowienia()
{
    int cena = 0;
    cout << "*** PODSUMOWANIE ***" << endl;
    cout << "Podsumowanie zamwwienia chcesz zobaczyc na ekranie czy zapisac je do pliku? 1-ekran 2-plik" << endl;
    cin >> wybor_podsumowania;
    if (wybor_podsumowania == 1)
    {
        cout << "RACHUNEK ZA ZAMOWIENIE\n";
        wyswietl_zamowienie();
        if (formaDostarczenia == 2){
            cout << "Zamowienie dla: " << imie << endl;
            cout << "Godzina dostawy: " << godzinaDostawy << ":00" << endl;
            cout << "Miasto: " << miastoDostawy << endl;
            cout << "Ulica: " << ulicaDostawy << endl;
            cout << "Numer mieszkania: " << numerMieszkaniaDostawy << endl;
        }
    }
    else if (wybor_podsumowania == 2)
    {
        ofstream rachunek;
        rachunek.open("rachunek.txt");

        rachunek << "RACHUNEK ZA ZAMOWIENIE\n";
        int j = 0;
        for (auto i : zamowienie["Zamowienie"]){
            rachunek << j+1 << ". " << i["nazwa"].get<string>() << ", cena: " << i["cena"] << " zł\n";
            cena += i["cena"].get<int>();
            j++;
        }
        rachunek << "Calkowita kwota zamowienia: " << cena << " zł" << endl;
        if (formaDostarczenia == 2){
            rachunek << "Zamowienie dla: " << imie << endl;
            rachunek << "Godzina dostawy: " << godzinaDostawy << ":00" << endl;
            rachunek << "Miasto: " << miastoDostawy << endl;
            rachunek << "Ulica: " << ulicaDostawy << endl;
            rachunek << "Numer mieszkania: " << numerMieszkaniaDostawy << endl;
        }
        rachunek.close();
    }
    else
    {
        cout <<"Zly wybor..." << endl;
        podsumowanie_zamowienia();
    }
    getch();
    cout << "Nacisnij dowolny klawisz żeby zakonczyc działanie programu..." << endl;
}

int main()
{
    przywitanie();
    cout << "Teraz wybierz cos z karty!" << endl;
    kompletowanie_zamowienia();
    podsumowanie_zamowienia();
    getch();
    return 0;
}