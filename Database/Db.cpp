//Created by Mohammed atir on 11/05/2026
//IA S4 / Groupe 1
#include "DB.h"
#include <QDebug>
#include <string>
#include "../Includes/Classe.h"
#include "../Includes/Professeur.h"
#include "../Includes/Etudiant.h"
#include "../Includes/User.h"
#include "../Includes/Video.h"
#include <QByteArray>
#include <QCryptographicHash>

DB::DB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DB::~DB() {
    disconnect();
}

bool DB::connect(const QString& dbName) {
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Erreur: Impossible d'ouvrir la base de donnees car: " << db.lastError().text();
        return false;
    }
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    qDebug() << "Succes : Connecte a la base de donnees";
    return true;
}

void DB::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de donnees deconnectee.";
    }
}

bool DB::AddClasse(Classe &cl, int idprof) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO classe (titre,code,description,prof_id) VALUES (:titre,:code,:description,:id)");
    requete.bindValue(":titre",QString::fromStdString(cl.getTitre()));
    requete.bindValue(":code",QString::fromStdString(cl.getCode()));
    requete.bindValue(":description",QString::fromStdString(cl.getDescription()));
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        return true;
    }
    else {
        return false;
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
                    "INNER JOIN classe ON demande.id_classe = classe.id"
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

bool DB::addQuestion(Question &q) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO question(contenu,id_etudiant,id_prof,id_classe) VALUES (:con,:id1,:id2,:id3)");
    requete.bindValue(":con",QString::fromStdString(q.getContenu()));
    requete.bindValue(":id1",q.getIdEtd());
    requete.bindValue(":id2",q.getIdProf());
    requete.bindValue(":id3",q.getIdClasse());
    if (requete.exec())
        return true;
    else
        qDebug() <<"Error:" <<requete.lastError().text();
        return false;
}

std::vector<Annonce> DB::getEtudiantAnnonces(int idetd) {
    std::vector<Annonce> vect;
    QSqlQuery requete;
    requete.prepare("SELECT annonce.id AS annonce_id, annonce.titre AS annonce_titre"
                    ", annonce.contenu AS annonce_contenu,annonce.id_prof AS annonce_idprof,"
                    " annonce.id_classe AS annonce_idclasse,annonce.date_poste AS annonce_date_poste"
                    " FROM annonce"
                    " INNER JOIN classe_etudiant ON annonce.id_classe = classe_etudiant.classe_id "
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
    requete.prepare("UPDATE demande SET status = 'accepte' WHERE id = :id AND status ='en_attente'");
    requete.bindValue(":id",demande.getId());
    if (requete.exec()) {
        QSqlQuery requete2;
        requete2.prepare("INSERT INTO classe_etudiant (classe_id, etudiant_id) "
                         "SELECT id_classe, id_etudiant FROM demande WHERE id = :id");
        requete2.bindValue(":id",demande.getId());//j'ai utiliser cette requete imbrique pour corriger une bugg
        //car dans la methode qui appelle cette methode j'ai initialiser la classe demande par des valeurs imaginaire;
        if (requete2.exec())
        return true;
        else
            return false;
    }
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

bool DB::AddAnnoce(Annonce& a) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO annonce(titre,contenu,id_prof,id_classe) VALUES (:titre,:contenu,:idprof,:idclasse)");
    requete.bindValue(":titre",QString::fromStdString(a.getTitre()));
    requete.bindValue(":contenu",QString::fromStdString(a.getContenu()));
    requete.bindValue(":idprof",a.getIdprof());
    requete.bindValue(":idclasse",a.getIdclasse());
    if (requete.exec()) {
        return true;
    }
    return false;
}

bool DB::AddDocument(Document& document) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO document(titre,chemin_fichier,id_classe,id_prof) VALUES (:titre,:chemin,:idcl,:idpr)");
    requete.bindValue(":titre",QString::fromStdString(document.getTitre()));
    requete.bindValue(":chemin",QString::fromStdString(document.getCheminFichier()));
    requete.bindValue(":idcl",document.getIdclasse());
    requete.bindValue(":idpr",document.getIdprof());
    if (requete.exec()) {
        return true;
    }
    qDebug() << "Echec d'ajout :" << requete.lastError().text();
    return false;
}

bool DB::AddReponse(Question& q,std::string reponse) {
    QSqlQuery requete;
    requete.prepare("UPDATE question SET est_reponde = :e,date_reponse = :date,reponse = :reponse WHERE id = :id");
    requete.bindValue(":id",q.getId());
    requete.bindValue(":e",1);
    requete.bindValue(":date",QDateTime::currentDateTime());
    requete.bindValue(":reponse",QString::fromStdString(reponse));
    if (requete.exec() && requete.numRowsAffected() > 0)
        return true;
    else
        return false;
}

bool DB::DelAnnonce(Annonce &annonce) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM annonce WHERE id = :id");
    requete.bindValue(":id",annonce.getId());
    if (requete.exec() && requete.numRowsAffected() > 0)
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
    if (demandeDejaAtt(idetd,classe.getId()))
        return false;
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

