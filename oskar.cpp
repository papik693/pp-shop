#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int numerStolika;
string miastoDostawy;
string ulicaDostawy;
int numerMieszkaniaDostawy;
int godzinaDostawy;

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

int main()
{
    int condition = 0;
    string imie;
    int formaDostarczenia;
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

    // wywowalanie funkcji menu tutaj

    return 0;
}