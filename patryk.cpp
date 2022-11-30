#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
float wartosc_zamowienia=0;
void wyswietl_menu(json menu){
    cout << "*** MENU ***" << endl;
    int j = 0;
    for (auto i : menu["Dania"]){
        cout << j+1 << ". " << menu["Dania"][j]["nazwa"].get<string>() << ", cena: " << menu["Dania"][j]["cena"] << endl;
        cout << "Składniki: " << menu["Dania"][j]["skladniki"].get<string>() << endl << endl;
        j++;
    }
}
void wyswietl_zamowienie(json zamowienie){
    int j = 0;
    for (auto i : zamowienie["Zamowienie"]){
        cout << j+1 << ". " << zamowienie["Zamowienie"][j]["nazwa"].get<string>() << ", cena: " << zamowienie["Zamowienie"][j]["cena"] << endl;
        j++;
        wartosc_zamowienia+= zamowienie["Zamowienie"][j]["cena"];
    }
    cout << wartosc_zamowienia;
}

int main() {
    int wybor=1, ilosc;
    float wartosc_zamowienia=0;
    ifstream plik("menu.json");
    json menu = json::parse(plik);
    ifstream plik2("zamowienie.json");
    json zamowienie = json::parse(plik2);
    while (wybor != 0){
        wyswietl_menu(menu);
        cout << "Które danie wybierasz(numerek)? Chyba że wolisz przejść do podsumowania - wtedy naciśnij 0. Aby wyświetlić zamówienie lub usunąć pozycję z obecnego zamówienie wciśnij 100." << endl << "Twój wybór: "; 
        cin >> wybor;
        switch (wybor)
        {
        case 0:
            cout << "Wyjście z zamówień" << endl;
            break;    
        case 100:
            cout << "Twoje obecne zamowienie to:" << endl;
            wyswietl_zamowienie(zamowienie);
            cout << "Czy chcesz przejść do podsumowania? Jeśli tak wciśnij 0, aby wyświetlić menu wybierz dowolną liczbę" << endl << "Twój wybór: ";
            cin >> wybor;
            break;
        default:
            bool istnieje = menu["Dania"][wybor].contains("nazwa");
            cout << istnieje << endl;
            if (istnieje != 0) {
                cout << "Ile porcji?: ";
                cin >> ilosc;
                zamowienie["Zamowienie"].push_back(menu["Dania"][wybor]);
            } else { 
                cout << "Nie ma takiej pozycji w karcie. Wybierz inną" << endl << endl;
            }
            break;      
        }
    }
    cout << "Kontynuacja.....";
}

