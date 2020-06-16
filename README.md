# Gratacels
*** Distribució de gratacels en una illa d'edificis quadrada ***

Utilització: ./gratacels.exe opcio fitxer


opcio pot ser:

-h, --help  : mostra aquest missatge d'ajuda i surt.

-u alt      : cerca una solució que compleixi les restriccions del problema sense fer servir edificis d'una altura superior a alt.

-m          : cerca la solució que maximitza la suma de les altures de tots els edificis de la solució.

fitxer        ha de ser un fitxer de text amb totes les dades amb el format següent:

              dimensió(n) // dimensió matriu
              
              vN1 vN2 ... VNn // visibles des del nord
              
              vS1 vS2 ... VSn // visibles des del sud
              
              vE1 vE2 ... VEn // visibles des del est
              
              vW1 vW2 ... VWn // visibles des del oest
              
              altura maxima(m) // altura màxima disponible
              
              a1 a2 ... am // edificis disponibles de cada altura
              
Al directori arrel d'aquest repositori deixem uns fitxers de text d'exemple de dades d'entrada. Són els fitxers anomentats "gN_V.txt", on la N correspon a la mida de la matriu d'aquest fitxer, i la V correspon al número de fitxer (per diferenciar entre fitxers que contenen matrius diferents però de la mateixa).
