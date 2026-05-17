//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/questionsPage.h"
#include "../UI/ui_questionsPage.h"
#include "../../Includes/Professeur.h"
#include "../../Database/DB.h"
#include "../../Includes/Etudiant.h"
#include "../../Includes/Question.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
#include <QBoxLayout>

QuestionsPage::QuestionsPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::QuestionsPage) {
    ui->setupUi(this);
}

QuestionsPage::~QuestionsPage() {
    delete ui;
}
void QuestionsPage::afficherQuestion(User* currentUser) {
     if (!currentUser) return;
    this->user = currentUser;
    ui->msgVide->setVisible(false);
    ui->tabQuestions->setVisible(true);
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        ui->question->setVisible(false);
        ui->classe->setVisible(false);
        ui->poser->setVisible(false);
        ui->label_2->setVisible(false);
        std::vector<Question> mesQuestion = professeur->getQuestions();
        if (mesQuestion.size() > 0) {
            ui->tabQuestions->clearContents();
            ui->tabQuestions->setRowCount(mesQuestion.size());
            ui->tabQuestions->setColumnCount(5);
            ui->tabQuestions->setHorizontalHeaderLabels({"Nom d'etudiant", "Question", "Classe", "Date Question","Action"});
            ui->tabQuestions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesQuestion.size(); ++i) {
                int id = mesQuestion[i].getId();
                QString nom = QString::fromStdString(mesQuestion[i].getEtd()->getNom());
                QString questionposer = QString::fromStdString(mesQuestion[i].getContenu());
                QString classe = QString::fromStdString(mesQuestion[i].getClasse()->getTitre());
                QDateTime date = mesQuestion[i].getDateQ();
                int idetd = mesQuestion[i].getIdEtd();
                int idcl = mesQuestion[i].getIdClasse();
                QString dateStr = mesQuestion[i].getDateQ().toString("dd/MM/yyyy a HH:mm");
                ui->tabQuestions->setItem(i, 0, new QTableWidgetItem(nom));
                ui->tabQuestions->setItem(i, 1, new QTableWidgetItem(questionposer));
                ui->tabQuestions->setItem(i, 2, new QTableWidgetItem(classe));
                ui->tabQuestions->setItem(i, 3, new QTableWidgetItem(dateStr));
                QWidget* pWidget = new QWidget();
                QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
                pLayout->setContentsMargins(2, 2, 2, 2);
                pLayout->setSpacing(5);
                QLineEdit* reponse = new QLineEdit();
                reponse->setStyleSheet("border: 1px solid #cccccc;"
                                       " border-radius: 4px;"
                                       " padding: 4px;");
                QPushButton* repondre = new QPushButton("Repondre");
                repondre->setStyleSheet("background-color: green;"
                                              " color: white; "
                                              "font-weight: bold; "
                                              "border-radius: 4px;"
                                              " padding: 5px;");
                pLayout->addWidget(reponse);
                pLayout->addWidget(repondre);
                connect(repondre,&QPushButton::clicked,[this, id,professeur,date,idetd,idcl,reponse,questionposer]() {
                    QString repo = reponse->text();
                    if (repo.isEmpty()) {
                        QMessageBox::warning(this,"Echech","Veuillez ecrit une reponse");
                    }
                    else {
                        QMessageBox::StandardButton comfirmation = QMessageBox::question(this,"Comfirmation","Vous etes sur de repondre?",QMessageBox::Yes|QMessageBox::No);
                        if (comfirmation == QMessageBox::Yes) {
                            QDateTime d = QDateTime::currentDateTime();
                            Question question(id,questionposer.toStdString(),date,idetd,professeur->getId(),idcl);
                            bool done = professeur->AddReponse(question,repo.toStdString());
                            if (done) {
                                QMessageBox::information(this,"Succes","Reponse poster");
                                afficherQuestion(this->user);
                            }
                            else {
                                QMessageBox::warning(this,"Erreur","reponse n'a pas ete poster");
                            }
                        }
                    }
                });
                ui->tabQuestions->setCellWidget(i, 4, pWidget);
            }
        } else {
            ui->tabQuestions->setVisible(false);
            ui->msgVide->setText("Vous n'avez pas de questions pour le moment");
            ui->msgVide->setVisible(true);
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
        ui->question->setVisible(true);
        ui->classe->setVisible(true);
        ui->poser->setVisible(true);
        ui->label_2->setVisible(true);
        std::vector<Classe> mesClasse = etudiant->getCoursInscri();
        if (mesClasse.size() > 0) {
            ui->classe->clear();
            for (size_t i=0;i<mesClasse.size();i++){
                QString titre = QString::fromStdString(mesClasse[i].getTitre());
                QString nomprof = QString::fromStdString(mesClasse[i].getNomProf());
                int idprof = mesClasse[i].getIdProf();
                int id = mesClasse[i].getId();
                ui->classe->addItem(titre,id);
            }
        }
        std::vector<Question> mesQuestion = etudiant->getMesQuestions();
        if (mesQuestion.size() > 0) {
            ui->tabQuestions->clearContents();
            ui->tabQuestions->setRowCount(mesQuestion.size());
            ui->tabQuestions->setColumnCount(5);
            ui->tabQuestions->setHorizontalHeaderLabels({"Titre du classe","Votre question", "Prof", "Date poster","Reponse"});
            ui->tabQuestions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesQuestion.size(); ++i) {
                int id = mesQuestion[i].getId();
                QString titre = QString::fromStdString(mesQuestion[i].getClasse()->getTitre());
                QString contenu = QString::fromStdString(mesQuestion[i].getContenu());
                QString prof = QString::fromStdString(mesQuestion[i].getClasse()->getNomProf());
                QString reponse = "le prof n'a pas reponde encore";
                if (mesQuestion[i].getReponse() != nullptr) {
                    reponse = QString::fromStdString(*mesQuestion[i].getReponse());
                }
                QString dateStr = mesQuestion[i].getDateQ().toString("dd/MM/yyyy a HH:mm");
                ui->tabQuestions->setItem(i, 0, new QTableWidgetItem(titre));
                ui->tabQuestions->setItem(i, 1, new QTableWidgetItem(contenu));
                ui->tabQuestions->setItem(i, 2, new QTableWidgetItem(prof));
                ui->tabQuestions->setItem(i, 3, new QTableWidgetItem(dateStr));
                ui->tabQuestions->setItem(i, 4, new QTableWidgetItem(reponse));
            }
        } else {
            ui->tabQuestions->setVisible(false);
            ui->msgVide->setText("Vous n'avez pas de questions pour le moment");
            ui->msgVide->setVisible(true);
        }
    }
}
void QuestionsPage::on_poser_clicked() {
    if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)){
        QString quest = ui->question->toPlainText();
        if (quest.isEmpty())
            QMessageBox::warning(this,"Echec","Veuillez entrer une question");
        else {
            int idcl = ui->classe->currentData().toInt();
            int idprof = DB::getIdprofByClass(idcl);
            QDateTime d = QDateTime::currentDateTime();
            Question question(1,quest.toStdString(),d,etudiant->getId(),idprof,idcl);
            bool estdone = etudiant->addQuestion(question);
            if (estdone) {
                QMessageBox::information(this,"Success","Question envoyer avec succes");
                ui->question->clear();
                afficherQuestion(user);
            }
            else {
                QMessageBox::warning(this,"echec","Question n'a pas ete envoyer");
                return;
            }
        }
    }
}