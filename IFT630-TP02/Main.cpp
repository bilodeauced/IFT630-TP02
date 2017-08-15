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
}