#ifndef MPI_CONTEXTE_H  
#define MPI_CONTEXTE_H

#include <mpi.h>
#include <string>

class MpiContext {
    int nbProcs;
    int rang;
public:
    MpiContext(int argc, char *argv[]);
    MpiContext(const MpiContext&) = delete;
    ~MpiContext();
    int obtenirNbProcs();
    int obtenirRang();  
    void envoyer(const std::string &msg, int dest, int msgTag);
    std::string recevoir(int emetteur, int msgTag);
    std::string recevoirToutEmetteur(int msgTag);
    std::string recevoirToutTag(int emetteur);
};

#endif 
