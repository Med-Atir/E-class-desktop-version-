//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "Question.h"
#include <QDateTime>
#include "Professeur.h"
#include "../Database/Db.h"

Question::Question(int id, std::string cont, QDateTime dateQ, int idEtd,int idPr,int idCl, bool estR,QDateTime* dateR, std::string *Reponse) {
    this->setId(id);
    this->setContenu(cont);
    this->setDateQ(dateQ);
    this->setEtd(idEtd);
    this->setProf(idPr);
    this->setClasse(idCl);
    this->setEtat(estR);
    this->dateReponse = nullptr;
    this->Reponse = nullptr;
    if (estR) {
        if (dateR != nullptr)
        this->setDateR(*dateR);
        if (Reponse != nullptr)
        this->setReponse(Reponse);
    }
    else {
        this->dateReponse = nullptr;
        this->Reponse = nullptr;
    }
}
Question::Question(const Question &q) {
    this->setId(q.id);
    this->setContenu(q.contenu);
    this->setDateQ(q.dateQuestion);
    this->setEtd(q.idEtd);
    this->setProf(q.idProf);
    this->setClasse(q.idClasse);
    this->setEtat(q.estRepondu);
    this->dateReponse = nullptr;
    this->Reponse = nullptr;
    if (q.estRepondu) {
        if (q.dateReponse != nullptr)
            this->setDateR(*q.dateReponse);
        if (q.Reponse!= nullptr)
            this->setReponse(q.Reponse);
    }
    else {
        this->dateReponse = nullptr;
        this->Reponse = nullptr;
    }
}

int Question::getId() {
    return this->id;
}

std::string Question::getContenu() {
    return this->contenu;
}

QDateTime Question::getDateQ() {
    return this->dateQuestion;
}

QDateTime *Question::getDateR() {
    return this->dateReponse;
}

bool Question::getEtat() {
    return this->estRepondu;
}

Classe *Question::getClasse() {
   return DB::getClasse(this->idClasse);
}

Etudiant *Question::getEtd() {
   return DB::getEtudiant(this->idEtd);
}

Professeur *Question::getProf() {
    return DB::getProf(this->idProf);
}

std::string* Question::getReponse() {
    return this->Reponse;
}

Question::~Question() {
    delete this->Reponse;
    delete this->dateReponse;
}

void Question::setClasse(int idcl) {
   this->idClasse = idcl;
}

void Question::setContenu(std::string cont) {
    this->contenu = cont;
}

void Question::setDateQ(QDateTime dateq) {
    this->dateQuestion = dateq;
}

void Question::setDateR(const QDateTime &dater) {
    if (this->dateReponse != nullptr) {
        delete this->dateReponse;
    }
    this->dateReponse = new QDateTime(dater);
}

void Question::setEtat(bool etat) {
    this->estRepondu = etat;
}

void Question::setEtd(int idetd) {
   this->idEtd = idetd;
}

void Question::setId(int id) {
    this->id = id;
}

void Question::setProf(int idpr) {
    this->idProf = idpr;
}

void Question::setReponse(std::string *reponse) {
    if (reponse != nullptr) {
        if (this->Reponse != nullptr) {
            delete this->Reponse;
        }
        this->Reponse = new std::string(*reponse);
    } else {
        if (this->Reponse != nullptr) {
            delete this->Reponse;
            this->Reponse = nullptr;
        }
    }
}

int Question::getIdClasse() {
    return this->idClasse;
}

int Question::getIdEtd() {
    return this->idEtd;
}

int Question::getIdProf() {
    return this->idProf;
}