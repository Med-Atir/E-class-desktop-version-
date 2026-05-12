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
    Annonce(int id,std::string titre,std::string contenu,QDateTime date,const Professeur& prof,const Classe& cl);
    ~Annonce();
    int getId();
    std::string getTitre();
    std::string getContenu();
    QDateTime getDate();
    Professeur* getProf();
    Classe* getClasse();
    void setId(int id);
    void setTitre(std::string titre);
    void setContenu(std::string contenu);
    void setDate(QDateTime date);
    void setProf(const Professeur& prof);
    void setClasse(const Classe& cl);
private:
    int Id;
    std::string titre;
    std::string contenu;
    QDateTime date;
    Professeur* prof;
    Classe* classe;
};

#endif //Annonce
