#include <iostream>
#include <fstream>
// #include <conio.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

ifstream plik2("zamowienie.json");
json zamowienie = json::parse(plik2);

int godzinaDostawy = 12;

void podsumowanie_zamowienia()
{
    int cena = 0;

    cout << "*** PODSUMOWANIE ***" << endl;

    ofstream rachunek;
    rachunek.open("rachunek.txt");

    rachunek << "RACHUNEK ZA ZAMÓWIENIE\n";

    int j = 0;
    for (auto i : zamowienie["Zamowienie"]){
        rachunek << j+1 << ". " << i["nazwa"].get<string>() << ", cena: " << i["cena"] << " zł\n";
        cena += i["cena"].get<int>();
        j++;
    }

    rachunek << "Całkowita kwota zamówienia: " << cena << " zł";

    rachunek.close();

    cout << "Godzina dostawy: " << godzinaDostawy << ":00" << endl;

    cout << "Naciśnij dowolny klawisz żeby zakończyć działanie programu...";
    //_getch();
}

int main()
{
    podsumowanie_zamowienia();
    return 0;
}