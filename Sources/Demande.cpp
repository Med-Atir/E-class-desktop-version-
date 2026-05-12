//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Demande.h"

Demande::Demande(int id, std::string status, QDateTime date,const Etudiant &etd,const Classe &cl) {
    this->Id = id;
    this->classe = new Classe(cl);
    this->Date = date;
    this->Status = status;
    this->etudiant = new Etudiant(etd);
}

Demande::~Demande() {
    delete this->classe;
    delete this->etudiant;
}

int Demande::getId() {
    return this->Id;
}

void Demande::setId(int id) {
    this->Id = id;
}

Classe *Demande::getClasse() {
    return this->classe;
}

QDateTime Demande::getDate() {
    return this->Date;
}

void Demande::setDate(QDateTime date) {
    this->Date = date;
}

Etudiant *Demande::getEtudiant() {
    return this->etudiant;
}

std::string Demande::getStatus() {
    return this->Status;
}

void Demande::setClasse(const Classe &cl) {
    this->classe = new Classe(cl);
}

void Demande::setEtudiant(const Etudiant &etd) {
    this->etudiant = new Etudiant(etd);
}

void Demande::setStatus(std::string status) {
    this->Status = status;
}