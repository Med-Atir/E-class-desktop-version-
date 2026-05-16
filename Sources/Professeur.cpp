//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Professeur.h"
#include "../Database/Db.h"
#include "../Includes/Document.h"
#include "../Includes/Devoir.h"

Professeur::Professeur(int Id,std::string Nom,std::string Email):User(Id,Nom,Email) {
}

Professeur::~Professeur() {

}

bool Professeur::AddClasse(Classe& cl) {
   return DB::AddClasse(cl,this->Id);
}

bool Professeur::DelClasse(Classe &cl) {
   return DB::DelClasse(cl);
}

std::vector<Demande> Professeur::getDemandes() {
   return DB::getDemandes(this->Id);
}

std::vector<Classe> Professeur::getMesClasses() {
   return DB::getProfclasse(this->Id);
}

bool Professeur::AccepteDemande(Demande &d) {
   return DB::AccepteDemande(d);
}

bool Professeur::AddAnnoce(Annonce &a) {
   return DB::AddAnnoce(a);
}

bool Professeur::AddDocument(Document& d,Classe &c) {
   return DB::AddDocument(d,c);
}

bool Professeur::AddReponse(Question& q,std::string reponse) {
   return DB::AddReponse(q,reponse);
}

bool Professeur::DelAnnonce(Annonce &a) {
   return DB::DelAnnonce(a);
}

bool Professeur::DelDocument(Document &d) {
   return DB::DelDocument(d);
}

std::vector<Document> Professeur::getDocuments() {
   return DB::getProfDocuments(this->getId());
}

bool Professeur::RejetDemande(Demande &d) {
   return DB::RejetDemande(d);
}

std::vector<Annonce> Professeur::getAnnonces() {
   return DB::getProfAnnonces(this->getId());
}

std::vector<Question> Professeur::getQuestions() {
   return DB::getProfQuestions(this->getId());
}

std::vector<Devoir> Professeur::getDevoirs() {
   return DB::getProfDevoirs(this->getId());
}
