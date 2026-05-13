//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Demande.h"
#include "../Database/Db.h"

Demande::Demande(int id, std::string status, QDateTime date,int idetd,int idclass) {
    this->Id = id;
    this->idclasse = idclass;
    this->Date = date;
    this->Status = status;
    this->idetd = idetd;
}

Demande::~Demande() {
}

int Demande::getId() {
    return this->Id;
}

void Demande::setId(int id) {
    this->Id = id;
}

int Demande::getIdClasse() {
    return this->idclasse;
}

QDateTime Demande::getDate() {
    return this->Date;
}

void Demande::setDate(QDateTime date) {
    this->Date = date;
}

int Demande::getIdEtd(){
    return this->idetd;
}

std::string Demande::getStatus() {
    return this->Status;
}

void Demande::setIdClasse(int id) {
    this->idclasse = id;
}
void Demande::setIdEtudiant(int etd) {
    this->idetd = etd;
}

void Demande::setStatus(std::string status) {
    this->Status = status;
}

Classe *Demande::getClasse() {
    return DB::getClasse(this->idclasse);
}

Etudiant *Demande::getEtudiant() {
    return DB::getEtudiant(this->idetd);
}