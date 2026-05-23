//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/VideoPage.h"
#include "../UI/ui_videoPage.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include "../../Includes/Video.h"
#include "../../Database/DB.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>

VideoPage::VideoPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::VideoPage) {
    ui->setupUi(this);
}

VideoPage::~VideoPage() {
    delete ui;
}

void VideoPage::afficherVids(User *currentUser) {
    if (!currentUser) return;
    this->user = currentUser;
    ui->msgVide->setText("Vous n'avez pas de video pour le moment");
    ui->msgVide->setVisible(false);
    ui->tabvideo->setVisible(true);
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        std::vector<Video> mesVideos = professeur->getVideos();
        std::vector<Classe> mesClasses = professeur->getMesClasses();
        ui->titreFichier->setVisible(true);
        ui->titreFichier->setPlaceholderText("Taper la titre ici.....");
        ui->chemin->setVisible(true);
        ui->choisirFichier->setVisible(true);
        ui->classe->setVisible(true);
        ui->classe->setPlaceholderText("Choisir classe");
        ui->poster->setVisible(true);
        ui->chemin->clear();
        ui->classe->clear();
        if (mesClasses.size() >0) {
            for (size_t i = 0;i<mesClasses.size();i++) {
                QString titrecl = QString::fromStdString(mesClasses[i].getTitre());
                int idcl = mesClasses[i].getId();
                ui->classe->addItem(titrecl,idcl);
            }
        }
        if (mesVideos.size() > 0){
            ui->tabvideo->clearContents();
            ui->tabvideo->setRowCount(mesVideos.size());
            ui->tabvideo->setColumnCount(3);
            ui->tabvideo->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe"});
            ui->tabvideo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            for (size_t i = 0; i < mesVideos.size(); ++i) {
                QString titre = QString::fromStdString(mesVideos[i].getTitre());
                QString classe = QString::fromStdString(mesVideos[i].getClasse()->getTitre());
                QString dateStr = mesVideos[i].getDate().toString("dd/MM/yyyy a HH:mm");
                ui->tabvideo->setItem(i, 0, new QTableWidgetItem(titre));
                ui->tabvideo->setItem(i, 1, new QTableWidgetItem(dateStr));
                ui->tabvideo->setItem(i, 2, new QTableWidgetItem(classe));
            }
        }
        else {
            ui->tabvideo->setVisible(false);
            ui->tabvideo->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
    else if (Etudiant* etudiant = dynamic_cast<Etudiant *>(user)) {
       std::vector<Video> mesVideos = etudiant->getMesVideos();
        ui->addlbl->setVisible(false);
        ui->titreFichier->setVisible(false);
        ui->chemin->setVisible(false);
        ui->choisirFichier->setVisible(false);
        ui->classe->setVisible(false);
        ui->poster->setVisible(false);
        ui->tabvideo->setVisible(true);
            if (mesVideos.size() > 0){
                ui->tabvideo->clearContents();
                ui->tabvideo->setRowCount(mesVideos.size());
                ui->tabvideo->setColumnCount(4);
                ui->tabvideo->setHorizontalHeaderLabels({"Titre de cours", "Date de publication", "Classe","Action"});
                ui->tabvideo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                for (size_t i = 0; i < mesVideos.size(); ++i) {
                    QString cheminFichier = QString::fromStdString(mesVideos[i].getCheminFichier());
                    QString titre = QString::fromStdString(mesVideos[i].getTitre());
                    QString classe = QString::fromStdString(mesVideos[i].getClasse()->getTitre());
                    QString dateStr = mesVideos[i].getDate().toString("dd/MM/yyyy a HH:mm");
                    ui->tabvideo->setItem(i, 0, new QTableWidgetItem(titre));
                    ui->tabvideo->setItem(i, 1, new QTableWidgetItem(dateStr));
                    ui->tabvideo->setItem(i, 2, new QTableWidgetItem(classe));
                    QPushButton* ouvrir = new QPushButton("Ouvrir");
                    ouvrir->setStyleSheet("background-color: green;"
                                                  " color: white; "
                                                  "font-weight: bold; "
                                                  "border-radius: 4px;"
                                                  " padding: 5px;");
                    ui->tabvideo->setCellWidget(i, 3, ouvrir);
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
        else {
            ui->tabvideo->setVisible(false);
            ui->tabvideo->setVisible(false);
            ui->msgVide->setVisible(true);
        }
    }
}

void VideoPage::on_choisirFichier_clicked() {
    QString cheminfile = QFileDialog::getOpenFileName(this,"Veuillez choisir le fichier","","Videos (*.mp4 *.mkv *.webm *.mov *.avi)");
    if (!cheminfile.isEmpty()) {
        ui->chemin->setText(cheminfile);
    }
}

void VideoPage::on_poster_clicked() {
    if (Professeur* professeur = dynamic_cast<Professeur *>(user)) {
        QString titrefile = ui->titreFichier->text();
        QString cheminSource = ui->chemin->text();
        if (titrefile.isEmpty() || cheminSource.isEmpty()) {
            QMessageBox::warning(this,"Echec","Veuillez entrer un titre de fichier et selectionner un fichier");
            return;
        }
        else{
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
                Classe classe(idcl,idprof,"","","");
                Video video(1,titrefile.toStdString(),cheminFinal.toStdString(),d,idprof,idcl);
                bool estdone = professeur->AddVideo(video,classe);
                if (estdone) {
                    QMessageBox::information(this,"Succes","Video a ete ajouter avec succes");
                    afficherVids(user);
                }
                else {
                    QMessageBox::warning(this,"Echec","Video n'a pas ete ajouter");
                return;
                }
            }
            }
        }