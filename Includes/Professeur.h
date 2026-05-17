//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _PROFESSEUR_H_
#define _PROFESSEUR_H_
#include "Annonce.h"
#include "User.h"
#include "Classe.h"
#include <vector>
#include "Demande.h"
#include "Question.h"
class Devoir;
class Document;
class Professeur:public User {
public:
    Professeur(int Id,std::string Nom,std::string Email);
    ~Professeur();
    bool AddClasse(Classe&);
    bool DelClasse(Classe&);
    bool addDevoir(Devoir&);
    std::vector<Demande> getDemandes();
    std::vector<Classe> getMesClasses();
    bool AccepteDemande(Demande&);
    bool RejetDemande(Demande&);
    bool AddAnnoce(Annonce&);
    bool DelAnnonce(Annonce&);
    std::vector<Annonce> getAnnonces();
    bool AddDocument(Document&,Classe&);
    bool DelDocument(Document&);
    std::vector<Document> getDocuments();
    std::vector<Devoir> getDevoirs();
    std::vector<Question> getQuestions();
    bool AddReponse(Question&,std::string reponse);
};


#endif //Professeur