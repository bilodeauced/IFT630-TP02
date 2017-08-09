#include "ProcessusChasseur.h"

ProcessusChasseur::ProcessusChasseur(MpiContext& mpi, Map map, Case c) : ProcessusJoueur{ mpi,map,c }
{ }

void ProcessusChasseur::exec()
{
    do
    {
        mpi.envoyer(requeteBouger(BOUGER_CHASSEUR, c, Case{ c.x,c.y - 1 }), 0, TAG_REQUETE);
    } while (lireMessage());
    mpi.envoyer("arrete", 0, TAG_ARRETER);
    std::cout << mpi.obtenirRang() << " : arreter" << std::endl;
}