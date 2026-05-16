//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef PFM_CLASSESWIDGET_H
#define PFM_CLASSESWIDGET_H

#include <QWidget>
class User;

QT_BEGIN_NAMESPACE

namespace Ui {
    class ClassesPage;
}

QT_END_NAMESPACE

class ClassesPage: public QWidget {
    Q_OBJECT

public:
    explicit ClassesPage(QWidget *parent = nullptr,User* user = nullptr);
    ~ClassesPage() override;
    void AfficherClasses(User*);
    void RechercherClasse(std::string);

private slots:
    void on_supprimer_clicked();
    void on_rechercher_clicked();
    void on_demandeAcces_clicked();
    void on_ajouter_clicked();
private:
    Ui::ClassesPage *ui;
    User* user;
    int idClasseRecherchee;
};


#endif //PFM_CLASSESWIDGET_H