// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#include <iostream>
#include "Solucionador.h"
#include "Solucio.h"
#include "Candidats.h"

using namespace std;

#ifdef _WIN32
   #include <windows.h>
#endif // _WIN32

/**
 @pre  Cert.
 @post Mostra ajuda per pantalla.
**/
void mostrarAjuda(const string& opcio);

/**
 @pre  Cert.
 @post S'ha executat el programa principal d'acord amb els paràmetres entrats.
**/
int main(int argn, char **argv) {

	///
    #ifdef _WIN32
       SetConsoleOutputCP(65001);
       SetConsoleCP(65001);
    #endif // _WIN32
	///

	if(argn==1 || (argn>1 && argv[1][0]!='-') || argn>4) {
        if(argn > 4) mostrarAjuda("sobren");
        else mostrarAjuda("falten");
        return 0;
	}
    else {
        bool millor = false, unica = false;

        string nomFitxer;
        int alt_max = 0;

        if( (string(argv[1])=="-h") || (string(argv[1])=="--help") ) {
            mostrarAjuda("ajuda");
            return 0;
        }
        else if(string(argv[1]) == "-u") {
            if(argn < 4) {
                cout << "Falta altura màxima tolerada o nom fitxer" << endl;
                return 0;
            }
            else {
                if(argv[2][0]>='0' && argv[2][0]<='9') {
                    unica = true;
                    alt_max = stoi(argv[2]);
                    nomFitxer = argv[3];
                }
                else {
                    cout << "El paràmetre 'alt' ha de ser un número" << endl;
                    return 0;
                }
            }
        }
        else if(string(argv[1]) == "-m") {
            if(argn < 3) {
                cout << "Falta nom fitxer" << endl;
                return 0;
            }
            else {
                millor = true;
                nomFitxer = argv[2];
            }
        }
        else {
            cout << "Opció desconeguda: " << argv[1] << endl;
            return 0;
        }


        ifstream file(nomFitxer.c_str());

        if(!file.is_open()) {
            cout << "El fitxer [" << nomFitxer << "] no es pot obrir. Revisa el nom o els permisos" << endl;
            return 0;
        }
        else {
            Solucio ini(file, alt_max, millor);
            Solucionador algBack;

            if(unica) {
                bool teSolucio = algBack.solucionarUna(ini);

                if(!teSolucio) cout << "No hi ha solució" << endl;
                else algBack.get_UnaSolucio().mostrar();

            }
            else if(millor) {
                algBack.solucionarMillor(ini);
                algBack.get_MillorSolucio().mostrar();
            }

            cout << "Temps: " << algBack.get_time() << " segons" << endl;

            return 0;
        }
    }
}

void mostrarAjuda(const string& opcio) {

    if(opcio == "falten") cout << "Falten arguments (\"./gratacels --help\" per ajuda)" << endl;
    else if(opcio == "sobren") cout << "Sobren arguments (\"./gratacels --help\" per ajuda)" << endl;
    else if(opcio == "ajuda") {
        cout << "*** Distribució de gratacels en una illa d'edificis quadrada ***" << endl;
        cout << "Utilització: ./gratacels opcio fitxer" << endl << endl;

        cout << "opcio pot ser:" << endl;
        cout << "-h, --help  : mostra aquest missatge d'ajuda i surt." << endl;

        cout << "-u alt      : cerca una solució que compleixi les restriccions\n";
        cout << "              del problema sense fer servir edificis d'una\n";
        cout << "              altura superior a alt." << endl;

        cout << "-m          : cerca la solució que maximitza la suma de les\n";
        cout << "              altures de tots els edificis de la solució." << endl;

        cout << "fitxer        ha de ser un fitxer de text amb totes les dades\n";
        cout << "              amb el format següent:" << endl;
        cout << "              dimensió(n) // dimensió matriu" << endl;
        cout << "              vN1 vN2 ... VNn // visibles des del nord" << endl;
        cout << "              vS1 vS2 ... VSn // visibles des del sud" << endl;
        cout << "              vE1 vE2 ... VEn // visibles des del est" << endl;
        cout << "              vW1 vW2 ... VWn // visibles des del oest" << endl;
        cout << "              altura maxima(m) // altura màxima disponible" << endl;
        cout << "              a1 a2 ... am // edificis disponibles de cada altura" << endl;
    }
}
