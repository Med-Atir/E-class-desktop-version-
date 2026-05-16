//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Etudiant.h"
#include "../Includes/Question.h"
#include "../Database/Db.h"

Etudiant::Etudiant(int id, std::string Nom, std::string Email) :User(id,Nom,Email){}

Etudiant::Etudiant(const Etudiant &e):User(e) {}
Etudiant::~Etudiant(){}

void Etudiant::addQuestion(Question &q) {
   return;DB::addQuestion(q);
}

std::vector<Annonce> Etudiant::getAnnonces() {
   return DB::getEtudiantAnnonces(this->Id);
}

std::vector<Classe> Etudiant::getCoursInscri() {
    return DB::getEtudiantclasse(this->Id);
}

std::vector<Devoir> Etudiant::getDevoirs() {
    return DB::getEtudiantDevoirs(this->Id);
}

bool Etudiant::InscrireClasse(Classe &c) {
   return DB::InscrireClasse(this->getId(),c);
}

std::vector<Question> Etudiant::getMesQuestions() {
    return DB::getEtudiantQuestions(this->getId());
}

Classe* Etudiant::RechercherClasse(std::string code) {
    return DB::RechercherClasse(code);
}

bool Etudiant::estInscri(int idclass) {
    if (DB::etdInscrit(this->getId(),idclass))
        return true;
    return false;
}

bool Etudiant::DemandeDejaAtt(int idclass) {
    if (DB::demandeDejaAtt(this->getId(),idclass))
        return true;
    return false;
}