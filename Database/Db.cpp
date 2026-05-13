//Created by Mohammed atir on 11/05/2026
//IA S4 / Groupe 1
#include "DB.h"
#include <QDebug>
#include <string>
#include "../Includes/Classe.h"
#include "../Includes/Professeur.h"
#include "../Includes/Etudiant.h"

DB::DB() {
    // On spécifie qu'on utilise le driver SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DB::~DB() {
    disconnect();
}

bool DB::connect(const QString& dbName) {
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Erreur critique : Impossible d'ouvrir la base de donnees ->" << db.lastError().text();
        return false;
    }
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    qDebug() << "Succes : Connecte a la base de donnees SQLite.";
    return true;
}

void DB::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de donnees deconnectee.";
    }
}

std::string DB::AddClasse(Classe &cl, int idprof) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO classe (titre,code,description,prof_id) VALUES (:titre,:code,:description,:id)");
    requete.bindValue(":titre",QString::fromStdString(cl.getTitre()));
    requete.bindValue(":code",QString::fromStdString(cl.getCode()));
    requete.bindValue(":description",QString::fromStdString(cl.getDescription()));
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        return cl.getCode();
    }
    else {
        return "erreur";
    }
}

Professeur *DB::getProf(int idProf) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM user WHERE id = :id");
    requete.bindValue(":id",idProf);
    if (requete.exec()) {
        if (requete.next()){
            int Id = requete.value("id").toInt();
            std::string Nom = requete.value("nom").toString().toStdString();
            std::string Email = requete.value("email").toString().toStdString();
            Professeur* pr = new Professeur(Id,Nom,Email);
            return pr;
        }
    }
    else {
        std::cout<<"Probleme servue" <<std::endl;
    }
    return nullptr;
}

Etudiant *DB::getEtudiant(int idEtd) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM user WHERE id = :id");
    requete.bindValue(":id",idEtd);
    if (requete.exec()) {
        if (requete.next()){
            int Id = requete.value("id").toInt();
            std::string Nom = requete.value("nom").toString().toStdString();
            std::string Email = requete.value("email").toString().toStdString();
            Etudiant* etd = new Etudiant(Id,Nom,Email);
            return etd;
        }
    }
    else {
        std::cout<<"Probleme servue" <<std::endl;
    }
    return nullptr;
}

Classe *DB::getClasse(int idclasse) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM classe WHERE id = :id");
    requete.bindValue(":id",idclasse);
    if (requete.exec()) {
        if (requete.next()){
            int Id = requete.value("id").toInt();
            int Idprof = requete.value("prof_id").toInt();
            std::string Titre = requete.value("titre").toString().toStdString();
            std::string Code = requete.value("code").toString().toStdString();
            std::string Description = requete.value("description").toString().toStdString();
            Classe* classe = new Classe(Id,Idprof,Titre,Code,Description);
            return classe;
        }
    }
    else {
        std::cout<<"Probleme servue" <<std::endl;
    }
    return nullptr;
}

bool DB::DelClasse(Classe &cl) {
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

std::vector<Demande> DB::getDemandes(int idprof) {
    std::vector<Demande> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM demande "
                    "INNER JOIN classe ON demande.id_class = classe.id"
                    " WHERE classe.prof_id = :id AND demande.status = 'en_attente'");
    requete.bindValue(":id",idprof);
    if (requete.exec()){
        while (requete.next()) {
            int id = requete.value("id").toInt();
            int idetd = requete.value("id_etudiant").toInt();
            int idcl = requete.value("id_classe").toInt();
            std::string status = requete.value("status").toString().toStdString();
            QDateTime date = requete.value("date").toDateTime();
            Demande demande(id,status,date,idetd,idcl);
            vect.push_back(demande);
        }
    }
    return vect;
}
std::vector<Devoir> DB::getEtudiantDevoirs(int idetd) {
    std::vector<Devoir> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM devoir INNER JOIN classe_etudiant ON devoir.id_classe = classe_etudiant.classe_id WHERE classe_etudiant.etudiant_id = :id");
    requete.bindValue(":id",idetd);
    if (requete.exec()) {
        while (requete.next()){
            int id = requete.value("id").toUInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string cheminFichier = requete.value("chemin_fichier").toString().toStdString();
            QDateTime date = requete.value("date_poste").toDateTime();
            int idprof = requete.value("id_prof").toUInt();
            int idclasse = requete.value("id_classe").toUInt();
            std::string consigne = requete.value("consigne").toString().toStdString();
            std::string deadline = requete.value("deadline").toString().toStdString();
            Devoir devoir(id,titre,consigne,deadline,cheminFichier,date,idprof,idclasse);
            vect.push_back(devoir);
        }
    }
return vect;
}

