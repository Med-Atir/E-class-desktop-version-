//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Document.h"

Document::Document(int id, std::string titre,std::string cheminFichier, QDateTime date, const Professeur &prof, const Classe &cl) {
    this->setId(id);
    this->setTitre(titre);
    this->setCheminFichier(cheminFichier);
    this->setDate(date);
    this->setProf(prof);
    this->setClasse(cl);
}

Document::Document(const Document &d) {
    this->setId(d.id);
    this->setTitre(d.titre);
    this->setCheminFichier(d.cheminFichier);
    this->setDate(d.date);
    this->setProf(*(d.prof));
    this->setClasse(*(d.classe));
}

void Document::setTitre(std::string titre) {
    this->titre = titre;
}

void Document::setClasse(const Classe &cl) {
    this->classe = new Classe(cl);
}

Professeur *Document::getProf() {
    return this->prof;
}

void Document::setDate(QDateTime date) {
    this->date = date;
}

std::string Document::getTitre() {
    return this->titre;
}

QDateTime Document::getDate() {
    return this->date;
}

Classe *Document::getClasse() {
    return this->classe;
}

void Document::setId(int id) {
    this->id = id;
}

void Document::setProf(const Professeur &pr) {
    this->prof = new Professeur(pr);
}

std::string Document::getCheminFichier() {
    return this->cheminFichier;
}

int Document::getID() {
    return this->id;
}

void Document::setCheminFichier(std::string chemin) {
    this->cheminFichier = chemin;
}

Document::~Document() {
    delete this->classe;
    delete this->prof;
}