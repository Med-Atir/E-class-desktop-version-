//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/classesPage.h"
#include <QMessageBox>
#include <QDateTime>
#include "../UI/ui_classesPage.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include "../../Database/Db.h"

ClassesPage::ClassesPage(QWidget *parent, User* user) : QWidget(parent), ui(new Ui::ClassesPage), user(user) {
    ui->setupUi(this);
    ui->msgVide->setVisible(false);
    ui->rechercheVide->setVisible(false);
    ui->codeClasse->setPlaceholderText("Veuillez entrer le code de la classe...");
    ui->description->setPlaceholderText("Veuillez entrer la description...");
    ui->delClasse->setPlaceholderText("Choisir la classe ici");
    ui->titreClasse->setPlaceholderText("Veuillez entrer le titre...");
}

ClassesPage::~ClassesPage() {
    delete ui;
}

void ClassesPage::AfficherClasses(User* currentUser) {
    if (!currentUser) return;
    this->user = currentUser;
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        std::vector<Classe> mesClasses  = professeur->getMesClasses();
        ui->rechercherClasse->setVisible(false);
        ui->codeClasse->setVisible(false);
        ui->rechercher->setVisible(false);
        ui->resultatRecherche->setVisible(false);
        ui->demandeAcces->setVisible(false);
        ui->rechercheVide->setVisible(false);
        ui->titreClasse->setVisible(true);
        ui->supprimer->setVisible(true);
        ui->delClasse->setVisible(true);
        ui->description->setVisible(true);
        ui->ajouter->setVisible(true);
        ui->ajouterClasse->setVisible(true);
        ui->supprimerClasse->setVisible(true);
        ui->mesClasseA->setVisible(true);

        ui->delClasse->clear();

        if (mesClasses.size() > 0) {
            ui->mesClasseA->clearContents();
            ui->mesClasseA->setRowCount(mesClasses.size());
            ui->mesClasseA->setColumnCount(3);
            ui->mesClasseA->setHorizontalHeaderLabels({"Titre de la classe","Code", "Description"});
            ui->mesClasseA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            for (size_t i = 0; i < mesClasses.size(); ++i) {
                int id = mesClasses[i].getId();
                QString titre = QString::fromStdString(mesClasses[i].getTitre());
                QString code = QString::fromStdString(mesClasses[i].getCode());
                QString description = QString::fromStdString(mesClasses[i].getDescription());
                ui->delClasse->addItem(titre, id);
                ui->mesClasseA->setItem(i, 0, new QTableWidgetItem(titre));
                ui->mesClasseA->setItem(i, 1, new QTableWidgetItem(code));
                ui->mesClasseA->setItem(i, 2, new QTableWidgetItem(description));
            }
        } else {
            ui->mesClasseA->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        std::vector<Classe> mesClasses = etudiant->getCoursInscri();
        ui->rechercherClasse->setVisible(true);
        ui->codeClasse->setVisible(true);
        ui->rechercher->setVisible(true);
        ui->resultatRecherche->setVisible(true);
        ui->demandeAcces->setVisible(false);

        ui->titreClasse->setVisible(false);
        ui->supprimer->setVisible(false);
        ui->delClasse->setVisible(false);
        ui->description->setVisible(false);
        ui->ajouter->setVisible(false);
        ui->ajouterClasse->setVisible(false);
        ui->supprimerClasse->setVisible(false);
        ui->mesClasseA->setVisible(true);

        if (mesClasses.size() > 0) {
            ui->mesClasseA->clearContents();
            ui->mesClasseA->setRowCount(mesClasses.size());
            ui->mesClasseA->setColumnCount(2);
            ui->mesClasseA->setHorizontalHeaderLabels({"Titre de la classe", "Description"});
            ui->mesClasseA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            for (size_t i = 0; i < mesClasses.size(); ++i) {
                QString titre = QString::fromStdString(mesClasses[i].getTitre());
                QString description = QString::fromStdString(mesClasses[i].getDescription());
                ui->mesClasseA->setItem(i, 0, new QTableWidgetItem(titre));
                ui->mesClasseA->setItem(i, 1, new QTableWidgetItem(description));
            }
        } else {
            ui->mesClasseA->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
}

void ClassesPage::RechercherClasse(std::string code) {
    if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        Classe* classe = etudiant->RechercherClasse(code);

        if (classe) {
            ui->resultatRecherche->clearContents();
            ui->resultatRecherche->setRowCount(1);
            ui->resultatRecherche->setColumnCount(2);
            ui->resultatRecherche->setHorizontalHeaderLabels({"Titre de la classe", "Description"});
            ui->resultatRecherche->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            this->idClasseRecherchee = classe->getId();

            QString titre = QString::fromStdString(classe->getTitre());
            QString description = QString::fromStdString(classe->getDescription());
            ui->resultatRecherche->setItem(0, 0, new QTableWidgetItem(titre));
            ui->resultatRecherche->setItem(0, 1, new QTableWidgetItem(description));

            ui->resultatRecherche->setVisible(true);

            if (etudiant->estInscri(this->idClasseRecherchee)) {
                ui->demandeAcces->setVisible(false);
                ui->rechercheVide->setText("Vous etes deja inscrit a cette classe.");
                ui->rechercheVide->setVisible(true);
            }
            else if (etudiant->DemandeDejaAtt(this->idClasseRecherchee)) {
                ui->demandeAcces->setVisible(false);
                ui->rechercheVide->setText("Demande d'acces deja en attente.");
                ui->rechercheVide->setVisible(true);
            }
            else {
                ui->demandeAcces->setVisible(true);
                ui->rechercheVide->setVisible(false);
            }
            delete classe;
        } else {
            ui->resultatRecherche->setVisible(false);
            ui->demandeAcces->setVisible(false);
            ui->rechercheVide->setText("Aucune classe trouvee.");
            ui->rechercheVide->setVisible(true);
        }
    }
}

void ClassesPage::on_rechercher_clicked() {
    QString code = ui->codeClasse->text();
    if (code.isEmpty()) {
        QMessageBox::warning(this, "Echec", "Veuillez entrer un code");
    } else {
        RechercherClasse(code.toStdString());
    }
}

void ClassesPage::on_demandeAcces_clicked() {
    if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        if (this->idClasseRecherchee == -1) return;
        Classe classeDemande(this->idClasseRecherchee, 0, "", "", "");
        bool demandebon = etudiant->InscrireClasse(classeDemande);
        if (demandebon) {
            QMessageBox::information(this, "Succes", "Demande envoyee avec succes");
            ui->demandeAcces->setVisible(false);
            ui->codeClasse->clear();
        } else {
            QMessageBox::warning(this, "Echec", "Un erreur s'est produite(ou deja demande en attente)");
        }
    }
}

