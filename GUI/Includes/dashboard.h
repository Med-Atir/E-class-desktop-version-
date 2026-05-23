//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#ifndef _DASHBOARDPROF_H_
#define _DASHBOARDPROF_H_
#include "classesPage.h"
#include "annoncesPage.h"
#include "demandesPage.h"
#include "devoirsPage.h"
#include "home.h"
#include "parametres.h"
#include "questionsPage.h"
#include "videoPage.h"
#include <QMainWindow>

class User;
QT_BEGIN_NAMESPACE
namespace Ui { class Dashboard; }
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(User* user,QWidget *parent = nullptr);
    ~Dashboard();
    void setUser(User*);
    void setUpUI();

private slots:
    void on_btnDeconnecter_clicked();
    void on_home_clicked();
    void on_mesclasses_clicked();
    void on_mesannonces_clicked();
    void on_mesdevoirs_clicked();
    void on_mesquestions_clicked();
    void on_mesdemandes_clicked();
    void on_parametre_clicked();
    void on_video_clicked();

private:
    Ui::Dashboard *ui;
    User* user;
    ClassesPage *classesPage;
    AnnoncesPage* annoncesPage;
    DemandesPage* demandesPage;
    DevoirsPage* devoirsPage;
    Home* homePage;
    Parametres* parametresPage;
    QuestionsPage* questionsPage;
    VideoPage* videoPage;
};
#endif // _DASHBOARD_H_