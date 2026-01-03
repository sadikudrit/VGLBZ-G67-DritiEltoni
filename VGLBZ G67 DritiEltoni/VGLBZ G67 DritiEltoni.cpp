#define _CRT_SECURE_NO_WARNINGS // Zgjidhja per gabimin C4996
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

class Liber {
public:
    int id;
    string titulli;
    string autori;
    bool iHuazuar;
    string infoKthimi;

    Liber(int i, string t, string a) {
        id = i;
        titulli = t;
        autori = a;
        iHuazuar = false;
        infoKthimi = " - ";
    }

    void shfaqDetaje() {
        cout << left << setw(8) << id
            << setw(20) << titulli
            << setw(15) << autori
            << setw(12) << (iHuazuar ? "HUAZUAR" : "LIRE")
            << " Statusi: " << infoKthimi << endl;
    }
};

class Biblioteka {
private:
    vector<Liber> inventari;

public:
    void shtoLiber() {
        int id;
        string t, a;
        cout << "\n--- Regjistrimi i Librit ---\n";
        cout << "ID (Numer): ";
        while (!(cin >> id)) {
            cout << "Gabim! Shkruaj nje numer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Titulli: "; cin.ignore(); getline(cin, t);
        cout << "Autori: "; getline(cin, a);

        inventari.push_back(Liber(id, t, a));
        cout << ">> Libri u shtua me sukses!\n";
    }

    void huazo() {
        int id;
        cout << "Shkruaj ID e librit per huazim: "; cin >> id;
        for (auto& l : inventari) {
            if (l.id == id) {
                if (l.iHuazuar) {
                    cout << "Ky liber eshte huazuar nje here!\n";
                    return;
                }
                l.iHuazuar = true;
                time_t koha = time(0);
                char* dt = ctime(&koha); // Tani Visual Studio e lejon kete
                string dataSot(dt);
                if (!dataSot.empty()) dataSot.pop_back();
                l.infoKthimi = "Huazuar me: " + dataSot;
                cout << "Huazimi u krye me sukses!\n";
                return;
            }
        }
        cout << "Libri nuk u gjet ne sistem.\n";
    }

    void shfaqInventarin() {
        if (inventari.empty()) {
            cout << "\nLibraria eshte boshe.\n";
            return;
        }
        cout << "\n" << string(70, '-') << "\n";
        cout << left << setw(8) << "ID" << setw(20) << "TITULLI" << setw(15) << "AUTORI"
            << setw(12) << "STATUSI" << "DATA E VEPRIMIT\n";
        cout << string(70, '-') << "\n";
        for (auto& l : inventari) {
            l.shfaqDetaje();
        }
    }
};

int main() {
    Biblioteka ime;
    int zgjedhja;

    while (true) {
        cout << "\n==== SISTEMI I BIBLIOTEKES ====\n";
        cout << "1. Shto Liber te Ri\n";
        cout << "2. Shfaq Inventarin\n";
        cout << "3. Huazo Librin\n";
        cout << "4. Mbyll Programin\n";
        cout << "Zgjedhja juaj: ";

        if (!(cin >> zgjedhja)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (zgjedhja == 1) ime.shtoLiber();
        else if (zgjedhja == 2) ime.shfaqInventarin();
        else if (zgjedhja == 3) ime.huazo();
        else if (zgjedhja == 4) break;
        else cout << "Opsion i gabuar!\n";
    }

    return 0;
}