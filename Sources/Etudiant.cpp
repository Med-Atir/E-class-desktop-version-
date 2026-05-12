//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Etudiant.h"

#include <QSqlQuery>

Etudiant::Etudiant(int id, std::string Nom, std::string Email) :User(id,Nom,Email){}

Etudiant::Etudiant(const Etudiant &e):User(e) {}
Etudiant::~Etudiant(){}

void Etudiant::addQuestion(const Question &q) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO question(contenu,id_etudiant,id_prof,id_classe) VALUES (:con,:id1,:id2,:id3)");
    requete.bindValue(":con",);
}

std::vector<Annonce> Etudiant::getAnnonces() {

}
