#include "ProcessusFactory.h"

Processus* ProcessusFactory::creerProcesus(MpiContext& mpi, std::string nomFichier, int nbRat, int nbChasseur)
{
    Map map = Map::creerMapViaFichier(std::move(nomFichier));
    if (mpi.obtenirRang() == 0)
    {
        return new ProcessusMap{ std::move(mpi), std::move(map) };
    }
    if (mpi.obtenirRang() < nbRat + 1)
    {
        Case c = map.trouver(Map::CASE_RAT)[mpi.obtenirRang() - 1];
        return new ProcessusRat{ std::move(mpi), std::move(map), c };
    }
    if (mpi.obtenirRang() < nbRat + nbChasseur + 1)
    {
        Case c = map.trouver(Map::CASE_CHASSEUR_RAT)[mpi.obtenirRang() - nbRat - 1];
        return new ProcessusChasseur{ std::move(mpi), std::move(map), c };
    }
    throw;
}