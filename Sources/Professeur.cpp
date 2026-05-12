//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/Professeur.h"
#include "../Database/Db.h"
#include <iostream>

Professeur::Professeur(int Id,std::string Nom,std::string Email,std::string Role):User(Id,Nom,Email,Role) {
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

std::vector<Demande> Professeur::getDemandes(Classe &cl) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM demande WHERE id_class = :id");
    requete.bindValue(":id",cl.getId());
    if (requete.exec())
        while (requete.next()) {
            int id = requete.value("id").toInt();
            int idetd = requete.value("id_etudiant").toInt();
            int idcl = requete.value("id_classe").toInt();
            QSqlQuery req1;
            req1.prepare("SELECT * FROM user WHERE id = :id");
            req1.bindValue(":id",idetd);
            if (req1.exec()) {
                while (req1.next()) {

                }
            }
            QSqlQuery req2;
            req2.prepare("SELECT * FROM classe WHERE id = :id");
            req2.bindValue(":id",idcl);
           QString status = requete.value("status").toString();
            QDateTime date = requete.value("date").toDateTime();
        }
}
