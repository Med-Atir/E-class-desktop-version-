//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/devoirsPage.h"
#include "../UI/ui_devoirsPage.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include "../../Database/DB.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>

DevoirsPage::DevoirsPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::DevoirsPage) {
    ui->setupUi(this);
}

DevoirsPage::~DevoirsPage() {
    delete ui;
}

void DevoirsPage::afficherFiles(User *currentUser) {
    if (!currentUser) return;
    this->user = currentUser;
    ui->msgVide->setText("Vous n'avez pas ni devoir ni cours pour le moment");
    ui->msgVide->setVisible(false);
    ui->tabdocs->setVisible(true);
    ui->tabdevoirs->setVisible(true);
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        std::vector<Document> mesDocuments = professeur->getDocuments();
        std::vector<Classe> mesClasses = professeur->getMesClasses();
        std::vector<Devoir> mesDevoirs = professeur->getDevoirs();
        ui->titreFichier->setVisible(true);
        ui->titreFichier->setPlaceholderText("Taper la titre ici.....");
        ui->chemin->setVisible(true);
        ui->choisirFichier->setVisible(true);
        ui->cours->setVisible(true);
        ui->devoir->setVisible(true);
        ui->classe->setVisible(true);
        ui->classe->setPlaceholderText("Choisir classe");
        ui->poster->setVisible(true);
        ui->deadline->setVisible(true);
        ui->consigne->setVisible(true);
        ui->consigne->setPlaceholderText("Taper la consigne ici.....");
        ui->chemin->clear();
        ui->classe->clear();
        if (mesClasses.size() >0) {
            for (size_t i = 0;i<mesClasses.size();i++) {
                QString titrecl = QString::fromStdString(mesClasses[i].getTitre());
                int idcl = mesClasses[i].getId();
                ui->classe->addItem(titrecl,idcl);
            }
        }
        if (mesDocuments.size() > 0 || mesDevoirs.size() > 0) {
            if (mesDocuments.size() > 0){
                ui->tabdocs->clearContents();
                ui->tabdocs->setRowCount(mesDocuments.size());
                ui->tabdocs->setColumnCount(3);
                ui->tabdocs->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe"});
                ui->tabdocs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                for (size_t i = 0; i < mesDocuments.size(); ++i) {
                    QString titre = QString::fromStdString(mesDocuments[i].getTitre());
                    QString classe = QString::fromStdString(mesDocuments[i].getClasse()->getTitre());
                    QString dateStr = mesDocuments[i].getDate().toString("dd/MM/yyyy a HH:mm");
                    ui->tabdocs->setItem(i, 0, new QTableWidgetItem(titre));
                    ui->tabdocs->setItem(i, 1, new QTableWidgetItem(dateStr));
                    ui->tabdocs->setItem(i, 2, new QTableWidgetItem(classe));
                }
            }
            if (mesDevoirs.size() > 0) {
                ui->tabdevoirs->clearContents();
                ui->tabdevoirs->setRowCount(mesDevoirs.size());
                ui->tabdevoirs->setColumnCount(5);
                ui->tabdevoirs->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe","Consigne","Deadline"});
                ui->tabdevoirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                for (size_t i = 0; i < mesDevoirs.size(); ++i) {
                    QString titre = QString::fromStdString(mesDevoirs[i].getTitre());
                    QString classe = QString::fromStdString(mesDevoirs[i].getClasse()->getTitre());
                    QString consigne = QString::fromStdString(mesDevoirs[i].getConsigne());
                    QString dateStr = mesDevoirs[i].getDate().toString("dd/MM/yyyy a HH:mm");
                    QString datedead = QString::fromStdString(mesDevoirs[i].getdeadline());
                    ui->tabdevoirs->setItem(i, 0, new QTableWidgetItem(titre));
                    ui->tabdevoirs->setItem(i, 1, new QTableWidgetItem(dateStr));
                    ui->tabdevoirs->setItem(i, 2, new QTableWidgetItem(classe));
                    ui->tabdevoirs->setItem(i, 3, new QTableWidgetItem(consigne));
                    ui->tabdevoirs->setItem(i, 4, new QTableWidgetItem(datedead));
                }
            }
        }else {
            ui->tabdocs->setVisible(false);
            ui->tabdevoirs->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
       std::vector<Document> mesDocuments = etudiant->getMesDocuments();
        std::vector<Devoir> mesDevoirs = etudiant->getDevoirs();
        ui->addlbl->setVisible(false);
        ui->titreFichier->setVisible(false);
        ui->chemin->setVisible(false);
        ui->choisirFichier->setVisible(false);
        ui->cours->setVisible(false);
        ui->devoir->setVisible(false);
        ui->classe->setVisible(false);
        ui->poster->setVisible(false);
        ui->deadline->setVisible(false);
        ui->consigne->setVisible(false);
        ui->tabdevoirs->setVisible(true);
        if (mesDocuments.size() > 0 || mesDevoirs.size() > 0) {
            if (mesDocuments.size() > 0){
                ui->tabdocs->clearContents();
                ui->tabdocs->setRowCount(mesDocuments.size());
                ui->tabdocs->setColumnCount(4);
                ui->tabdocs->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe","Action"});
                ui->tabdocs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                for (size_t i = 0; i < mesDocuments.size(); ++i) {
                    QString cheminFichier = QString::fromStdString(mesDocuments[i].getCheminFichier());
                    QString titre = QString::fromStdString(mesDocuments[i].getTitre());
                    QString classe = QString::fromStdString(mesDocuments[i].getClasse()->getTitre());
                    QString dateStr = mesDocuments[i].getDate().toString("dd/MM/yyyy a HH:mm");
                    ui->tabdocs->setItem(i, 0, new QTableWidgetItem(titre));
                    ui->tabdocs->setItem(i, 1, new QTableWidgetItem(dateStr));
                    ui->tabdocs->setItem(i, 2, new QTableWidgetItem(classe));
                    QPushButton* ouvrir = new QPushButton("Ouvrir");
                    ouvrir->setStyleSheet("background-color: green;"
                                                  " color: white; "
                                                  "font-weight: bold; "
                                                  "border-radius: 4px;"
                                                  " padding: 5px;");
                    ui->tabdocs->setCellWidget(i, 3, ouvrir);
                    connect(ouvrir,&QPushButton::clicked,[this,cheminFichier]() {
                        QFile fichier(cheminFichier);
                        if (!fichier.exists()) {
                            QMessageBox::warning(this, "Fichier introuvable", "Le fichier n'existe pas.");
                            return;
                        }
                        bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
                        if (!success) {
                            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir ce fichier");
                        }
                    });
                }
            }
            if (mesDevoirs.size() > 0) {
                ui->tabdevoirs->clearContents();
                ui->tabdevoirs->setRowCount(mesDevoirs.size());
                ui->tabdevoirs->setColumnCount(6);
                ui->tabdevoirs->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe","Consigne","Deadline","Action"});
                ui->tabdevoirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                for (size_t i = 0; i < mesDevoirs.size(); ++i) {
                    QString cheminFichier = QString::fromStdString(mesDevoirs[i].getCheminFichier());
                    QString titre = QString::fromStdString(mesDevoirs[i].getTitre());
                    QString classe = QString::fromStdString(mesDevoirs[i].getClasse()->getTitre());
                    QString consigne = QString::fromStdString(mesDevoirs[i].getConsigne());
                    QString dateStr = mesDevoirs[i].getDate().toString("dd/MM/yyyy a HH:mm");
                    QString datedead = QString::fromStdString(mesDevoirs[i].getdeadline());
                    ui->tabdevoirs->setItem(i, 0, new QTableWidgetItem(titre));
                    ui->tabdevoirs->setItem(i, 1, new QTableWidgetItem(dateStr));
                    ui->tabdevoirs->setItem(i, 2, new QTableWidgetItem(classe));
                    ui->tabdevoirs->setItem(i, 3, new QTableWidgetItem(consigne));
                    ui->tabdevoirs->setItem(i, 4, new QTableWidgetItem(datedead));
                    QPushButton* ouvrir = new QPushButton("Ouvrir");
                    ouvrir->setStyleSheet("background-color: green;"
                                                  " color: white; "
                                                  "font-weight: bold; "
                                                  "border-radius: 4px;"
                                                  " padding: 5px;");
                    ui->tabdevoirs->setCellWidget(i, 5, ouvrir);
                    connect(ouvrir,&QPushButton::clicked,[this,cheminFichier]() {
                        QFile fichier(cheminFichier);
                        if (!fichier.exists()) {
                            QMessageBox::warning(this, "Fichier introuvable", "Le fichier n'existe pas.");
                            return;
                        }
                        bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
                        if (!success) {
                            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir ce fichier");
                        }
                    });
                }
            }
        }else {
            ui->tabdocs->setVisible(false);
            ui->tabdevoirs->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
}

void DevoirsPage::on_choisirFichier_clicked() {
    QString cheminfile = QFileDialog::getOpenFileName(this,"Veuillez choisir le fichier","","Documents (*.ppt *.docx *.pdf *.doc *.txt,"
                                                                                            "*.pptx *.csv *.xls *.xlsx *.txt *.html)");
    if (!cheminfile.isEmpty()) {
        ui->chemin->setText(cheminfile);
    }
}

void DevoirsPage::on_poster_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        QString titrefile = ui->titreFichier->text();
        QString cheminSource = ui->chemin->text();
        if (titrefile.isEmpty() || cheminSource.isEmpty()) {
            QMessageBox::warning(this,"Echec","Veuillez entrer un titre de fichier et selectionner un fichier");
            return;
        }
        else{
            QString typefile = "";
            if (ui->cours->isChecked())
                typefile = "cours";
            else if (ui->devoir->isChecked())
                typefile = "devoir";
            QString dossierDest = QCoreApplication::applicationDirPath() + "/EClass_Fichiers";
            QDir dir(dossierDest);//on creer le dossier de destination
            if (!dir.exists()) {
                dir.mkpath(".");// si le folder n'existe pas on le creer par mkpath
            }
            QFileInfo fileInfo(cheminSource);
            QString nomFichier = fileInfo.fileName();//on extraire le nom du fichier
            QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_");
            QString cheminFinal = dossierDest + "/" + timestamp + nomFichier;//on ajout a lui l'heure actuelle
            //pour eviter les conflits et les erasements
            if (!QFile::copy(cheminSource, cheminFinal)) {
                QMessageBox::warning(this, "erreur", "Impossible d'uploader le fichier");
                return;// si la copier fail on quite(inis7ab taktiki)
            }
            int idcl = ui->classe->currentData().toInt();
            int idprof = professeur->getId();
            QDateTime d = QDateTime::currentDateTime();
            if (typefile == "cours") {
                Classe classe(idcl,idprof,"","","");
                Document document(1,titrefile.toStdString(),cheminFinal.toStdString(),d,idprof,idcl);
                bool estdone = professeur->AddDocument(document,classe);
                if (estdone) {
                    QMessageBox::information(this,"Succes","Cours a ete ajouter avec succes");
                    afficherFiles(user);
                }
                else {
                    QMessageBox::warning(this,"Echec","Cours n'a pas ete ajouter");
                return;
                }
            }
            else if (typefile == "devoir") {
                QString aide = ui->consigne->toPlainText();
                QDateTime dernier = ui->deadline->dateTime();
                if (aide.isEmpty() || !(dernier.isValid())) {
                    QMessageBox::warning(this,"Erreur","Veuillez entrer une cosigne et date valides");
                    return;
                }
                Classe classe(idcl,idprof,"","","");
                Devoir devoir(1,titrefile.toStdString(),aide.toStdString(),dernier.toString("dd/MM/yyyy a HH:mm:ss").toStdString(),cheminFinal.toStdString(),d,idprof,idcl);
                bool estdone = professeur->addDevoir(devoir);
                if (estdone) {
                    QMessageBox::information(this,"Succes","Devoir a ete ajouter avec succes");
                    afficherFiles(user);
                }
                else {
                    QMessageBox::warning(this,"Echec","Devoir n'a pas ete ajouter");\
                    return;
                }
            }
        }
    }
}