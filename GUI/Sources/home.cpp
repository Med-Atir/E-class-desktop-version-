//Created by Mohammed atir
//IA S4 / Groupe 1
#include "../Includes/home.h"
#include "../UI/ui_home.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include <QString>

Home::Home(QWidget *parent, User* user) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);
}

Home::~Home() {
    delete ui;
}

void Home::afficherStats(User* currentUser) {
    if (!currentUser) return;
    this->user = currentUser;
    QString nameuti = QString::fromStdString(user->getNom());
    ui->labelBienvenue->setText("Bienvenue sur E-Class, " + nameuti + " !");
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        ui->proftab->setVisible(true);
        ui->etdtab->setVisible(false);
        int totalClasses = professeur->getMesClasses().size();
        int totalDocs = professeur->getDocuments().size() + professeur->getDevoirs().size();
        int totalQuestions = professeur->getQuestions().size();
        ui->nbClassesProf->setText("Nombre totale des classes: " + QString::number(totalClasses));
        ui->nbDocsProf->setText("Nombre totale des docs: " + QString::number(totalDocs));
        ui->nbQuestionsProf->setText("Nombre totale des questions: " + QString::number(totalQuestions));
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        ui->proftab->setVisible(false);
        ui->etdtab->setVisible(true);
        int totalCoursInscrits = etudiant->getCoursInscri().size();
        int totalDevoirs = etudiant->getDevoirs().size();
        ui->nbClassesEtd->setText("Nombre totale des classes: " + QString::number(totalCoursInscrits));
        ui->nbDevoirsEtd->setText("Nombre totale des devoirs: " + QString::number(totalDevoirs));
    }
}