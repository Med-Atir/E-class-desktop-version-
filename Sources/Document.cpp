//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Document.h"
#include "../Database/Db.h"

Document::Document(int id, std::string titre,std::string cheminFichier, QDateTime date,int idprof,int idclass) {
    this->setId(id);
    this->setTitre(titre);
    this->setCheminFichier(cheminFichier);
    this->setDate(date);
    this->setIdProf(idprof);
    this->setIdClasse(idclass);
}

Document::Document(const Document &d) {
    this->setId(d.id);
    this->setTitre(d.titre);
    this->setCheminFichier(d.cheminFichier);
    this->setDate(d.date);
    this->setIdProf(d.idprof);
    this->setIdClasse(d.idclasse);
}

int Document::getIdclasse() {
    return this->idclasse;
}

int Document::getIdprof() {
    return this->idprof;
}

void Document::setTitre(std::string titre) {
    this->titre = titre;
}

void Document::setIdClasse(int cl) {
    this->idclasse = cl;
}

Professeur *Document::getProf() {
    DB::getProf(this->idprof);
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
    DB::getClasse(this->idclasse);
}

void Document::setId(int id) {
    this->id = id;
}

void Document::setIdProf(int id) {
    this->idprof = id;
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
}