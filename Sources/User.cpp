// Created by Atir Mohammed on 18-Apr-26
//CNE: K133125030
//Filiere: IA/4 G:1
#include "../Includes/User.h"
#include "../Database/Db.h"
using namespace std; /* puique nous avons dans le fichier CPP nous pouvons mettre tous utilise
espace de noms std, aucun harm (risque car on inclut seulement le header)
*/
User::User() {//je vais initialiser seulement son cin par 'Nothing' alors je sais qui est qui.
}

User::User(int id,string Nom,string Email) {
    this->setId(id);
    this->setNom(Nom);
    this->setEmail(Email);
}

User::User(const User& p) {
    this->setId(p.getId());
    this->setNom(p.getNom());
    this->setEmail(p.getEmail());
}

User::~User() {// je n'ai pas des pointeurs dans ma classe alors pas d'operations
}

User& User::operator=(const User& p) {
    if (this != &p) {
        this->setNom(p.getNom());
        this->setEmail(p.getEmail());
        this->setId(p.getId());
    }
    return *this;
}

string User::getNom() const {// j'ai defini mes getters ici
    return this->Nom;
}


string User::getEmail() const {
    return this->Email;
} // mainetnant on va definir les setters(muttateurs)

void User::setNom(string name) {
    this->Nom = name;
}

void User::setEmail(string email) {
    this->Email = email;
}

int User::getId() const {
    return this->Id;
}

void User::setId(int id) {
    this->Id = id;
}

bool User::DeleteAcc() {
    return DB::delAccount(this->Id);
}

bool User::changeremail(std::string mail) {
    return DB::changerEmail(this->Id,mail);
}

bool User::changerNom(std::string name) {
    return DB::changerNom(this->Id,name);
}