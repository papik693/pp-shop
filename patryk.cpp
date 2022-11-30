#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
int wartosc_zamowienia=0;
int wybor_w_menu=1, ilosc_porcji, numer_do_usuniecia;
ifstream plik("menu.json");
json menu = json::parse(plik);
ifstream plik2("zamowienie.json");
json zamowienie = json::parse(plik2);


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
    cout << "Całkowita wartość zamówienia wynosi: " << wartosc_zamowienia << endl;
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

int main() {
    while (wybor_w_menu != 0){
        wyswietl_menu(menu);
        cout << "Które danie wybierasz(numerek)? Chyba że wolisz przejść do podsumowania - wtedy naciśnij 0. Aby wyświetlić zamówienie wciśnij 100 lub aby usunąć pozycję z obecnego zamówienie wciśnij 200" << endl << "Twój wybór: "; 
        cin >> wybor_w_menu;
        switch (wybor_w_menu)
        {
        case 0:
            cout << "Wyjście z zamówień" << endl;
            break;    
        case 100:
            cout << "Twoje obecne zamowienie to:" << endl;
            wyswietl_zamowienie();
            cout << "Czy chcesz przejść do podsumowania? Jeśli tak wciśnij 0, aby wyświetlić menu wybierz dowolną liczbę" << endl << "Twój wybór: ";
            cin >> wybor_w_menu;
            break;
        case 200:
            cout << "Twoje obecne zamowienie to:" << endl;
            wyswietl_zamowienie();
            cout << "Którą pozycję chcesz usunąć?" << endl;
            cin >> numer_do_usuniecia;
            usun_z_zamowienia(numer_do_usuniecia);
            break;
        default:
            bool istnieje = menu["Dania"][wybor_w_menu-1].contains("nazwa");
            if (istnieje != 0) {
                dodaj_do_zamowienia(wybor_w_menu);
            } else { 
                cout << "Nie ma takiej pozycji w karcie. Wybierz inną" << endl << endl;
            }
            break;      
        }
    }
    cout << "Kontynuacja.....";
}

