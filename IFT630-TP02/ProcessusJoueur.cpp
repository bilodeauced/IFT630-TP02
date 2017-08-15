#include "ProcessusJoueur.h"

ProcessusJoueur::ProcessusJoueur(MpiContext & mpi, Map map, Case c) : Processus{ mpi,map }, c{ c }, astar(map.obtenirMaxY(), map.obtenirMaxX())
{ }

void ProcessusJoueur::attendreDemarrage() 
{
	std::string message;
	std::vector<std::string> demande;

	do
	{
		message = mpi.recevoirToutTag(0);
		demande = split(message, SEPARATEUR);

		if (demande[0] == COMMENCER) {
			map.updateMap(std::move(demande[1]));
			c = lireCase(demande[2]);
		}
	} while (demande[1] != COMMENCER);
}

void ProcessusJoueur::pret()
{
	mpi.envoyer(PRET, 0, TAG_PRET);
	std::cout << mpi.obtenirRang() << " : pret" << std::endl;

	std::string message;
	std::vector<std::string> demande;

	message = mpi.recevoir(0, TAG_COMMENCER);
	demande = split(message, SEPARATEUR);

	c = lireCase(demande[0]);
	map.updateMap(std::move(demande[1]));
}