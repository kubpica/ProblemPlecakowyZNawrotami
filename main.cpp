#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
std::stringstream ss;

//int elementy[1000];
int n = 0;
int pojemnosc = 0;
int maxwar = 0;
int maxwag = 0;
bool czyWygenerowac = true;
int poziom = 1;
int waga = 0;
int wartosc = 0;
int najw = 0;
string snajw = "";
string *ostatnioNaTymPoziomie;
bool czyZmienicElementy = false;

void sortowanie_babelkowe(int *tab,int *war,int n)
{
  for(int i=0;i<n;i++)
    for(int j=n-2;j>=0;j--) //pêtla wewnêtrzna
    if(tab[j+1]>tab[j]){
      swap(tab[j+1], tab[j]); //zamiana miejscami
      swap(war[j+1], war[j]);
    }
}

void zamienElementy(int *a){
    a[poziom-1]++;
    for(int i = 1; poziom-i-1>=0 ; ){
        if( a[poziom-i] >= n-i+2 && poziom-i-1 >= 0){
            a[poziom-i-1]++;
            for(int j = poziom-i-1; j+1<=n-1; j++)
                a[j+1] = a[j]+1;
            i++;
        } else break;
    }

    if(a[0] > n-poziom+1){
        poziom--;
        //cout << "tutututut!!" << endl;
        for(int i = 0; i<poziom; i++){
            a[i] = ostatnioNaTymPoziomie[poziom-1][i] - '0';
        }
        if(poziom >= 1) zamienElementy(a);
        cout << endl;
        int i = 0;
        while(i<poziom-1){
            cout << ostatnioNaTymPoziomie[i] << " ";
            i++;
        }
    }
}

int main()
{
    cout << "Program rozwiazuje dyskretny problem plecakowy (0-1) dla wprowadzonych danych." << endl;
    srand( time( NULL ) );
    while(1){
        //cout << "Gdzie wypisac wyniki? 1 - na ekran 2 - do pliku" << endl;
        //cin >> n;
        //if(n==2) cout << "Jeszcze nie zaimplementowalem wyprowadzenia wyniku do pliku - ale to nie problem zrobic to" << endl;
        n = 0;

        cout << "Skad wziac dane? 1-wygeneruj losowe 2-pozwol mi podac" << endl;
        cin >> n;
        if(n==2) czyWygenerowac = false;

        cout << "Podaj pojemnosc plecaka: ";
        cin >> pojemnosc;
        if(!(pojemnosc<=1000 && pojemnosc>=0)){
            cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
            continue;
        }

        cout << "Podaj liczbe przedmiotow (n): ";
        cin >> n;
        if(n>1000 || n<0){
            cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
            continue;
        }

        if(czyWygenerowac){
            cout << "Podaj maksymalna wartosc jednego elementu: ";
            cin >> maxwar;
            if(!(maxwar<=1000 && maxwar>=0)){
                cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
                continue;
            }

            cout << "Podaj maksymalna wage jednego elementu: ";
            cin >> maxwag;
            if(!(maxwag<=1000 && maxwag>=0)){
                cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
                continue;
            }
        }

        break;
    }
    cout << endl;
    int *elementy;
    int *wagi;
    elementy = new int [n];
    wagi = new int [n];
    int *a;
    a = new int [n];

    ostatnioNaTymPoziomie = new string [n];

    for(int i=0;i<n;i++) a[i] = i+1;


    if(czyWygenerowac){
        for(int i = 0; i<n ; i++){
            int wylosowana =( std::rand() % maxwar ) + 1;
            elementy[i] = wylosowana;
            wylosowana =( std::rand() % maxwag ) + 1;
            wagi[i] = wylosowana;
        }
    }else{
        for( int i = 0; i < n; ++i )
        {
            cout << "Podaj wage " << i+1 << "-go przedmiotu: ";
            cin >> wagi[ i ];
            cout << "Podaj wartosc " << i+1 << "-go przedmiotu: ";
            cin >> elementy[ i ];
            cout << endl;
        }
    }

    sortowanie_babelkowe(wagi,elementy,n);

    if(czyWygenerowac) cout << "Wygenerowalem i posortowalem (malejaco wzgledem wag) n-przedmiotow (" << n << "):" << endl;
    else cout << "Podales nastepujace dane:" << endl;
    cout << "Indeks elementu: waga ; wartosc" << endl;
    for(int i=0;i<n;i++) cout<< i+1 << ": " << wagi[i] << " ; " << elementy[i] << endl;

    cout<<endl;
    system("pause");
    cout<<endl;
    cout << "Reprezentacja dzialania programu: (! oznacza nowa najwieksza wartosc)" << endl;
    cout << "(* oznacza przekroczenie pojemnosci plecaka i \"nawrot\" algorytmu)" << endl;

    while(1){
        waga = 0;
        wartosc = 0;
        czyZmienicElementy  = false;

        for(int i=0;i<poziom;i++){
            cout << a[i];
            waga += wagi[ a[i]-1 ];
            wartosc += elementy[ a[i]-1 ];
        }
        if(waga<=pojemnosc){
            ss.str( std::string() ); ss.clear();
            for(int i=0;i<poziom;i++){
                ss << a[i];
            }
            if(wartosc>najw){
                cout << "!";
                najw = wartosc;
                snajw = ss.str();
                if(poziom == n){
                    cout << endl;
                    break;
                }
            }
            ostatnioNaTymPoziomie[poziom-1]  = ss.str();
            poziom++;
            cout << " ";
            if(poziom>n || a[poziom-2]==n){
                poziom--;
                cout << endl;
                int i = 0;
                while(i<poziom-1){
                    cout << ostatnioNaTymPoziomie[i] << " ";
                    i++;
                }
                czyZmienicElementy = true;
            }else{
                a[poziom-1] = a[poziom-2]+1;
            }
        }else{
            cout << "*" << endl;
            int i = 0;
            while(i<poziom-1){
                cout << ostatnioNaTymPoziomie[i] << " ";
                i++;
            }
            czyZmienicElementy = true;
        }

        if(a[0] == n) break;
        if(czyZmienicElementy) zamienElementy(a);
    }

    cout << "Koniec. Wyniki:" << endl;
    cout << "Plecak zawiera najbardziej wartosciowa mieszczaca sie kombinacje przedmiotow (bez powtorzen)" << endl;
    cout << "Przedmioty w plecaku: ";
    int wagael = 0;
    for(int i = 0; i < snajw.length(); i++){
        cout << snajw[i] << " ";
        wagael += wagi[snajw[i] - '0' - 1];
    }
    cout << endl;
    cout << "Wartosc tych przedmiotow: " << najw << endl;
    cout << "Zajete miejsce w plecaku: " << wagael << "/" << pojemnosc << endl;
    cin >> n;

    return 0;
}
