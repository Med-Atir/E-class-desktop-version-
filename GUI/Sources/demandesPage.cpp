//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#include "../Includes/demandesPage.h"
#include "../UI/ui_demandesPage.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
DemandesPage::DemandesPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::DemandesPage) {
    ui->setupUi(this);
}

DemandesPage::~DemandesPage() {
    delete ui;
}

void DemandesPage::afficherDemandes(User *currentUser) {
     if (!currentUser) return;
    this->user = currentUser;
    ui->msgVide->setVisible(false);
    ui->tabDemandes->setVisible(true);
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        std::vector<Demande> mesDemandes = professeur->getDemandes();
        if (mesDemandes.size() > 0) {
            ui->tabDemandes->clearContents();
            ui->tabDemandes->setRowCount(mesDemandes.size());
            ui->tabDemandes->setColumnCount(5);
            ui->tabDemandes->setHorizontalHeaderLabels({"Email d'etudiant", "Nom d'etudiant", "Classe", "Date demande","Actions"});
            ui->tabDemandes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesDemandes.size(); ++i) {
                int id = mesDemandes[i].getId();
                QString email = QString::fromStdString(mesDemandes[i].getEtudiant()->getEmail());
                QString nom = QString::fromStdString(mesDemandes[i].getEtudiant()->getNom());
                QString classe = QString::fromStdString(mesDemandes[i].getClasse()->getTitre());
                QString dateStr = mesDemandes[i].getDate().toString("dd/MM/yyyy a HH:mm");
                ui->tabDemandes->setItem(i, 0, new QTableWidgetItem(email));
                ui->tabDemandes->setItem(i, 1, new QTableWidgetItem(nom));
                ui->tabDemandes->setItem(i, 2, new QTableWidgetItem(classe));
                ui->tabDemandes->setItem(i, 3, new QTableWidgetItem(dateStr));
                QWidget* pWidget = new QWidget();
                QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
                pLayout->setContentsMargins(2, 2, 2, 2);
                pLayout->setSpacing(5);
                QPushButton* accepterDemande = new QPushButton("Accepter");
                accepterDemande->setStyleSheet("background-color:green;"
                                               "color: white; "
                                               "font-weight: bold; "
                                               "border-radius: 4px; "
                                               "padding: 5px;");
                QPushButton* refuserDemande = new QPushButton("Refuser");
                refuserDemande->setStyleSheet("background-color: red;"
                                              " color: white; "
                                              "font-weight: bold; "
                                              "border-radius: 4px;"
                                              " padding: 5px;");
                pLayout->addWidget(accepterDemande);
                pLayout->addWidget(refuserDemande);
                connect(refuserDemande,&QPushButton::clicked,[this, id,professeur]() {
                    QMessageBox::StandardButton reponse = QMessageBox::question(this,"Comfirmation","Vous etes sur de rejeter la demande?",QMessageBox::Yes|QMessageBox::No);
                    if (reponse == QMessageBox::Yes) {
                        QDateTime d;
                        Demande demande(id,"",d,1,1);
                        bool done = professeur->RejetDemande(demande);
                        if (done) {
                            QMessageBox::information(this,"Succes","Demade a ete rejeter");
                            afficherDemandes(this->user);
                        }
                        else {
                            QMessageBox::warning(this,"Erreur","Demade n'a pas ete rejeter");
                        }
                    }
                });
                connect(accepterDemande,&QPushButton::clicked,[this, id,professeur]() {
                   QMessageBox::StandardButton reponse = QMessageBox::question(this,"Comfirmation","Vous etes sur d'accepter la demande?",QMessageBox::Yes|QMessageBox::No);
                   if (reponse == QMessageBox::Yes) {
                       QDateTime d;
                       Demande demande(id,"",d,1,1);
                       bool done = professeur->AccepteDemande(demande);
                       if (done) {
                           QMessageBox::information(this,"Succes","Demade a ete accepter");
                           afficherDemandes(this->user);
                       }
                       else {
                           QMessageBox::warning(this,"Erreur","Demade n'a pas ete accepter");
                       }
                   }
               });
                ui->tabDemandes->setCellWidget(i, 4, pWidget);
            }
        } else {
            ui->tabDemandes->setVisible(false);
            ui->msgVide->setText("Vous n'avez pas de demandes pour le moment");
            ui->msgVide->setVisible(true);
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        std::vector<Demande> mesDemandes = etudiant->getMesDemandes();
        if (mesDemandes.size() > 0) {
            ui->tabDemandes->clearContents();
            ui->tabDemandes->setRowCount(mesDemandes.size());
            ui->tabDemandes->setColumnCount(4);
            ui->tabDemandes->setHorizontalHeaderLabels({"Titre du classe", "Prof", "Date demande","Action"});
            ui->tabDemandes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesDemandes.size(); ++i) {
                int id = mesDemandes[i].getId();
                QString titre = QString::fromStdString(mesDemandes[i].getClasse()->getTitre());
                QString prof = QString::fromStdString(mesDemandes[i].getClasse()->getNomProf());
                QString dateStr = mesDemandes[i].getDate().toString("dd/MM/yyyy a HH:mm");
                ui->tabDemandes->setItem(i, 0, new QTableWidgetItem(titre));
                ui->tabDemandes->setItem(i, 1, new QTableWidgetItem(prof));
                ui->tabDemandes->setItem(i, 2, new QTableWidgetItem(dateStr));
                QPushButton* annulerDemande = new QPushButton("Annuler");
                annulerDemande->setStyleSheet("background-color: red;"
                                              " color: white; "
                                              "font-weight: bold; "
                                              "border-radius: 4px;"
                                              " padding: 5px;");
                ui->tabDemandes->setCellWidget(i, 3, annulerDemande);
                connect(annulerDemande,&QPushButton::clicked,[this, id,etudiant]() {
                    QMessageBox::StandardButton reponse = QMessageBox::question(this,"Comfirmation","Vous etes sur d'annuler la demande?",QMessageBox::Yes|QMessageBox::No);
                    if (reponse == QMessageBox::Yes) {
                        bool done = etudiant->AnnulerDemande(id);
                        if (done) {
                            QMessageBox::information(this,"Succes","Demade a ete annule");
                            afficherDemandes(this->user);
                        }
                        else {
                            QMessageBox::warning(this,"Erreur","Demade n'a pas ete annule");
                        }
                    }
                });
                //[this,id]
                //elle va capturer l'id de demande courantt des la boucle for et elle va coller lui
                // ici dans le tableau, pourquoi? car le prof ou l'etudiant ne va pas clicker exactement
                //quand for va s'execute (hhhhhh mymknch)
            }
        } else {
            ui->tabDemandes->setVisible(false);
            ui->msgVide->setText("Vous n'avez pas de demandes pour le moment");
            ui->msgVide->setVisible(true);
        }
    }
}