User *DB::Login(const std::string &email, const std::string &password) {
    QSqlQuery requete;
    std::string passhasher = hasherPass(password);
    requete.prepare("SELECT * FROM user WHERE email = :email AND password = :password");
    requete.bindValue(":email", QString::fromStdString(email));
    requete.bindValue(":password", QString::fromStdString(passhasher));
    if (requete.exec()) {
        if (requete.next()) {
            int id = requete.value("id").toInt();
            std::string nom = requete.value("nom").toString().toStdString();
            std::string email = requete.value("email").toString().toStdString();
            std::string role = requete.value("role").toString().toStdString();
            if (role == "professeur") {
                return new Professeur(id, nom, email);
            }
            else if (role == "etudiant") {
                return new Etudiant(id, nom, email);
            }
        }
    }
    else {
        qDebug() << "Erreur SQL lors de l'authentification :" << requete.lastError().text();
    }
    return nullptr;
}

bool DB::Signup(const std::string &email, const std::string &nom, const std::string &password, const std::string &role) {
    QSqlQuery requete;
    std::string passhasher = hasherPass(password);
    requete.prepare("INSERT INTO user (email,nom, password, role) VALUES (:email,:nom, :password, :role)");
    requete.bindValue(":email",QString::fromStdString(email));
    requete.bindValue(":nom",QString::fromStdString(nom));
    requete.bindValue(":password",QString::fromStdString(passhasher));
    requete.bindValue(":role",QString::fromStdString(role));
    if (requete.exec()) {
       return true;
    }
    else {
        qDebug() << "Erreur CRITIQUE lors de l'inscription :" << requete.lastError().text();
        return false;
    }
}

std::string DB::hasherPass(const std::string &pass) {
    QByteArray tabpass = QByteArray::fromStdString(pass);
    QByteArray passhasher = QCryptographicHash::hash(tabpass,QCryptographicHash::Sha256);
    return passhasher.toHex().toStdString();
}

bool DB::etdInscrit(int idetd,int idclasse) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM classe_etudiant WHERE classe_id = :idclass AND etudiant_id = :idetd");
    requete.bindValue(":idclass",idclasse);
    requete.bindValue(":idetd",idetd);
    if (requete.exec()) {
        if (requete.next()) {
            return true;
        }
    }
    return false;
}

bool DB::demandeDejaAtt(int idetd, int idclasse) {
    QSqlQuery requete;
    requete.prepare("SELECT * FROM demande WHERE id_classe = :idclass AND id_etudiant = :idetd"
                    " AND status = 'en_attente'");
    requete.bindValue(":idclass",idclasse);
    requete.bindValue(":idetd",idetd);
    if (requete.exec()) {
        if (requete.next()) {
            return true;
        }
    }
    return false;
}

bool DB::delAccount(int iduser) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM user WHERE id = :id");
    requete.bindValue(":id",iduser);
    if (requete.exec())
        return true;
    return false;
}

bool DB::changerEmail(int iduser, std::string email) {
    QSqlQuery requete;
    requete.prepare("UPDATE user SET email = :email WHERE id = :id");
    QString mail = QString::fromStdString(email);
    requete.bindValue(":email",mail);
    requete.bindValue(":id",iduser);
    if (requete.exec())
        return true;
    return false;
}

bool DB::changerNom(int iduser, std::string nom) {
    QSqlQuery requete;
    requete.prepare("UPDATE user SET nom = :nom WHERE id = :id");
    QString name = QString::fromStdString(nom);
    requete.bindValue(":nom",name);
    requete.bindValue(":id",iduser);
    if (requete.exec())
        return true;
    return false;
}

std::vector<Demande> DB::getDemandesEtd(int idetd) {
    std::vector<Demande> mesdemandes;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM demande WHERE id_etudiant = :idE AND status = 'en_attente'");
    requete.bindValue(":idE",idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string status = requete.value("status").toString().toStdString();
            QDateTime date = requete.value("date_demande").toDateTime();
            int idetd = requete.value("id_etudiant").toInt();
            int idclasse = requete.value("id_classe").toInt();
            Demande demande(id,status,date,idetd,idclasse);
            mesdemandes.push_back(demande);
        }
    }
    return mesdemandes;
}
std::string DB::getNomProf(int idprof) {
    QSqlQuery requete;
    requete.prepare("SELECT nom FROM user WHERE id = :idpr");
    requete.bindValue(":idpr",idprof);
    if (requete.exec()) {
        if (requete.next())
            return requete.value("nom").toString().toStdString();
    }
    return "N'existe pas";
}

bool DB::AnnulerDemandeEtd(int idetd,int iddemande) {
    QSqlQuery requete;
    requete.prepare("DELETE FROM demande WHERE id = :id AND id_etudiant = :id2 AND status = 'en_attente'");
    requete.bindValue(":id",iddemande);
    requete.bindValue(":id2",idetd);
    if (requete.exec())
        return true;
    return false;
}

