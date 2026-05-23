//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _ETUDIANT_H_
#define _ETUDIANT_H_
#include "Devoir.h"
#include "Question.h"
class Video;
class Etudiant:public User{
public:
    Etudiant(int id,std::string Nom,std::string Email);
    Etudiant(const Etudiant& e);
    ~Etudiant();
    Classe* RechercherClasse(std::string code);
    bool InscrireClasse(Classe&);
    bool estInscri(int);
    bool DemandeDejaAtt(int);
    bool AnnulerDemande(int);
    std::vector<Classe> getCoursInscri();
    std::vector<Annonce> getAnnonces();
    std::vector<Devoir> getDevoirs();
    std::vector<Question> getMesQuestions();
    std::vector<Demande> getMesDemandes();
    std::vector<Document> getMesDocuments();
    std::vector<Video> getMesVideos();
    bool addQuestion(Question&);
};

#endif //Etudiant