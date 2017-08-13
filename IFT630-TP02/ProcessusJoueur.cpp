#include "ProcessusJoueur.h"

ProcessusJoueur::ProcessusJoueur(MpiContext & mpi, Map map, Case c) : Processus{ mpi,map }, c{ c }
{ }

bool ProcessusJoueur::lireMessage()
{
    std::string message;
    std::vector<std::string> demande;

	message = mpi.recevoirToutTag(0);
    demande = split(message,SEPARATEUR);
	if (demande.size() > 1)
	{
		if (demande[1] == BOUGER)
		{
			c = lireCase(demande[2]);
			map.updateMap(std::move(demande[3]));
		}
		else if (demande[1] == CAPTURER_RAT)
		{
			map.updateMap(std::move(demande[3]));
			if (demande[0] == std::to_string(mpi.obtenirRang())) 
			{
				c = lireCase(demande[3]);
			}
		}
		else if (demande[1] == SORTI_RAT) 
		{
			map.updateMap(std::move(demande[3]));
		}
		else if (demande[1] == MANGER_FROMAGE)
		{
			map.updateMap(std::move(demande[3]));
			if (demande[0] == std::to_string(mpi.obtenirRang()))
			{
				c = lireCase(demande[3]);
			}
		}
		else if (demande[1] == MIAULEMENT) 
		{
			// change rat mode
		}
		
    }

    if (message == ARRETER) {
        // le procesus doit arreter
        return false;
    }
	return true;
}

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