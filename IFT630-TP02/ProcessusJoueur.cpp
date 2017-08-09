#include "ProcessusJoueur.h"

ProcessusJoueur::ProcessusJoueur(MpiContext & mpi, Map map, Case c) : Processus{ mpi,map }, c{ c }
{ }

bool ProcessusJoueur::lireMessage()
{
    std::string message;
    std::vector<std::string> demande;
    do
    {
       message = mpi.recevoirToutTag(0);
       demande = split(message,SEPARATEUR);
       if (demande.size() > 1)
       {
           if (demande[1] == BOUGER_RAT)
           {
               map.bougerRat(lireCase(demande[2]),lireCase(demande[3]));
               if (demande[0] == std::to_string(mpi.obtenirRang())) 
               {
                   c = lireCase(demande[3]);
               }
           }
           else if (demande[1] == BOUGER_CHASSEUR)
           {
               map.bougerChasseur(lireCase(demande[2]), lireCase(demande[3]));
               if (demande[0] == std::to_string(mpi.obtenirRang())) 
               {
                   c = lireCase(demande[3]);
               }
           }
       }
    } while (message != ARRETER && demande[0] != std::to_string(mpi.obtenirRang()));

    if (message == ARRETER) {
        // le procesus doit arreter
        return false;
    }

    return true;
}