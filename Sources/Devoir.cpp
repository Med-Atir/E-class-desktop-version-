//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#include "Devoir.h"

Devoir::Devoir(int id, std::string titre, std::string consigne, std::string deadline, std::string cheminFichier, QDateTime date, const Professeur &prof, const Classe &cl): Document(id,titre,cheminFichier,date,prof,cl){
    this->setConsigne(consigne);
    this->setDeadline(deadline);
}

Devoir::Devoir(const Devoir &d):Document(d) {
    this->setConsigne(d.consigne);
    this->setDeadline(d.deadline);
}

Devoir::~Devoir(){
}

std::string Devoir::getConsigne() {
    return this->consigne;
}

void Devoir::setConsigne(std::string consigne) {
    this->consigne = consigne;
}

std::string Devoir::getdeadline() {
    return this->deadline;
}

void Devoir::setDeadline(std::string deadline) {
    this->deadline = deadline;
}