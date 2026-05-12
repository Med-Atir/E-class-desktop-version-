//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _PROFESSEUR_H_
#define _PROFESSEUR_H_
#include "Annonce.h"
#include "User.h"
#include "Classe.h"
#include "Vect.h"
#include "Demande.h"
#include "Document.h"
#include "Question.h"

class Professeur:public User {
public:
    Professeur(int Id,std::string Nom,std::string Email);
    ~Professeur();
    std::string AddClasse(Classe&);
    bool DelClasse(Classe&);
    Vect<Demande> getDemandes(Classe&);
    Vect<Classe> getClasses();
    bool AccepteDemande(Demande&);
    bool RejetDemande(Demande&);
    bool AddAnnoce(Annonce&);
    bool DelAnnonce(Annonce&);
    Vect<Annonce> getAnnonces();
    bool AddDocument(Classe&);
    bool DelDocument(Document&);
    Vect<Document> getDocuments(Classe&);
    Vect<Question> getQuestions();
    bool AddReponse(std::string reponse);
};


#endif //Professeur