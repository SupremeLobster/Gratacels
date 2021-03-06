// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#include "Solucio.h"

Solucio::Solucio() {}

Solucio::Solucio(ifstream& fin, int alcada_max, bool trobarMillor) {

    nivell = alcada_total = 0;
    fin >> mida;

    sol.resize(mida*mida, 0);

    vector<int> vAux(1, 0);
    pair<int, vector<int>> pAux(0, vAux);
    vista_N.resize(mida, pAux);
    vista_W.resize(mida, pAux);

    int aux;

    for(int i=0; i<mida; i++) {
        fin >> aux;
        vN.push_back(aux);
    }
    for(int i=0; i<mida; i++) {
        fin >> aux;
        vS.push_back(aux);
    }
    for(int i=0; i<mida; i++) {
        fin >> aux;
        vE.push_back(aux);
    }
    for(int i=0; i<mida; i++) {
        fin >> aux;
        vW.push_back(aux);
    }

    int aMax_temp;
    fin >> aMax_temp;
    if(alcada_max != 0) aMax = min(alcada_max, aMax_temp);
    else aMax = aMax_temp;

    alcades.push_back(0); // PRIMERA POSICIÓ BUIDA
    for(int i=0; i<aMax; i++) {
        // POT SER QUE NO HAGI DE LLEGIR TOTES LES ALÇADES DISPONIBLES
        // SI L'ALÇADA MÀXIMA ENTRADA PER L'USUARI ÉS MENOR AL NOMBRE D'ALÇADES DISPONIBLES
        int aux;
        fin >> aux;
        alcades.push_back(aux);
    }


    vector<bool> auxV(aMax+1, false);

    aColumnes.resize(mida, auxV);
    aFiles.resize(mida, auxV);

    if(trobarMillor) calcularMatriuSumes();

    fin.close();
}

void Solucio::anotarCandidat(const Candidats& iCan) {

    int alcada = iCan.actual();
    int fil = nivell/mida;
    int col = nivell%mida;

    if(alcada > vista_N[col].second.back()) {
        vista_N[col].second.push_back(alcada);
        vista_N[col].first++;
    }
    if(alcada > vista_W[fil].second.back()) {
        vista_W[fil].second.push_back(alcada);
        vista_W[fil].first++;
    }

    aFiles[fil][alcada] = true;
    aColumnes[col][alcada] = true;

    alcades[alcada]--;
    alcada_total += alcada;

    sol[nivell] = alcada;

    nivell++;
}

void Solucio::desanotarCandidat(const Candidats& iCan) {

    nivell--;

    int alcada = iCan.actual();
    int fil = nivell/mida;
    int col = nivell%mida;

    if(alcada == vista_N[col].second.back()) {
        vista_N[col].second.pop_back();
        vista_N[col].first--;
    }
    if(alcada == vista_W[fil].second.back()) {
        vista_W[fil].second.pop_back();
        vista_W[fil].first--;
    }

    alcades[alcada]++;
    aFiles[fil][alcada] = false;
    aColumnes[col][alcada] = false;

    alcada_total -= alcada;

    sol[nivell] = 0;
}

Candidats Solucio::inicialitzarCandidats() const {

    return Candidats(aMax);
}

bool Solucio::potSerMillor(const Solucio& opt) const {

    return alcada_total+matSumes[nivell] >= opt.alcada_total;
}

bool Solucio::esMillor(const Solucio& opt) const {

    return alcada_total > opt.alcada_total;
}

bool Solucio::acceptable(const Candidats& iCan) const {

    int aActual = iCan.actual();
    int fil = nivell/mida;
    int col = nivell%mida;
    int vista_S = 0, vista_E = 0;

    if(fil == mida-1) {
        // SUD
        int maxS = aActual;
        vista_S = 1;
        for(int i=fil-1; i>=0; i--) {
            int aux = sol[col+i*mida]; // AIXÍ ESTALVIO FER CÒPIES DEL VECTOR 'sol'
            if(aux > maxS) {maxS = aux; vista_S++;}
        }
    }
    if(col == mida-1) {
        // EST
        int maxE = aActual;
        vista_E = 1;
        for(int i=col-1; i>=0; i--) {
            int aux = sol[i+fil*mida]; // AIXÍ ESTALVIO FER CÒPIES DEL VECTOR 'sol'
            if(aux > maxE) {maxE = aux; vista_E++;}
        }
    }

    return  (
                (
                    (alcades[aActual] > 0)
                )
                &&
                (
                    (!aFiles[fil][aActual] && !aColumnes[col][aActual])
                )
                &&
                (
                    (fil<mida-1) || (vista_S==vS[col])
                )
                &&
                (
                    (col<mida-1) || (vista_E==vE[fil])
                )
                &&
                (
                    ( aActual>vista_N[col].second.back() && vista_N[col].first<vN[col] && aMax-aActual+1>=vN[col]-vista_N[col].first )
                    ||
                    ( aActual<=vista_N[col].second.back() && mida-(fil+1)>=vN[col]-vista_N[col].first )
                )
                &&
                (
                    ( aActual>vista_W[fil].second.back() && vista_W[fil].first<vW[fil] && aMax-aActual+1>=vW[fil]-vista_W[fil].first )
                    ||
                    ( aActual<=vista_W[fil].second.back() && mida-(col+1)>=vW[fil]-vista_W[fil].first )
                )
            );
}

bool Solucio::completa() const {

    return nivell == mida*mida;
}

void Solucio::mostrar() const {

    cout << "  "; for(int i=0; i<mida; i++) cout << vN[i] << " "; cout << endl;
    for(int i=0; i<mida; i++) {
        cout << vW[i] << " ";
        for(int j=0; j<mida; j++) cout << sol[j+i*mida] << " ";
        cout << vE[i] << endl;
    }
    cout << "  "; for(int i=0; i<mida; i++) cout << vS[i] << " "; cout << endl;

    cout << "Alçada total: " << alcada_total << endl;
}

void Solucio::calcularMatriuSumes() { // ALGORISME VORAÇ

    for(int k=0; k<mida*mida; k++) {
        vector<vector<bool>> aux_aFiles = aFiles, aux_aColumnes = aColumnes; // S'ACABA D'INICIALITZAR TOT A 'false'
        vector<int> aux_alcades = alcades;
        int suma = 0;

        for(int i=0; i<mida*mida-k; i++) {
            int fil = i/mida;
            int col = i%mida;
            int j = aMax;

            while( j>0 && (aux_alcades[j]<=0 || aux_aFiles[fil][j] || aux_aColumnes[col][j]) ) j--;

            if(j > 0) {
                aux_aFiles[fil][j] = true;
                aux_aColumnes[col][j] = true;
            }
            else {
                j = aMax;
                while(j>0 && aux_alcades[j]<=0) j--;
            }

            aux_alcades[j]--;
            suma += j;
        }

        matSumes.push_back(suma);
    }
}
