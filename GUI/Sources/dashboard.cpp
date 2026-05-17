//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/dashboard.h"
#include "../../Includes/Etudiant.h"
#include "../UI/ui_Dashboard.h"
#include "../Includes/loginwindow.h"
#include "../../Includes/Professeur.h"

Dashboard::Dashboard(User* user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard){
    ui->setupUi(this);
    this->setUser(user);
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->centralwidget->layout()->setSpacing(0);
    ui->contenu->setCurrentIndex(0);
    this->setMenuBar(nullptr);
    this->setStatusBar(nullptr);
    ui->sidebar->setMaximumHeight(16777215);
    ui->sidebar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    while(ui->contenu->count() > 0) {
        ui->contenu->removeWidget(ui->contenu->widget(0));
    }
    classesPage = new ClassesPage(this);
    homePage = new Home(this);
    demandesPage = new DemandesPage(this);
    devoirsPage  = new DevoirsPage(this);
    questionsPage = new QuestionsPage(this);
    annoncesPage = new AnnoncesPage(this);
    parametresPage = new Parametres(this);
    connect(parametresPage,&Parametres::demandeDeconnection,this,&Dashboard::on_btnDeconnecter_clicked);
    ui->contenu->addWidget(homePage);
    ui->contenu->addWidget(classesPage);
    ui->contenu->addWidget(demandesPage);
    ui->contenu->addWidget(devoirsPage);
    ui->contenu->addWidget(questionsPage);
    ui->contenu->addWidget(annoncesPage);
    ui->contenu->addWidget(parametresPage);
    ui->contenu->setCurrentWidget(homePage);
    homePage->afficherStats(this->user);
}

Dashboard::~Dashboard(){
    delete ui;
    delete this->user;
}

void Dashboard::setUser(User *user) {
    this->user = user;
    this->setUpUI();
}

void Dashboard::on_btnDeconnecter_clicked(){
    LoginWindow *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->showMaximized();
    this->close();
}

void Dashboard::setUpUI() {
    if (Professeur* prof = dynamic_cast<Professeur *>(user)) {

    }
    else if (Etudiant* etd = dynamic_cast<Etudiant *>(user)) {

    }
}

void Dashboard::on_home_clicked() {
    ui->contenu->setCurrentWidget(homePage);
    homePage->afficherStats(this->user);
}
void Dashboard::on_mesclasses_clicked() {
    ui->contenu->setCurrentWidget(classesPage);
    classesPage->AfficherClasses(this->user);
}
void Dashboard::on_mesannonces_clicked(){
    ui->contenu->setCurrentWidget(annoncesPage);
    annoncesPage->afficherAnnonces(this->user);
}
void Dashboard::on_mesdevoirs_clicked() {
    ui->contenu->setCurrentWidget(devoirsPage);
    devoirsPage->afficherFiles(this->user);
}
void Dashboard::on_mesquestions_clicked() {
    ui->contenu->setCurrentWidget(questionsPage);
    questionsPage->afficherQuestion(this->user);
}
void Dashboard::on_mesdemandes_clicked() {
    ui->contenu->setCurrentWidget(demandesPage);
    demandesPage->afficherDemandes(this->user);
}
void Dashboard::on_parametre_clicked() {
    ui->contenu->setCurrentWidget(parametresPage);
    parametresPage->setUser(this->user);
}