//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _QUESTION_H_
#define _QUESTION_H_
#include <QDateTime>

class Professeur;
class Etudiant;
class Classe;

class Question {
public:
    Question(int id,std::string cont,QDateTime dateQ,int idetd,int idpr,int idcl,bool estR = false,QDateTime* dateR = nullptr,std::string* Reponse = nullptr);
    Question(const Question&);
    ~Question();
    int getId();
    std::string getContenu();
    QDateTime getDateQ();
    Etudiant* getEtd();
    Professeur* getProf();
    Classe* getClasse();
    bool getEtat();
    QDateTime* getDateR();
    std::string* getReponse();
    void setId(int id);
    void setContenu(std::string cont);
    void setDateQ(QDateTime dateq);
    void setEtat(bool etat);
    void setDateR(const QDateTime& dater);
    void setReponse(std::string* reponse);
    void setEtd(int idetd);
    void setProf(int idpr);
    void setClasse(int idcl);
    int getIdEtd();
    int getIdProf();
    int getIdClasse();
private:
    int id;
    std::string contenu;
    QDateTime dateQuestion;
    int idEtd;
    int idProf;
    int idClasse;
    bool estRepondu;
    QDateTime* dateReponse;//les attributs qui peuvent etre null
    std::string* Reponse;
};

#endif //_QUESTION_H_