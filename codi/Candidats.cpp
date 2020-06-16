// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#include "Candidats.h"

Candidats::Candidats(int maxim) {

    a_maxim = maxim;
    iCan = 1; // COMENCEM PER 1. ELS VECTORS D'ALÇADES TENEN LA PRIMERA POSICIÓ BUIDA
}

void Candidats::seguent() {

    iCan++;
}

int Candidats::actual() const {

    return iCan;
}

bool Candidats::esFi() const {

    return iCan > a_maxim;
}
