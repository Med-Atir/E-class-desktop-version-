//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _ANNONCE_H_
#define _ANNONCE_H_
#include <string>
#include <QDateTime>

#include "Classe.h"

class Professeur;

class Annonce {
public:
private:
    int Id;
    std::string titre;
    std::string contenu;
    QDateTime date;
    Professeur* prof;
    Classe* classe;
    
};

#endif //Annonce
