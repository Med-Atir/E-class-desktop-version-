//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1

#include "../Includes/annoncesPage.h"
#include "../../Includes/Etudiant.h"
#include "../../Database/Db.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/User.h"
#include "../UI/ui_annoncesPage.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QDateTime>

AnnoncesPage::AnnoncesPage(QWidget *parent, User* user) : QWidget(parent), ui(new Ui::AnnoncesPage), user(user) {
    ui->setupUi(this);
    ui->msgVide->setVisible(false);
    ui->titreAnnonce->setPlaceholderText("Veuillez entrer le titre de l'annonce ici.......");
    ui->contenuAnnonce->setPlaceholderText("Veuillez entrer le contenu de l'annonce ici.......");
    ui->classeChoix->setPlaceholderText("Choisir la classe");
    ui->delAnnonce->setPlaceholderText("Choisir l'annonce");
}

AnnoncesPage::~AnnoncesPage() {
    delete ui;
}

void AnnoncesPage::afficherAnnonces(User* currentUser) {
    if (!currentUser) return;
    this->user = currentUser;
    ui->msgVide->setVisible(false);
    ui->tableAnnonces->setVisible(true);
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        std::vector<Annonce> mesAnnonces = professeur->getAnnonces();
        std::vector<Classe> mesClasses = professeur->getMesClasses();
        ui->titreAnnonce->setVisible(true);
        ui->contenuAnnonce->setVisible(true);
        ui->posterAnnonce->setVisible(true);
        ui->addAnnonce->setVisible(true);
        ui->classeChoix->setVisible(true);
        ui->delAnnonce->setVisible(true);
        ui->supprimerAnnonce->setVisible(true);
        ui->supprimerAnnoncelbl->setVisible(true);
        ui->delAnnonce->clear();
        ui->classeChoix->clear();
        if (mesAnnonces.size() > 0) {
            ui->tableAnnonces->clearContents();
            ui->tableAnnonces->setRowCount(mesAnnonces.size());
            ui->tableAnnonces->setColumnCount(4);
            ui->tableAnnonces->setHorizontalHeaderLabels({"Titre de l'annonce", "Contenu", "Date de publication", "Classe"});
            ui->tableAnnonces->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesAnnonces.size(); ++i) {
                int id = mesAnnonces[i].getId();
                QString titre = QString::fromStdString(mesAnnonces[i].getTitre());
                QString contenu = QString::fromStdString(mesAnnonces[i].getContenu());
                QString classe = QString::fromStdString(mesAnnonces[i].getClasse()->getTitre());
                QString dateStr = mesAnnonces[i].getDate().toString("dd/MM/yyyy a HH:mm");
                ui->delAnnonce->addItem(titre, id);
                ui->tableAnnonces->setItem(i, 0, new QTableWidgetItem(titre));
                ui->tableAnnonces->setItem(i, 1, new QTableWidgetItem(contenu));
                ui->tableAnnonces->setItem(i, 2, new QTableWidgetItem(dateStr));
                ui->tableAnnonces->setItem(i, 3, new QTableWidgetItem(classe));
            }
        } else {
            ui->tableAnnonces->setVisible(false);
            ui->msgVide->setVisible(true);
        }
        for (Classe c : mesClasses) {
            ui->classeChoix->addItem(QString::fromStdString(c.getTitre()), c.getId());
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        std::vector<Annonce> mesAnnonces = etudiant->getAnnonces();
        ui->titreAnnonce->setVisible(false);
        ui->contenuAnnonce->setVisible(false);
        ui->posterAnnonce->setVisible(false);
        ui->addAnnonce->setVisible(false);
        ui->classeChoix->setVisible(false);
        ui->delAnnonce->setVisible(false);
        ui->supprimerAnnonce->setVisible(false);
        ui->supprimerAnnoncelbl->setVisible(false);
        if (mesAnnonces.size() > 0) {
            ui->tableAnnonces->clearContents();
            ui->tableAnnonces->setRowCount(mesAnnonces.size());
            ui->tableAnnonces->setColumnCount(5);
            ui->tableAnnonces->setHorizontalHeaderLabels({"Titre de l'annonce", "Contenu", "Date de publication", "Professeur", "Classe"});
            ui->tableAnnonces->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesAnnonces.size(); ++i) {
                QString titre = QString::fromStdString(mesAnnonces[i].getTitre());
                QString contenu = QString::fromStdString(mesAnnonces[i].getContenu());
                QString dateStr = mesAnnonces[i].getDate().toString("dd/MM/yyyy a HH:mm");
                QString prof = QString::fromStdString(mesAnnonces[i].getProf()->getNom());
                QString classe = QString::fromStdString(mesAnnonces[i].getClasse()->getTitre());
                ui->tableAnnonces->setItem(i, 0, new QTableWidgetItem(titre));
                ui->tableAnnonces->setItem(i, 1, new QTableWidgetItem(contenu));
                ui->tableAnnonces->setItem(i, 2, new QTableWidgetItem(dateStr));
                ui->tableAnnonces->setItem(i, 3, new QTableWidgetItem(prof));
                ui->tableAnnonces->setItem(i, 4, new QTableWidgetItem(classe));
            }
        } else {
            ui->tableAnnonces->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
}

void AnnoncesPage::on_posterAnnonce_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        QString titre = ui->titreAnnonce->text();
        QString contenu = ui->contenuAnnonce->toPlainText();

        if(titre.trimmed().isEmpty() || contenu.trimmed().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir le titre et le contenu.");
            return;
        }
        int idclasse = ui->classeChoix->currentData().toInt();
        QDateTime dateposte = QDateTime::currentDateTime();
        Annonce annonce(1, titre.toStdString(), contenu.toStdString(), dateposte, professeur->getId(), idclasse);
        bool estInserer = professeur->AddAnnoce(annonce);

        if (estInserer) {
            QMessageBox::information(this, "Succs", "Annonce ajouter avec succes");
            ui->titreAnnonce->clear();
            ui->contenuAnnonce->clear();
            afficherAnnonces(user);
        } else {
            QMessageBox::warning(this, "Erreur", "L'annonce n'a ajoute pas, veuillez reessager");
        }
    }
}

void AnnoncesPage::on_supprimerAnnonce_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        int idAnnonce = ui->delAnnonce->currentData().toInt();

        if (idAnnonce == 0) {
            QMessageBox::warning(this, "Erreur", "Veuillez selectionner une annonce a supprimer.");
            return;
        }
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "vous voulez vraiment supprimer cette annonce ?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QDateTime date = QDateTime::currentDateTime();
            Annonce annonce(idAnnonce, "dont matter", "aussi", date, professeur->getId(), idAnnonce);

            bool estSupprimer = professeur->DelAnnonce(annonce);

            if (estSupprimer) {
                QMessageBox::information(this, "Succes", "Annonce supprime avec succes");
                afficherAnnonces(user);
            } else {
                QMessageBox::warning(this, "Erreur", "Impossible de supprimer l'annonce.");
            }
        }
    }
}