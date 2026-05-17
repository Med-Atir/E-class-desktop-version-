//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1

#ifndef PFM_PARAMETRES_H
#define PFM_PARAMETRES_H

#include <QWidget>
class User;

QT_BEGIN_NAMESPACE

namespace Ui {
    class Parametres;
}

QT_END_NAMESPACE

class Parametres : public QWidget {
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr);
    ~Parametres() override;
    void setUser(User* user);
private slots:
    void on_changernom_clicked();
    void on_supprimercompte_clicked();
    void on_changeremail_clicked();
    signals:
    void demandeDeconnection();
private:
    Ui::Parametres *ui;
    User* user;
};


#endif //PFM_PARAMETRES_H
