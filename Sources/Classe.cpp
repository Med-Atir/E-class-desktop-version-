//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Classe.h"

Classe::Classe(int id, std::string titre, std::string code, std::string description) {
    this->setId(id);
    this->setTitre(titre);
    this->setCode(code);
    this->setDescription(description);
}

Classe::Classe(const Classe &cl) {
    this->setId(cl.Id);
    this->setTitre(cl.Titre);
    this->setCode(cl.Code);
    this->setDescription(cl.Description);
}

Classe::~Classe() {
}

int Classe::getId() {
    return this->Id;
}

std::string Classe::getTitre() {
    return this->Titre;
}

std::string Classe::getCode() {
    return this->Code;
}

std::string Classe::getDescription() {
    return this->Description;
}

void Classe::setCode(std::string Code) {
    this->Code = Code;
}

void Classe::setId(int id) {
    this->Id = id;
}

void Classe::setDescription(std::string Description) {
    this->Description = Description;
}

void Classe::setTitre(std::string Titre) {
    this->Titre = Titre;
}