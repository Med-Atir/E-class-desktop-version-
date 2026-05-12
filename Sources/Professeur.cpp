//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Headers/Professeur.h"
#include "../Database/Db.h"
#include <iostream>

Professeur::Professeur(int Id,std::string Nom,std::string Email):User(Id,Nom,Email) {
}

Professeur::~Professeur() {

}

std::string Professeur::AddClasse(Classe& cl) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO classe (titre,code,description,prof_id) VALUES (:titre,:code,:description,:id)");
    requete.bindValue(":titre",QString::fromStdString(cl.getTitre()));
    requete.bindValue(":code",QString::fromStdString(cl.getCode()));
    requete.bindValue(":description",QString::fromStdString(cl.getDescription()));
    requete.bindValue(":id",this->getId());
    if (requete.exec()) {
        return cl.getCode();
    }
    else {
       return "erreur";
    }
}

bool Professeur::DelClasse(Classe &cl) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM classe WHERE id = :id");
    requete.bindValue(":id",cl.getId());
    if (requete.exec())
        return true;
    else{
        qDebug() << "Echec de la suppression :" << requete.lastError().text();
        return false;
    }
}

Vect<Demande> Professeur::getDemandes(Classe &cl) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM demande WHERE id_class = :id");
    requete.bindValue(":id",cl.getId());
    if (requete.exec())
        while (requete.next()) {
            int
        }
}
