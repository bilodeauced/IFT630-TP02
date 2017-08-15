#ifndef PROCESSUS_H  
#define PROCESSUS_H

#include "Map.h"
#include "MpiContext.h"
#include <iostream>
#include <sstream>

struct Processus {
	//enum ID_MESSAGE{ BOUGER, BOUGER_RAT};
	
	const std::string BOUGER = "bouger";
	const std::string BOUGER_RAT = "bougerRat";
	const std::string BOUGER_CHASSEUR = "bougerChasseur";
	const std::string CAPTURER_RAT = "capturerRat";
	const std::string SORTI_RAT = "sortiRat";
	const std::string MANGER_FROMAGE = "mangerFromage";
	const std::string MIAULEMENT = "miaulement";
	const std::string ARRETER = "arreter";
	const std::string PRET = "pret";
	const std::string COMMENCER = "commencer";
	
    const char SEPARATEUR = '|';
    const char SEPARATEUR_CASE = ',';

    const int TAG_PRET = 0;
    const int TAG_COMMENCER = 1;
    const int TAG_REQUETE = 2;
    const int TAG_ARRETER = 3;

    void executer();
protected:
    MpiContext& mpi;
    Map map;
    Processus(MpiContext& mpi, Map map);
    virtual void exec() = 0;
    virtual void pret();
    virtual std::string requeteBouger(const std::string bouger,Case c, Case nC);
    std::vector<std::string> split(const std::string &s, char delim);
    Case lireCase(std::string c);
};

#endif 
