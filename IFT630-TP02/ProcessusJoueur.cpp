#include "ProcessusJoueur.h"

ProcessusJoueur::ProcessusJoueur(MpiContext & mpi, Map map, Case c) : Processus{ mpi,map }, c{ c }, astar(map.obtenirMaxY(), map.obtenirMaxX())
{ }

void ProcessusJoueur::pret()
{
	mpi.envoyer(PRET, 0, TAG_PRET);

	std::string message;
	std::vector<std::string> demande;

	message = mpi.recevoir(0, TAG_COMMENCER);
	demande = split(message, SEPARATEUR);

	c = lireCase(demande[0]);
	map.updateMap(std::move(demande[1]));
}