//Created by Mohammed atir on 11/05/2026
//IA S4 / Groupe 1
#ifndef _DB_H_
#define _DB_H_

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>

class Demande;
class Document;
class Question;
class Annonce;
class Devoir;
class Classe;
class Professeur;
class Etudiant;
class User;
class DB {
private:
    QSqlDatabase db;

public:
    DB();
    ~DB();
    bool connect(const QString& dbName);
    void disconnect();
    static bool AddClasse(Classe& cl,int idprof);
    static Professeur* getProf(int idProf);
    static Classe* getClasse(int idClasse);
    static Etudiant* getEtudiant(int idEtd);
    static bool DelClasse(Classe &cl);
    static std::vector<Demande> getDemandes(int idprof);
    static std::vector<Devoir> getEtudiantDevoirs(int idetd);
    static void addQuestion(Question &q);
    static std::vector<Annonce> getEtudiantAnnonces(int idetd);
    static std::vector<Classe> getEtudiantclasse(int idetd);
    static std::vector<Classe> getProfclasse(int idprof);
    static bool AccepteDemande(Demande&);
    static bool RejetDemande(Demande&);
    static bool AddAnnoce(Annonce&);
    static bool DelAnnonce(Annonce&);
    static std::vector<Annonce> getProfAnnonces(int idprof);
    static bool AddDocument(Document& document,Classe&);
    static bool DelDocument(Document&);
    static bool DelDevoir(Devoir&);
    static std::vector<Document> getDocuments(Classe&);
    static std::vector<Devoir> getProfDevoirs(int idprof);
    static std::vector<Document> getProfDocuments(int idprof);
    static std::vector<Question> getProfQuestions(int idprof);
    static bool AddReponse(Question& q,std::string reponse);
    static Classe* RechercherClasse(std::string code);
    static bool InscrireClasse(int idetd,Classe&);
    static std::vector<Question> getEtudiantQuestions(int idetd);
    static User* Login(const std::string& email, const std::string& password);
    static bool Signup(const std::string& email,const std::string& nom,const std::string& password,const std::string& role);
    static std::string hasherPass(const std::string& pass);
    static bool etdInscrit(int idetd,int idclasee);
    static bool demandeDejaAtt(int idetd,int idclasse);
    static bool delAccount(int iduser);
    static bool changerNom(int iduser,std::string nom);
    static bool changerEmail(int iduser,std::string email);
    static std::vector<Demande> getDemandesEtd(int idetd);
    static std::string getNomProf(int);
    static bool AnnulerDemandeEtd(int,int);
};

#endif // DB_H