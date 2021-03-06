// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#ifndef SOLUCIO_H
#define SOLUCIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Candidats.h"

using namespace std;

/**
 Permet gestionar la solució del problema.
**/
class Solucio
{
    public:
        /**
         @pre  Cert.
         @post S'ha creat una solució buida.
        **/
        Solucio();

        /**
         @param fin És el fitxer d'entrada a partir del qual es crea la solució inicial.
         @param alcada_max Indica l'edifici més alt que podrem utilitzar en aquesta solució.
         @param trobarMillor Indica si s'ha de preparar la solució per trobar millor solució.
         @pre  Cert.
         @post S'ha creat una solució inicial a partir del fitxer 'fin' i els paràmetres 'alcada_max' i 'trobarMillor'.
        **/
        Solucio(ifstream& fin, int alcada_max, bool trobarMillor);


        /**
         @pre  'iCan' és acceptable.
         @post Ha anotat el candidat 'iCan' a la solució.
        **/
        void anotarCandidat(const Candidats& iCan);

        /**
         @pre  'iCan' és el darrer candidat anotat.
         @post Ha desanotat 'iCan' de la solució (l'últim candidat que s'havia anotat).
        **/
        void desanotarCandidat(const Candidats& iCan);


        /**
         @pre  Cert.
         @post Retorna el conjunt de candidats del nivell actual.
        **/
        Candidats inicialitzarCandidats() const;

        /**
         @pre  'opt' és una solució completa.
         @post Diu si la cota màxima d'aquesta solució parcial podria millorar la solució òptima 'opt'.
        **/
        bool potSerMillor(const Solucio& opt) const;

        /**
         @pre  Aquesta solució és completa i 'opt' també ho és.
         @post Diu si aquesta solució és millor que la solució 'opt'.
        **/
        bool esMillor(const Solucio& opt) const;

        /**
         @pre  Cert.
         @post Diu si el candidat 'iCan' es pot afegir a aquesta solució.
        **/
        bool acceptable(const Candidats& iCan) const;

        /**
         @pre  Cert.
         @post Diu si aquesta solució és completa.
        **/
        bool completa() const;

        /**
         @pre  Cert.
         @post Ha mostrat aquesta solució per pantalla.
        **/
        void mostrar() const;

    private:
        int nivell, /**< Guarda el nivell actual de la solució. */
            aMax, /**< Guarda l'alçada màxima d'edifici que es podrà fer servir en aquesta solució. */
            mida, /**< Guarda la mida de la solució [mida = núm.Columnes = núm.Files]. */
            alcada_total; /**< Guarda l'alçada total de la solució, que és la suma de les alçades de tots els edificis que hi ha actualment a la solució. */

        vector<vector<bool>> aFiles, /**< Guarda quines alçades s'han fet servir a cada FILA. */
                             aColumnes; /**< Guarda quines alçades s'han fet servir a cada COLUMNA. */

        vector<int> alcades, /**< Guarda la quantitat d'edificis disponibles que hi ha de cada alçada. Inicialment s'ha llegit de fitxer. */
                    sol, /**< Guarda la solució actual (parcial o final). Es guarda en un vector però s'interpreta com una matriu de mida*mida. */
                    vN, /**< TARGET. VISTES DEL NORD. Guarda el nombre d'edificis que S'HAN DE VEURE des del NORD per cada COLUMNA. */
                    vS, /**< TARGET. VISTES DEL SUD. Guarda el nombre d'edificis que S'HAN DE VEURE des del SUD per cada COLUMNA. */
                    vE, /**< TARGET. VISTES DE L'EST. Guarda el nombre d'edificis que S'HAN DE VEURE des de l'EST per cada FILA. */
                    vW, /**< TARGET. VISTES DE L'OEST. Guarda el nombre d'edificis que S'HAN DE VEURE des de l'OEST per cada FILA. */
                    matSumes; /**< Es genera durant el constructor, només en el cas que es vulgui preparar per trobar la millor solució. Es guarda en un vector però s'interpreta com una matriu de mida*mida. Permetrà decidir si una solució pot ser millor que una altra. */

        vector< pair<int, vector<int>> > vista_N, /**< PARCIAL. Guarda, per cada columna, el nombre d'edificis que es veuen ACTUALMENT des del NORD (al first del pair) i un vector que es fa servir com a pila que guarda al final de tot l'alçada de l'edifici més alt que es veu des del NORD (al second del pair). */
                                         vista_W; /**< PARCIAL. Guarda, per cada fila, el nombre d'edificis que es veuen ACTUALMENT des de l'OEST (al first del pair) i un vector que es fa servir com a pila que guarda al final de tot l'alçada de l'edifici més alt que es veu des de l'OEST (al second del pair). */


        /**
         @pre  S'acaben d'inicialitzar tots els atributs d'aquesta solució.
         @post S'ha calculat el vector 'matSumes' (que es tracta com una matriu de mida*mida). S'ha calculat tenint en compte que no hi hagi repeticions d'alçades en fila i columna.
        **/
        void calcularMatriuSumes();
};

#endif // SOLUCIO_H
