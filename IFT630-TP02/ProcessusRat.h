#ifndef PROCESSUS_RAT_H  
#define PROCESSUS_RAT_H

#include "ProcessusJoueur.h"

struct ProcessusRat : ProcessusJoueur {
    ProcessusRat(MpiContext& mpi, Map map, Case c);
protected:
    void exec();
};


#endif 