int DB::getIdprofByClass(int idcl) {
    QSqlQuery requete;
    requete.prepare("SELECT prof_id FROM classe WHERE id=:id");
    requete.bindValue(":id",idcl);
    if (requete.exec()) {
        if (requete.next()) {
            int idprof = requete.value("prof_id").toInt();
            return idprof;
        }
    }
    return 0;
}

/*bool DB::addDevoir(Devoir &devoir) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO devoir(titre,consigne,chemin_fichier,id_prof,id_classe,date_poste,deadline"
                    "VALUES (:titre,:consigne,:chemin,:idprof,:idclass,:date,:deadline)");
    requete.bindValue(":titre",QString::fromStdString(devoir.getTitre()));
    requete.bindValue(":consigne",QString::fromStdString(devoir.getConsigne()));
    requete.bindValue(":chemin",QString::fromStdString(devoir.getCheminFichier()));
    requete.bindValue(":idprof",devoir.getIdprof());
    requete.bindValue(":idclass",devoir.getIdclasse());
    requete.bindValue(":date",devoir.getDate());
    requete.bindValue(":deadline",QString::fromStdString(devoir.getdeadline()));
    if (requete.exec())
        return true;
    return false;
}
*/
bool DB::addDevoir(Devoir &devoir) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO devoir (titre, consigne, chemin_fichier, id_prof, id_classe, deadline) "
                    "VALUES (?, ?, ?, ?, ?, ?)");
    requete.addBindValue(QString::fromStdString(devoir.getTitre()));
    requete.addBindValue(QString::fromStdString(devoir.getConsigne()));
    requete.addBindValue(QString::fromStdString(devoir.getCheminFichier()));
    requete.addBindValue(devoir.getIdprof());
    requete.addBindValue(devoir.getIdclasse());
    requete.addBindValue(QString::fromStdString(devoir.getdeadline()));
    if (requete.exec()) {
        return true;
    } else {
        return false;
    }
}

std::vector<Document> DB::getEtdDocuments(int idetd) {
    QSqlQuery requete;
    std::vector<Document> mesdocs;
    requete.prepare("SELECT * FROM document "
                    "INNER JOIN classe_etudiant "
                    "ON document.id_classe = classe_etudiant.classe_id "
                    "WHERE classe_etudiant.etudiant_id = :id");
    requete.bindValue(":id",idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string chemin = requete.value("chemin_fichier").toString().toStdString();
            int idclasse = requete.value("id_classe").toInt();
            int idprof = requete.value("id_prof").toInt();
            QDateTime date = requete.value("date_upload").toDateTime();
            Document document(id,titre,chemin,date,idprof,idclasse);
            mesdocs.push_back(document);
        }
    }
    return mesdocs;
}

std::vector<Video> DB::getEtdVideos(int idetd) {
    QSqlQuery requete;
    std::vector<Video> mesvids;
    requete.prepare("SELECT * FROM video "
                    "INNER JOIN classe_etudiant "
                    "ON video.id_classe = classe_etudiant.classe_id "
                    "WHERE classe_etudiant.etudiant_id = :id");
    requete.bindValue(":id",idetd);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string chemin = requete.value("chemin_fichier").toString().toStdString();
            int idclasse = requete.value("id_classe").toInt();
            int idprof = requete.value("id_prof").toInt();
            QDateTime date = requete.value("date_upload").toDateTime();
            Video video(id,titre,chemin,date,idprof,idclasse);
            mesvids.push_back(video);
        }
    }
    return mesvids;
}

std::vector<Video> DB::getProfVideos(int idprof) {
    std::vector<Video> vect;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM video WHERE id_prof = :id");
    requete.bindValue(":id",idprof);
    if (requete.exec()) {
        while (requete.next()) {
            int id = requete.value("id").toUInt();
            std::string titre = requete.value("titre").toString().toStdString();
            std::string cheminFichier = requete.value("chemin_fichier").toString().toStdString();
            QDateTime date = requete.value("date_upload").toDateTime();
            int idprof = requete.value("id_prof").toUInt();
            int idclasse = requete.value("id_classe").toUInt();
            Video video(id,titre,cheminFichier,date,idprof,idclasse);
            vect.push_back(video);
        }
    }
    return vect;
}

bool DB::AddVideo(Video& video) {
    QSqlQuery requete;
    requete.prepare("INSERT INTO document(titre,chemin_fichier,id_classe,id_prof) VALUES (:titre,:chemin,:idcl,:idpr)");
    requete.bindValue(":titre",QString::fromStdString(video.getTitre()));
    requete.bindValue(":chemin",QString::fromStdString(video.getCheminFichier()));
    requete.bindValue(":idcl",video.getIdclasse());
    requete.bindValue(":idpr",video.getIdprof());
    if (requete.exec()) {
        return true;
    }
    qDebug() << "Echec d'ajout :" << requete.lastError().text();
    return false;
}