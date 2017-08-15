#ifndef PROCESSUS_JOUEUR_H  
#define PROCESSUS_JOUEUR_H

#include "Processus.h"
#include "AStar.h"

struct ProcessusJoueur : Processus {
protected:
    Case c;
	AStar astar;
    ProcessusJoueur(MpiContext& mpi, Map map, Case c);
	void pret();
};


#endif 

