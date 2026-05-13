//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "Annonce.h"
#include "../Includes/Professeur.h"
#include "../Database/Db.h"

Annonce::Annonce(int id, std::string titre, std::string contenu, QDateTime date,int idprof,int idclasse) {
    this->setId(id);
    this->setTitre(titre);
    this->setContenu(contenu);
    this->setDate(date);
    this->setProf(idprof);
    this->setClasse(idclasse);
}
Annonce::~Annonce() {
}

int Annonce::getId() {
    return this->Id;
}

Classe *Annonce::getClasse() {
    return DB::getClasse(this->idclasse);
}

std::string Annonce::getContenu() {
    return this->contenu;
}

QDateTime Annonce::getDate() {
    return this->date;
}

Professeur *Annonce::getProf() {
    return DB::getProf(this->idprof);
}

std::string Annonce::getTitre() {
    return this->titre;
}

void Annonce::setClasse(int c) {
    this->idclasse = c;
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

void Annonce::setProf(int p) {
    this->idprof = p;
}

void Annonce::setTitre(std::string titre) {
    this->titre = titre;
}

int Annonce::getIdclasse() {
    return this->idclasse;
}

int Annonce::getIdprof() {
    return this->idprof;
}