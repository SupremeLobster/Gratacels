// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#ifndef SOLUCIONADOR_H
#define SOLUCIONADOR_H

#include <chrono>
#include "Solucio.h"
#include "Candidats.h"

using namespace std::chrono;

/**
 Permet resoldre el problema de trobar una solució i el de trobar la millor solució, fent servir backtracking. També calcula el temps que tarda a executar cada un d'aquests algorísmes.
**/
class Solucionador
{
    public:
        /**
         @pre  Cert.
         @post S'ha creat un solucionador buit.
        **/
        Solucionador();


        /**
         @pre  'inicial' és una solució construida per paràmetres (no és buida).
         @post Diu si la solució 'inicial' té alguna solució.
        **/
        bool solucionarUna(const Solucio& inicial);

        /**
         @pre  Cert.
         @post Ha trobat la millor solució possible.
        **/
        void solucionarMillor(const Solucio& inicial);


        /**
         @pre  Cert.
         @post Retorna la primera solució que hagi trobat.
        **/
        Solucio get_UnaSolucio() const;

        /**
         @pre  Cert.
         @post Retorna la millor solució.
        **/
        Solucio get_MillorSolucio() const;

        /**
         @pre  Cert.
         @post Retorna el temps d'execució del backtracking.
        **/
        double get_time() const;

    private:
        Solucio solAct, /**< Guarda la solució parcial actual. En el cas de voler trobar UNA única solució també guardarà la solució final trobada. */
                solOpt; /**< Guarda la solució completa més òptima. Només s'usa si es vol trobar la MILLOR solució. */

        bool encertat; /**< És TRUE quan es troba una solució. Només s'usa pel cas de voler trobar UNA única solució. */

        high_resolution_clock::time_point t1, /**< Guarda el moment d'inici del backtracking. */
                                          t2; /**< Guarda el moment d'acabament del backtracking. */


        /**
         @pre  Cert.
         @post Ha trobat una solució (si n'hi ha alguna) fent backtracking.
        **/
        void backtrackingUna();

        /**
         @pre  Cert.
         @post Ha trobat la millor solució possible fent backtracking.
        **/
        void backtrackingMillor();
};

#endif // SOLUCIONADOR_H
