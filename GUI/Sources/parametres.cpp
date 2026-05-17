//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/parametres.h"
#include "../UI/ui_parametres.h"
#include "../Includes/loginwindow.h"
#include "../../Includes/User.h"
#include <QMessageBox>


Parametres::Parametres(QWidget *parent) : QWidget(parent), ui(new Ui::Parametres) {
    ui->setupUi(this);
    ui->email->setPlaceholderText("Veuillez entre le nouveau email ici....");
    ui->nom->setPlaceholderText("Veuillez entre le nouveau nom ici....");
}

Parametres::~Parametres() {
    delete ui;
}
void Parametres::setUser(User* user) {
    this->user = user;
}
void Parametres::on_supprimercompte_clicked() {
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this,"Comfirmation","Vous voulez vraiment supprimer votre compte? tous sera perdu!!",QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes) {
        QMessageBox::StandardButton reponse2;
        reponse2 = QMessageBox::question(this,"Double comfirmation","Vous avez vraiment sur?",QMessageBox::Yes|QMessageBox::No);
        if (reponse2 == QMessageBox::Yes) {
            QMessageBox::StandardButton reponse3;
            reponse3 = QMessageBox::question(this,"Triple comfirmation","Vous avez changez votre avis?",QMessageBox::Yes|QMessageBox::No);
            if (reponse3 == QMessageBox::No){
                if (this->user->DeleteAcc()) {
                    emit demandeDeconnection();
                }
                else {
                    QMessageBox::warning(this,"Echec","Un probleme s'est produit");
                    return;
                }
            }
        }
    }
    return;
}
void Parametres::on_changernom_clicked() {
    QString name = ui->nom->text();
    if (name.isEmpty()){
        QMessageBox::warning(this,"Echec","Vous devez remplir le champs");
    return;
}
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this,"Comfirmation","Vous voulez vraiment changer votre nom?",QMessageBox::Yes|QMessageBox::No);
    if (reponse) {
        bool estchanger = this->user->changerNom(name.toStdString());
        if (estchanger){
           emit demandeDeconnection();
        }
        else {
            QMessageBox::warning(this,"Echec","Un probleme s'est produit");
            return;
        }
    }
    return;
}
void Parametres::on_changeremail_clicked() {
    QString mail = ui->email->text();
    if (mail.isEmpty()){
        QMessageBox::warning(this,"Echec","Vous devez remplir le champs");
        return;
    }
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this,"Comfirmation","Vous voulez vraiment changer votre email?",QMessageBox::Yes|QMessageBox::No);
    if (reponse) {
        bool estchanger = this->user->changeremail(mail.toStdString());
        if (estchanger){
           emit demandeDeconnection();
        }
        else {
            QMessageBox::warning(this,"Echec","Un probleme s'est produit");
            return;
        }
    }
    return;
}