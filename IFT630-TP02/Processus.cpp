#include "Processus.h"

Processus::Processus(MpiContext& mpi, Map map) : mpi{ mpi }, map{ map }
{ }

void Processus::executer()
{
    pret();
    exec();
}

void Processus::pret()
{
    mpi.envoyer(PRET, 0, TAG_PRET);
    mpi.recevoir(0, TAG_COMMENCER);
}

std::vector<std::string> Processus::split(const std::string & s, char delim)
{
    std::vector<std::string> res;
    std::stringstream ss{ s };
    std::string item;
    while (std::getline(ss, item, delim)) {
        res.push_back(item);
    }
    return res;
}

std::string Processus::requeteBouger(const std::string bouger,Case c, Case nC)
{
    std::stringstream ss;
    ss << mpi.obtenirRang() << SEPARATEUR << bouger << SEPARATEUR << c.x << SEPARATEUR_CASE
       << c.y << SEPARATEUR << nC.x << SEPARATEUR_CASE << nC.y;
    return ss.str();
}

Case Processus::lireCase(std::string c)
{   
    std::vector<std::string> vectorCase = split(c, SEPARATEUR_CASE);
    return Case { stoi(vectorCase[0]),stoi(vectorCase[1]) };
}