//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#ifndef _DASHBOARDPROF_H_
#define _DASHBOARDPROF_H_
#include "classes.h"
#include "annonces.h"
#include "demandes.h"
#include "devoirs.h"
#include "home.h"
#include "parametres.h"
#include "questions.h"
#include <QMainWindow>

class User;
QT_BEGIN_NAMESPACE
namespace Ui { class Dashboard; }
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
    void setUser(User*);
    void setUpUI();

private slots:
    void on_btnDeconnecter_clicked();
    void on_home_clicked();
    void on_mesclasses_clicked();
    void on_mesannonces_clicked();
    void on_mesdevoirs_clicked();
    void on_mesquestion_clicked();
    void on_mesdemandes_clicked();
    void on_parametre_clicked();

private:
    Ui::Dashboard *ui;
    User* user;
    Classes *classesPage;
    Annonces* annoncesPage;
    Demandes* demandesPage;
    Devoirs* devoirsPage;
    Home* homePage;
    Parametres* parametresPage;
    Questions* questionsPage;
};
#endif // _DASHBOARD_H_