void ClassesPage::on_ajouter_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        QString titre = ui->titreClasse->text();
        QString description = ui->description->toPlainText();

        if(titre.trimmed().isEmpty() || description.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
            return;
        }
        qint64 numcode = QDateTime::currentDateTime().toMSecsSinceEpoch();
        QString code = QString::number(numcode).right(6);
        Classe nouvelleClasse(1, professeur->getId(), titre.toStdString(), code.toStdString(), description.toStdString());

        bool estcreer = professeur->AddClasse(nouvelleClasse);

        if (estcreer) {
            QMessageBox::information(this, "Succcs", "Classe ajoutee ! \nLe code pour vos etudiants est : " + code);
            ui->titreClasse->clear();
            ui->description->clear();

            AfficherClasses(this->user);
        } else {
            QMessageBox::warning(this, "Echec", "La classe n'a pas ete ajoutee");
        }
    }
}

void ClassesPage::on_supprimer_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        int idClasse = ui->delClasse->currentData().toInt();

        if (idClasse == 0) {
            QMessageBox::warning(this, "Erreur", "Veuillez selectionner une classe a supprimer.");
            return;
        }
        QMessageBox::StandardButton reponse;
        reponse = QMessageBox::question(this, "Confirmation", "Vous etes sur de supprimer cette classe et toutes ses donnees ?", QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes) {
            int idprof = professeur->getId();
            Classe classe(idClasse,idprof,"","","");
            bool estSupprime = professeur->DelClasse(classe);
            if (estSupprime) {
                QMessageBox::information(this, "Succes", "La classe a ete supprimee.");
                AfficherClasses(this->user);
            } else {
                QMessageBox::warning(this, "Erreur", "Impossible de supprimer la classe.");
            }
        }
    }
}