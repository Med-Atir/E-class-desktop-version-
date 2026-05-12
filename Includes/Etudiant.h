//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _ETUDIANT_H_
#define _ETUDIANT_H_
#include "Demande.h"
#include "Devoir.h"
#include "Question.h"

class Etudiant:public User{
public:
    Etudiant(int id,std::string Nom,std::string Email);
    Etudiant(const Etudiant& e);
    ~Etudiant();
    Classe RechercherClasseCode(std::string code);
    void InscrireClasse(const Classe&);
    std::vector<Classe> getCoursInscri();
    std::vector<Annonce> getAnnonces();
    std::vector<Devoir> getDevoirs();
    std::vector<Question> getQuestions();
    void addQuestion(const Question&);
};

#endif //Etudiant