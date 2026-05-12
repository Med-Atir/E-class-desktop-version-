//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_
#include <string>
#include "Professeur.h"

class Document {
public:
    Document(int id,std::string titre,std::string cheminFichier,QDateTime date,const Professeur& prof,const Classe& cl);
    Document(const Document&);
    ~Document();
    int getID();
    std::string getTitre();
    std::string getCheminFichier();
    QDateTime getDate();
    Professeur* getProf();
    Classe* getClasse();
    void setId(int id);
    void setTitre(std::string titre);
    void setCheminFichier(std::string chemin);
    void setDate(QDateTime date);
    void setProf(const Professeur& pr);
    void setClasse(const Classe& cl);
private:
    int id;
    std::string titre;
    std::string cheminFichier;
    QDateTime date;
    Professeur* prof;
    Classe* classe;
};

#endif //Document