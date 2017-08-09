#ifndef PROCESSUS_MAP_H  
#define PROCESSUS_MAP_H

#include "Processus.h"


struct ProcessusMap : Processus {
    struct Rat;
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
    void traiterResultatBouger(std::string s, std::vector<std::string> demande, ResultatBouger res);
    void envoyerATous(const std::string& s);
};


#endif 
