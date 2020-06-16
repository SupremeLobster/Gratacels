// Martí Mas Fullana
// Usuari u1956231
// Sessió p2

#ifndef CANDIDATS_H
#define CANDIDATS_H

/**
 Permet getionar el conjunt de candidats.
**/
class Candidats
{
    public:
        /**
         @pre 'maxim' > 0.
         @post S'ha inicialitzat el candidat.
        **/
        Candidats(int maxim);


        /**
         @pre  Cert.
         @post Passa al següent candidat.
        **/
        void seguent();


        /**
         @pre  Cert.
         @post Retorna el candidat actual.
        **/
        int actual() const;

        /**
         @pre  Cert.
         @post Retorna TRUE si ja no queden candidats.
        **/
        bool esFi() const;

    private:
        int iCan, /**< És el valor actual del candidat. */
            a_maxim; /**< És el valor màxim que pot prendre el candidat. */
};

#endif // CANDIDATS_H
