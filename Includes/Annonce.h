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
    Annonce(int id,std::string titre,std::string contenu,QDateTime date,int idprof,int idclasse);
    ~Annonce();
    int getId();
    std::string getTitre();
    std::string getContenu();
    QDateTime getDate();
    Professeur* getProf();
    Classe* getClasse();
    int getIdprof();
    int getIdclasse();
    void setId(int id);
    void setTitre(std::string titre);
    void setContenu(std::string contenu);
    void setDate(QDateTime date);
    void setProf(int idprof);
    void setClasse(int idclasse);
private:
    int Id;
    std::string titre;
    std::string contenu;
    QDateTime date;
    int idprof;
    int idclasse;
};

#endif //Annonce
