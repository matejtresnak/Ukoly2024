#include <iostream>
#include <vector>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;  // Kolík, ze kterého disk přesouváme
    char na; // Kolík, na který disk přesouváme
    vector<vector<int>> stavVezi; // Stav věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, char z, char na) {
    // Přesuň disk ze zdrojového kolíku na cílový
    veze[na - 'A'].push_back(veze[z - 'A'].back());
    veze[z - 'A'].pop_back();
}

// Funkce pro řešení Hanoiských věží (rekurzivně)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n == 1) {
        // Základní případ: přesun jediného disku
        provedTah(veze, z, cil);
        Tah tah = { 1, z, cil, veze };
        tahy.push_back(tah);
        return;
    }

    // Rekurzivně přesunout n-1 disků na pomocný kolík
    hanoi(n - 1, z, cil, pomocny, veze, tahy);

    // Přesunout n-tý disk na cílový kolík
    provedTah(veze, z, cil);
    Tah tah = { n, z, cil, veze };
    tahy.push_back(tah);

    // Rekurzivně přesunout n-1 disků na cílový kolík
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro zobrazení stavu věží
void zobrazVeze(const vector<vector<int>>& veze) {
    
    for (int i = 0; i < 3; i++) {
        cout << "Kolik " << char('A' + i) << ": ";
        for (int disk : veze[i]) {
            cout << disk << " ";
        }
        cout << endl;
    }
    cout << endl;
    
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte počet disků: ";
    cin >> n;
    cin.ignore();

    // Vytvoření tří věží
    vector<vector<int>> veze(3);
    for (int i = n; i > 0; i--) {
        veze[0].push_back(i);  // Všechny disky začínají na kolíku A
    }

    vector<Tah> tahy; // Vektor pro uložení tahů
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah& tah : tahy) {
        cout << "Přesuň disk " << tah.disk << " z kolíku " << tah.z << " na kolík " << tah.na << endl;
        zobrazVeze(tah.stavVezi); // Zobrazení stavu věží po tahu
    }

    return 0;
}
#endif // __TEST__