void DB::addQuestion(Question &q) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO question(contenu,id_etudiant,id_prof,id_classe) VALUES (:con,:id1,:id2,:id3)");
    requete.bindValue(":con",QString::fromStdString(q.getContenu()));
    requete.bindValue(":id1",q.getIdEtd());
    requete.bindValue(":id2",q.getIdProf());
    requete.bindValue(":id3",q.getIdClasse());
    if (requete.exec())
        std::cout<<"Question a ete ajouter avec succes!!"<<std::endl;
    else
        std::cout<<"Un probleme servu!!"<<std::endl;
}

std::vector<Annonce> DB::getEtudiantAnnonces(int idetd) {
    std::vector<Annonce> vect;
    QSqlQuery requete;
    requete.prepare("SELECT annonce.id AS annonce_id, annonce.titre AS annonce_titre"
                    ", annonce.contenu AS annonce_contenu,annonce.id_prof AS annonce_idprof,"
                    " annonce.id_classe AS annonce_idclasse,annonce.date_poste AS annonce_date_poste"
                    " FROM annonce"
                    " INNER JOIN classe_etudiant ON annonce.classe_id = classe_etudiant.classe_id "
                    "WHERE classe_etudiant.etudiant_id = :id_etd");
    requete.bindValue(":id_etd",idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int annonceID = requete.value("annonce_id").toUInt();
            std::string annoncetitre = requete.value("annonce_titre").toString().toStdString();
            std::string annoncecontenu = requete.value("annonce_contenu").toString().toStdString();
            int annoncePr = requete.value("annonce_idprof").toUInt();
            int annonceCl = requete.value("annonce_idclasse").toUInt();
            QDateTime annonceDate = requete.value("annonce_date_poste").toDateTime();
            Annonce a1(annonceID,annoncetitre,annoncecontenu,annonceDate,annoncePr,annonceCl);
            vect.push_back(a1);
        }
    }
    else {
        std::cout<<"probleme "<<std::endl;
    }
    return vect;
}


std::vector<Classe> DB::getEtudiantclasse(int idetd) {
    std::vector<Classe> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM classe "
                    "INNER JOIN classe_etudiant ON classe.id = classe_etudiant.classe_id "
                    "WHERE classe_etudiant.etudiant_id = :id");
    requete.bindValue(":id",idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int Id = requete.value("id").toUInt();
            int Idprof = requete.value("prof_id").toUInt();
            std::string Titre = requete.value("titre").toString().toStdString();
            std::string Code = requete.value("code").toString().toStdString();
            std::string Description = requete.value("description").toString().toStdString();
            Classe c1(Id,Idprof,Titre,Code,Description);
            vect.push_back(c1);
        }
    }
    else {
        std::cout<<"probleme "<<std::endl;
    }
    return vect;
}

std::vector<Classe> DB::getProfclasse(int idprof) {
    QSqlQuery requete;
    std::vector<Classe> vect;
    requete.prepare("SELECT * FROM classe WHERE prof_id = :id");
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int Id = requete.value("id").toInt();
            int Idprof = requete.value("prof_id").toInt();
            std::string Titre = requete.value("titre").toString().toStdString();
            std::string Code = requete.value("code").toString().toStdString();
            std::string Description = requete.value("description").toString().toStdString();
            Classe classe(Id,Idprof,Titre,Code,Description);
            vect.push_back(classe);
        }
    }
    return vect;
}

bool DB::AccepteDemande(Demande &demande) {
    QSqlQuery requete;
    requete.prepare("UPDATE demande SET status = 'accepte' WHERE id = :id");
    requete.bindValue(":id",demande.getId());
    if (requete.exec())
        return true;
    else
        return false;
}

