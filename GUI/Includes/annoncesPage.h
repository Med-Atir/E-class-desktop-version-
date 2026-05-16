//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#ifndef PFM_ANNONCES_H
#define PFM_ANNONCES_H
#include <QWidget>
class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class AnnoncesPage;
}

QT_END_NAMESPACE

class AnnoncesPage : public QWidget {
    Q_OBJECT

public:
    explicit AnnoncesPage(QWidget *parent = nullptr,User* user = nullptr);
    ~AnnoncesPage() override;
    void afficherAnnonces(User* user);
private slots:
    void on_posterAnnonce_clicked();
    void on_supprimerAnnonce_clicked();
private:
    Ui::AnnoncesPage *ui;
    User* user;
};

#endif //PFM_ANNONCES_H
