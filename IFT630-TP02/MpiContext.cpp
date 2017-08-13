#include "MpiContext.h"

MpiContext::MpiContext(int argc, char * argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nbProcs); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);  
}

MpiContext::~MpiContext()
{
    MPI_Finalize();
}

int MpiContext::obtenirNbProcs()
{
    return nbProcs;
}

int MpiContext::obtenirRang()
{
    return rang;
}

void MpiContext::envoyer(const std::string & msg, int dest, int msgTag)
{
    MPI_Send(&msg[0], static_cast<int>(msg.size()), MPI_CHAR, dest, msgTag, MPI_COMM_WORLD);
}

std::string MpiContext::recevoir(int emetteur, int msgTag)
{
    enum  { BUFSIZE = 256 };
    char buff[BUFSIZE];
    MPI_Status stat;
    MPI_Recv(buff, BUFSIZE, MPI_CHAR, emetteur, msgTag, MPI_COMM_WORLD, &stat);
    int nbRecus;
    MPI_Get_count(&stat, MPI_CHAR, &nbRecus);
    return std::string{ buff, buff + nbRecus };
}

std::string MpiContext::recevoirToutEmetteur(int msgTag)
{
    return recevoir(MPI_ANY_SOURCE,msgTag);
}

std::string MpiContext::recevoirToutTag(int emetteur)
{
    return recevoir(emetteur, MPI_ANY_TAG);
}