bool DB::RejetDemande(Demande &demande) {
    QSqlQuery requete;
    requete.prepare("UPDATE demande SET status = 'refuse' WHERE id = :id");
    requete.bindValue(":id",demande.getId());
    if (requete.exec())
        return true;
    else
        return false;
}

bool DB::AddAnnoce(Annonce &annonce) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO annonce(id,titre,contenu,id_prof,id_classe) VALUES (:id,:titre,:contenu,:idprof,:idclasse)");
    requete.bindValue(":id",annonce.getId());
    requete.bindValue(":titre",QString::fromStdString(annonce.getTitre()));
    requete.bindValue(":contenu",QString::fromStdString(annonce.getContenu()));
    requete.bindValue(":idprof",annonce.getIdprof());
    requete.bindValue(":idclasse",annonce.getIdclasse());
    if (requete.exec()) {
        return true;
    }
    return false;
}

bool DB::AddDocument(Document& document,Classe &classe) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO document(id,titre,chemin_fichier,id_classe,id_prof) VALUES (:id,:titre,:chemin,:idcl,:idpr)");
    requete.bindValue(":id",document.getID());
    requete.bindValue(":titre",QString::fromStdString(document.getTitre()));
    requete.bindValue(":chemin",QString::fromStdString(document.getCheminFichier()));
    requete.bindValue(":idcl",classe.getId());
    requete.bindValue(":idpr",classe.getIdProf());
    if (requete.exec()) {
        return true;
    }
    return false;
}

bool DB::AddReponse(Question& q,std::string reponse) {
    QSqlQuery requete;
    requete.prepare("UPDATE question SET est_reponde = :e,date_reponse = :date,reponse = :reponse WHERE id = :id");
    requete.bindValue("id",q.getId());
    requete.bindValue(":e",1);
    requete.bindValue("date_reponse",QDateTime::currentDateTime());
    requete.bindValue("reponse",QString::fromStdString(reponse));
    if (requete.exec())
        return true;
    else
        return false;
}

bool DB::DelAnnonce(Annonce &annonce) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM annonce WHERE id = :id");
    requete.bindValue("id",annonce.getId());
    if (requete.exec())
        return true;
    else
        return false;
}

bool DB::DelDocument(Document &document) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM document WHERE id = :id");
    requete.bindValue(":id",document.getID());
    if (requete.exec())
        return true;
    else
        return false;
}

bool DB::DelDevoir(Devoir &devoir) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM devoir WHERE id = :id");
    requete.bindValue(":id",devoir.getID());
    if (requete.exec())
        return true;
    else
        return false;
}

std::vector<Annonce> DB::getProfAnnonces(int idprof) {
    QSqlQuery requete;
    std::vector<Annonce> vect;
    requete.prepare("SELECT * FROM annonce WHERE id_prof = :id");
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int Id = requete.value("id").toInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string contenu = requete.value("contenu").toString().toStdString();
            QDateTime date = requete.value("date_poste").toDateTime();
            int idprof = requete.value("id_prof").toInt();
            int idclasse = requete.value("id_classe").toInt();
            Annonce annonce(Id,titre,contenu,date,idprof,idclasse);
            vect.push_back(annonce);
        }
    }
    return vect;
}

std::vector<Document> DB::getDocuments(Classe &classe) {
    QSqlQuery requete;
    std::vector<Document> vect;
    requete.prepare("SELECT * FROM document WHERE id_classe = :id");
    requete.bindValue(":id",classe.getId());
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string cheminFichier = requete.value("chemin_fichier").toString().toStdString();
            QDateTime date = requete.value("date_upload").toDateTime();
            int idprof = requete.value("id_prof").toInt();
            int idclasse = requete.value("id_classe").toInt();
            Document document(id,titre,cheminFichier,date,idprof,idclasse);
            vect.push_back(document);
        }
    }
    return vect;
}

