//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _DEMANDE_H_
#define _DEMANDE_H_
#include <string>
#include "Etudiant.h"
#include <QDateTime>

#include "Classe.h"

class Demande {
public:
    Demande(int id,std::string status,QDateTime date,Etudiant* etd,Classe* cl);
    ~Demande();

private:
    int Id;
    std::string Status;
    QDateTime Date;
    Etudiant* etudiant;
    Classe* classe;
};

#endif //Demande