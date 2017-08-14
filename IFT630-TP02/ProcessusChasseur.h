#ifndef PROCESSUS_CHASSEUR_H  
#define PROCESSUS_CHASSEUR_H

#include "ProcessusJoueur.h"

struct ProcessusChasseur : ProcessusJoueur {
    ProcessusChasseur(MpiContext& mpi, Map map, Case c);
protected:
    void exec();
	bool lireMessage();    // return false si doit arreter
};

#endif 
