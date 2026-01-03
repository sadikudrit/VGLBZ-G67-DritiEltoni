#define _CRT_SECURE_NO_WARNINGS 
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
    string emriHuazuesit;
    string infoKthimi;

    Liber(int i, string t, string a) {
        id = i;
        titulli = t;
        autori = a;
        iHuazuar = false;
        emriHuazuesit = " - ";
        infoKthimi = " - ";
    }

    void shfaqDetaje() {
        cout << left << setw(8) << id
            << setw(18) << titulli.substr(0, 17)
            << setw(15) << autori.substr(0, 14)
            << setw(12) << (iHuazuar ? "HUAZUAR" : "LIRE")
            << setw(15) << emriHuazuesit.substr(0, 14)
            << " Data: " << infoKthimi << endl;
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
            cout << "Gabim! Jepni nje numer per ID: ";
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
        string emri;
        cout << "Shkruaj ID e librit per huazim: "; cin >> id;
        for (auto& l : inventari) {
            if (l.id == id) {
                if (l.iHuazuar) {
                    cout << "Gabim: Libri eshte zene nga " << l.emriHuazuesit << endl;
                    return;
                }
                cout << "Emri i personit qe po e huazon: ";
                cin.ignore(); getline(cin, emri);

                l.iHuazuar = true;
                l.emriHuazuesit = emri;

                time_t koha = time(0);
                char* dt = ctime(&koha);
                string dataSot(dt);
                if (!dataSot.empty()) dataSot.pop_back();
                l.infoKthimi = dataSot;

                cout << "Sukses! Libri u huazua nga " << emri << endl;
                return;
            }
        }
        cout << "Libri me kete ID nuk u gjet!\n";
    }
    void shfaq() {
        if (inventari.empty()) {
            cout << "\nLibraria eshte boshe.\n";
            return;
        }
        cout << "\n" << string(85, '-') << "\n";
        cout << left << setw(8) << "ID" << setw(18) << "TITULLI" << setw(15) << "AUTORI"
            << setw(12) << "STATUSI" << setw(15) << "HUAZUESI" << "DATA\n";
        cout << string(85, '-') << "\n";
        for (auto& l : inventari) l.shfaqDetaje();
    }
};

int main() {
    Biblioteka ime;
    int zgjedhja;

    while (true) {
        cout << "\n==== MENAXHIMI I BIBLIOTEKES ====\n";
        cout << "1. Shto Liber te Ri\n";
        cout << "2. Shfaq Inventarin\n";
        cout << "3. Huazo Liber\n";
        cout << "4. Mbyll Programin\n";
        cout << "Zgjedhja: ";

        if (!(cin >> zgjedhja)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (zgjedhja == 1) ime.shtoLiber();
        else if (zgjedhja == 2) ime.shfaq();
        else if (zgjedhja == 3) ime.huazo();
        else if (zgjedhja == 4) break;
        else cout << "Zgjedhje e gabuar!\n";
    }

    return 0;
}
