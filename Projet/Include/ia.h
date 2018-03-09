#ifndef _IA_H_
#define _IA_H_

#include "board.h"

/*
Renvoie le numero de la prochaine colonne a jouer en facile (num de 1 à board.width)
ou -1 si pas trouvé
la colonne est choisi aléatoirement
 */
int Easy(Board b);

int checkEmpty1(Board b,int num,int numOfrow);//?

/*
Renvoie le numero de la prochaine colonne a jouer en moyen (num de 1 à board.width)
ou -1 si pas trouvé
Le prochain colonne à jouer est la colonne qui complete une suite de 4 character
 */
int Medium(Board b, char character/*, int *num*/);

/*
Renvoie le numero de la prochaine colonne a jouer en hard (num de 1 à board.width)
ou -1 si pas trouvé
??
*/
int Hard(Board b/*, int *num*/);

#endif
