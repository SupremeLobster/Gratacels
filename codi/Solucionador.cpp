// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#include "Solucionador.h"

Solucionador::Solucionador() {}

bool Solucionador::solucionarUna(const Solucio& inicial) {

    t1 = high_resolution_clock::now();

    encertat = false;
    solAct = inicial;
    backtrackingUna();

    t2 = high_resolution_clock::now();

    return encertat;
}

void Solucionador::solucionarMillor(const Solucio& inicial) {

    t1 = high_resolution_clock::now();

    solAct = solOpt = inicial;
    backtrackingMillor();

    t2 = high_resolution_clock::now();
}

Solucio Solucionador::get_UnaSolucio() const {

    return solAct;
}

Solucio Solucionador::get_MillorSolucio() const {

    return solOpt;
}

double Solucionador::get_time() const {

    return duration_cast< duration<double> >(t2 - t1).count();
}

void Solucionador::backtrackingUna() {

    Candidats iCan = solAct.inicialitzarCandidats();

    while(!iCan.esFi() && !encertat) {
        if(solAct.acceptable(iCan)) {
            solAct.anotarCandidat(iCan);

            if(!solAct.completa()) {
                backtrackingUna();

                if(!encertat) {
                    solAct.desanotarCandidat(iCan);
                }
            }
            else encertat = true;
        }

        iCan.seguent();
    }
}

void Solucionador::backtrackingMillor() {

    Candidats iCan = solAct.inicialitzarCandidats();

    while(!iCan.esFi() && solAct.potSerMillor(solOpt)) { // FICAR EL potSerMillor AQUÍ FA QUE VAGI MÉS RÀPID, JA QUE EL CANDIDAT ACTUAL NO AFECTA AL RESULTAT DE potSerMillor
        if(solAct.acceptable(iCan)) {
            solAct.anotarCandidat(iCan);

            if(!solAct.completa()) {
                backtrackingMillor();
            }
            else {
                if(solAct.esMillor(solOpt)) {
                    solOpt = solAct;
                }
            }

            solAct.desanotarCandidat(iCan);
        }

        iCan.seguent();
    }
}
