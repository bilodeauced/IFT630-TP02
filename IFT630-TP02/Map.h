#ifndef MAP_H  
#define MAP_H

#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>

struct Case {
    int x, y;
    Case();
    Case(int x, int y);
};

enum ResultatBouger
{
    RIEN, // Action impossible, donc pas de mouvement
    BOUGER_CASE_VIDE, // Bouger sur une case vide
    BOUGER_RAT, // Bouger sur un rat
    BOUGER_FROMAGE, // Bouger sur un fromage
    BOUGER_SORTIE // Bouger en dehors de la ville
};

class Map {
    std::vector<char> cases;
    const int maxY;
    const int maxX;
    Map(std::vector<char> cases, int maxX, int  maxY);
    bool peutBougerRat(Case c, Case nC);
    bool peutbougerChasseur(Case c, Case nC);
public:
    static const char CASE_VIDE;
    static const char CASE_MUR;
    static const char CASE_RAT;
    static const char CASE_CHASSEUR_RAT;
    static const char CASE_FROMAGE;
	static const char CASE_SORTIE;

    static Map creerMapViaFichier(std::string && nomFichier);
    static Map creerMap(std::string && stringDeCases);
	void updateMap(std::string && stringDeCases);
    char& operator()(int x, int y); // conditon : x <= maxX, y <= maxY
    char& operator()(Case c); // conditon : x <= maxX, y <= maxY
    const int obtenirMaxX();
    const int obtenirMaxY();
	const std::vector<char> obtenirMap();
    ResultatBouger bougerRat(Case c, Case nC);
    ResultatBouger bougerChasseur(Case c, Case nC);
    std::vector<Case> trouver(char c);
    std::string toString();
};


#endif 
