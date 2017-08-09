#ifndef PROCESSUS_FACTORY_H  
#define PROCESSUS_FACTORY_H

#include "ProcessusChasseur.h"
#include "ProcessusMap.h"
#include "ProcessusRat.h"

struct ProcessusFactory  {
    static Processus* creerProcesus(MpiContext& mpi, std::string nomFichier, int nbRat, int nbChasseur);
};

#endif 
