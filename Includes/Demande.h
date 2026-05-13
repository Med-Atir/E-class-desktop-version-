//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _DEMANDE_H_
#define _DEMANDE_H_
#include <string>
#include <QDateTime>
#include "Classe.h"
class Etudiant;

class Demande {
public:
    Demande(int id,std::string status,QDateTime date,int idetd,int idclasse);
    ~Demande();
    int getId();
    int getIdEtd();
    int getIdClasse();
    std::string getStatus();
    QDateTime getDate();
    Etudiant* getEtudiant();
    Classe* getClasse();
    void setId(int id);
    void setStatus(std::string status);
    void setDate(QDateTime date);
    void setIdEtudiant(int id);
    void setIdClasse(int cl);
private:
    int Id;
    std::string Status;
    QDateTime Date;
    int idetd;
    int idclasse;
};

#endif //Demande