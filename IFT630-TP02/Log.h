#ifndef LOG_H  
#define LOG_H

#include "Map.h"
#include <chrono>
#include <string>
#include <vector>

class Log {
    const std::string FICHIER = "out.txt";
    const int DELAI_PHOTO = 1000;

    struct Processus {
        int nb;
        int requeteMouvement;
        int requeteMouvementRefuser;
        Processus(int nb);
    };
    std::vector<std::string> evenement;
    std::vector<Processus> processus;
    std::vector<std::string> photoMap;
    std::chrono::time_point<std::chrono::system_clock> debut;
    std::chrono::time_point<std::chrono::system_clock> fin;
    std::chrono::time_point<std::chrono::system_clock> dernierePhoto;
public:
    Log(int nbProcs);
    void commencer(Map& map);
    void finir(Map& map);
    std::string toString();
    void ecrireDansFichier();
    void prendrePhotoMap(Map& map); // le fait seulement si le delai est passer
    void ajouterMangerFromage(int proc,Case f);
    void ajouterRatAttraper(int procChasseur,int procRat, Case c);
    void ajouterRatSorti(int proc, Case r);
    void ajouterMiaulement(int proc, Case c);
    void ajouterRequeteMouvement(int proc);
    void ajouterRequeteMouvementRejeter(int proc);
};


#endif 
