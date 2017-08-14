#include "ProcessusChasseur.h"

ProcessusChasseur::ProcessusChasseur(MpiContext& mpi, Map map, Case c) : ProcessusJoueur{ mpi,map,c }
{ }

void ProcessusChasseur::exec()
{
    do
    {
		Case dest = astar.findNextMoveToBestGoal("chasseur", map.obtenirMap(), c, map.trouver(Map::CASE_RAT));
		if (astar.getCostToGoal() <= 10)
		{
			stringstream ss;
			ss << mpi.obtenirRang() << SEPARATEUR << MIAULEMENT << SEPARATEUR << c.x << SEPARATEUR_CASE << c.y;
			mpi.envoyer(ss.str(), 0, TAG_REQUETE);
		}
        mpi.envoyer(requeteBouger(BOUGER_CHASSEUR, c, dest), 0, TAG_REQUETE);
    } while (lireMessage());
    mpi.envoyer("arrete", 0, TAG_ARRETER);
    std::cout << mpi.obtenirRang() << " : arreter" << std::endl;
}

bool ProcessusChasseur::lireMessage()
{
	string message = mpi.recevoir(0, 0);
	vector<string> demande = split(message, SEPARATEUR);

	if (message == ARRETER) return false;

	if (demande.size() > 1)
	{
		if (demande[1] == BOUGER)
		{
			c = lireCase(demande[2]);
			map.updateMap(std::move(demande[3]));
		}
	}
	
	return true;
}
