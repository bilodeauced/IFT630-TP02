#include "Map.h"
#include "ProcessusFactory.h"

// parametre 
// 1 - fichier pour init la map
// 2 - nb de rat
// 3 - nb chasseur de rat
int main(int argc, char* argv[]) {
    // 4, car le premier est toujours le nom de l'executable
    if (argc != 4) { return -1; }
    MpiContext mpi{ argc,argv };
    Processus *p = ProcessusFactory::creerProcesus(mpi, argv[1], atoi(argv[2]), atoi(argv[3]));
    p->executer();
    delete p;

   /* Map map = Map::creerMapViaFichier(std::move(argv[1]));
    AStar astar{ map.obtenirMaxY(), map.obtenirMaxX() };
    vector<char> m = map.obtenirMap();
    vector<Case> goal = map.trouver(Map::CASE_FROMAGE);
    cout << map.toString() << endl;
    for (Case g : goal)
        std::cout << "goal Case: " << g.x << " ," << g.y << endl;
    for (Case c : map.trouver(Map::CASE_RAT)) {
        //Case c = map.trouver(Map::CASE_RAT)[1];
        std::cout << "avant a* Case: " << c.x << " ," << c.y << endl;
        c = astar.findNextMoveToBestGoal("rat", m, c, goal);
        std::cout << "apres a* Case: " << c.x << " ," << c.y << endl;
    }
    for (Case c : map.trouver(Map::CASE_CHASSEUR_RAT)) {
        std::cout << "avant a* Case: " << c.x << " ," << c.y << endl;
        c = astar.findNextMoveToBestGoal("chaseur", m, c, goal);
        std::cout << "apres a* Case: " << c.x << " ," << c.y << endl;
    }*/
}