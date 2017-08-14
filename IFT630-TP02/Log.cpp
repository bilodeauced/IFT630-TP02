#include "Log.h"

Log::Processus::Processus(int nb) : nb { nb }, requeteMouvement{}, requeteMouvementRefuser{}
{ }

Log::Log(int nbProcs) : evenement{}, processus{}, photoMap{}
{
    for (int i = 1; i < nbProcs; ++i)  // pas le 0 (c'est la map)
    {
        processus.push_back(Processus{ i });
    }
}

void Log::commencer(Map& map)
{
    debut = std::chrono::system_clock::now();
    photoMap.push_back(map.toString());
    dernierePhoto = std::chrono::system_clock::now();
}

void Log::finir(Map& map)
{
    fin = std::chrono::system_clock::now();
    photoMap.push_back(map.toString());
}

std::string Log::toString()
{
    std::string res{};

    res.append("---------------------------------\n");
    for (std::string photo : photoMap)
    {
        res.append(photo + '\n');
    }
    res.append("---------------------------------\n");
    for (Processus p : processus)
    {
        float pourcentage = p.requeteMouvementRefuser == 0 ? 100.f : (p.requeteMouvement - p.requeteMouvementRefuser) / p.requeteMouvementRefuser;
        res.append(std::to_string(p.nb) + ": mouvement: " + std::to_string(p.requeteMouvement - p.requeteMouvementRefuser) +
            ": demandeMouvement: " + std::to_string(p.requeteMouvement) + ", pourcentage:" + std::to_string(pourcentage) + '\n');
    }
    res.append("---------------------------------\n");
    for (std::string e : evenement)
    {
        res.append(e + '\n');
    }
    res.append("---------------------------------\n");
    res.append("temps (ms): " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut).count()) + '\n');
    
    return res;
}

void Log::ecrireDansFichier()
{
    std::string res{ toString() };
    std::copy(std::begin(res),
        std::end(res),
        std::ostream_iterator<char>{ std::ofstream{ FICHIER } });
}

// le fait seulement si le delai est passer
void Log::prendrePhotoMap(Map& map)
{
    auto t = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(t - dernierePhoto).count() > 1000) {
        photoMap.push_back(map.toString());
        dernierePhoto = std::chrono::system_clock::now();
    }
}

void Log::ajouterMangerFromage(int proc, Case f)
{
    evenement.push_back(std::to_string(proc) + ": Mange fromage a la case " + std::to_string(f.x) + "," + std::to_string(f.y));
}

void Log::ajouterRatAttraper(int procChasseur, int procRat, Case c)
{
    evenement.push_back(std::to_string(procChasseur) + ": Attraper rat (proc:" + std::to_string(procRat) + ") a la case " + std::to_string(c.x) + "," + std::to_string(c.y));
}

void Log::ajouterRatSorti(int proc, Case r)
{
    evenement.push_back(std::to_string(proc) + ": Rat sort a la case " + std::to_string(r.x) + "," + std::to_string(r.y));
}

void Log::ajouterMiaulement(int proc, Case c)
{
    evenement.push_back(std::to_string(proc) + ": Miaulement a la case " + std::to_string(c.x) + "," + std::to_string(c.y));
}

void Log::ajouterRequeteMouvement(int proc)
{
    ++processus[proc - 1].requeteMouvement;
}

void Log::ajouterRequeteMouvementRejeter(int proc)
{
    ++processus[proc - 1].requeteMouvementRefuser;
}

