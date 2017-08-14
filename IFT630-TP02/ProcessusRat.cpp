#include "ProcessusRat.h"

ProcessusRat::ProcessusRat(MpiContext& mpi, Map map, Case c) : ProcessusJoueur{ mpi,map,c }, tourAFuir{}
{ }

void ProcessusRat::exec()
{
    do
    {
		Case dest;
		if(tourAFuir == 0)
			dest = astar.findNextMoveToBestGoal("rat", map.obtenirMap(), c, map.trouver(Map::CASE_FROMAGE));
		else
			dest = astar.findNextMoveToBestGoal("rat", map.obtenirMap(), c, map.trouver(Map::CASE_SORTIE));
        mpi.envoyer(requeteBouger(BOUGER_RAT, c, dest), 0, TAG_REQUETE);
    } while (lireMessage());
    //mpi.envoyer("arrete", 0, TAG_ARRETER);
    //std::cout << mpi.obtenirRang() << " : arreter" << std::endl;
}

bool ProcessusRat::lireMessage()
{
	std::string message;
	std::vector<std::string> demande;
	bool relire;


	do {
		relire = false;
		message = mpi.recevoir(0, 0);
		demande = split(message, SEPARATEUR);

		if (message == ARRETER) return false;

		if (demande.size() > 1)
		{
			if (demande[1] == BOUGER)
			{
				c = lireCase(demande[2]);
				map.updateMap(std::move(demande[3]));
			}
			else if (demande[1] == MIAULEMENT)
			{
				std::vector<Case> goals;
				goals.emplace_back(lireCase(demande[2]));
				astar.findNextMoveToBestGoal("chasseur", map.obtenirMap(), c, goals);
				if (astar.getCostToGoal() <= 10)
					tourAFuir = 5;
				relire = true;
			}
		}
	} while(relire);

	
	return true;
}
