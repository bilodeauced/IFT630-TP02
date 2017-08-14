#ifndef PROCESSUS_MAP_H  
#define PROCESSUS_MAP_H

#include "Processus.h"
#include "Log.h"
#include <cstdlib>

struct ProcessusMap : Processus {
    ProcessusMap(MpiContext& mpi, Map map);
protected:
    void exec();
    void pret();
private:
    enum Etat {
        EN_COURS, // en cours
        ARRETER // arreter
    };
    struct Rat {
        Etat etat;
        int processus;
        Case c;
        Rat(int processus, Case c);
    };
    std::vector<Rat> rats;
    Log log;
    void traiterResultatBouger(std::string s, std::vector<std::string> demande, ResultatBouger res);
};


#endif 
