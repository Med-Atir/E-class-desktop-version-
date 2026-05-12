//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "Annonce.h"
#include "../Includes/Professeur.h"

Annonce::Annonce(int id, std::string titre, std::string contenu, QDateTime date,const Professeur &prof,const Classe &cl) {
    this->setId(id);
    this->setTitre(titre);
    this->setContenu(contenu);
    this->setDate(date);
    this->prof = new Professeur(prof);
    this->classe = new Classe(cl);
}
Annonce::~Annonce() {
    delete this->prof;
    delete this->classe;
}

int Annonce::getId() {
    return this->Id;
}

Classe *Annonce::getClasse() {
    return this->classe;
}

std::string Annonce::getContenu() {
    return this->contenu;
}

QDateTime Annonce::getDate() {
    return this->date;
}

Professeur *Annonce::getProf() {
    return this->prof;
}

std::string Annonce::getTitre() {
    return this->titre;
}

void Annonce::setClasse(const Classe &c) {
    this->classe = new Classe(c);
}

void Annonce::setContenu(std::string contenu) {
    this->contenu = contenu;
}

void Annonce::setDate(QDateTime date) {
    this->date = date;
}

void Annonce::setId(int id) {
    this->Id = id;
}

void Annonce::setProf(const Professeur &p) {
    this->prof = new Professeur(p);
}

void Annonce::setTitre(std::string titre) {
    this->titre = titre;
}