std::vector<Devoir> DB::getProfDevoirs(int idprof) {
    std::vector<Devoir> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM devoir WHERE id_prof = :id");
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toUInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string cheminFichier = requete.value("chemin_fichier").toString().toStdString();
            QDateTime date = requete.value("date_poste").toDateTime();
            int idprof = requete.value("id_prof").toUInt();
            int idclasse = requete.value("id_classe").toUInt();
            std::string consigne = requete.value("consigne").toString().toStdString();
            std::string deadline = requete.value("deadline").toString().toStdString();
            Devoir devoir(id,titre,consigne,deadline,cheminFichier,date,idprof,idclasse);
            vect.push_back(devoir);
        }
    }
    return vect;
}

std::vector<Question> DB::getEtudiantQuestions(int idetd) {
    std::vector<Question> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM question WHERE id_etudiant = :id");
    requete.bindValue(":id", idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string contenu = requete.value("contenu").toString().toStdString();
            QDateTime dateQuestion = requete.value("date_question").toDateTime();
            int idEtd  = requete.value("id_etudiant").toInt();
            int idProf = requete.value("id_prof").toInt();
            int idClasse = requete.value("id_classe").toInt();
            bool estRepondu = (requete.value("est_reponde").toInt() == 1);
            QDateTime tempDateReponse;
            std::string tempReponse;
            QDateTime* ptrDate = nullptr;
            std::string* ptrRep = nullptr;
            if (estRepondu) {
                tempDateReponse = requete.value("date_reponse").toDateTime();
                tempReponse = requete.value("reponse").toString().toStdString();
                ptrDate = &tempDateReponse;
                ptrRep = &tempReponse;
            }
            Question question(id,contenu,dateQuestion,idEtd,idProf,idClasse,estRepondu,ptrDate,ptrRep);
            vect.push_back(question);
        }
    }
    return vect;
}

std::vector<Question> DB::getProfQuestions(int idprof) {
    std::vector<Question> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM question WHERE id_prof = :id AND est_reponde = 0");
    requete.bindValue(":id", idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string contenu = requete.value("contenu").toString().toStdString();
            QDateTime dateQuestion = requete.value("date_question").toDateTime();
            int idEtd  = requete.value("id_etudiant").toInt();
            int idProf = requete.value("id_prof").toInt();
            int idClasse = requete.value("id_classe").toInt();
            bool estRepondu = (requete.value("est_reponde").toInt() == 1);
            QDateTime tempDateReponse;
            std::string tempReponse;
            QDateTime* ptrDate = nullptr;
            std::string* ptrRep = nullptr;
            if (estRepondu) {
                tempDateReponse = requete.value("date_reponse").toDateTime();
                tempReponse = requete.value("reponse").toString().toStdString();
                ptrDate = &tempDateReponse;
                ptrRep = &tempReponse;
            }
            Question question(id,contenu,dateQuestion,idEtd,idProf,idClasse,estRepondu,ptrDate,ptrRep);
            vect.push_back(question);
        }
    }
    return vect;
}

bool DB::InscrireClasse(int idetd,Classe &classe) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO demande(id_etudiant,id_classe) VALUES (:idetd,:idcl)");
    requete.bindValue(":idetd",idetd);
    requete.bindValue(":idcl",classe.getId());
    if (requete.exec())
        return true;
    else
        return false;
}

Classe* DB::RechercherClasse(std::string code) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM classe WHERE code = :code");
    requete.bindValue(":code",QString::fromStdString(code));
    if (requete.exec()) {
        if (requete.next()) {
            int Id = requete.value("id").toInt();
            int Idprof = requete.value("prof_id").toInt();
            std::string Titre = requete.value("titre").toString().toStdString();
            std::string Code = requete.value("code").toString().toStdString();
            std::string Description = requete.value("description").toString().toStdString();
            Classe* classe = new Classe (Id,Idprof,Titre,Code,Description);
            return classe;
        }
    }
    return nullptr;
}

std::vector<Document> DB::getProfDocuments(int idprof) {
    std::vector<Document> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM document WHERE id_prof = :id");
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toUInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string cheminFichier = requete.value("chemin_fichier").toString().toStdString();
            QDateTime date = requete.value("date_upload").toDateTime();
            int idprof = requete.value("id_prof").toUInt();
            int idclasse = requete.value("id_classe").toUInt();
            Document document(id,titre,cheminFichier,date,idprof,idclasse);
            vect.push_back(document);
        }
    }
    return vect;
}