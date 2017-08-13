#ifndef PROCESSUS_JOUEUR_H  
#define PROCESSUS_JOUEUR_H

#include "Processus.h"

struct ProcessusJoueur : Processus {
protected:
    ProcessusJoueur(MpiContext& mpi, Map map, Case c);
    Case c;
    bool lireMessage();    // return false si doit arreter
	void attendreDemarrage();
};


#endif 

