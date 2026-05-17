//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#ifndef PFM_DEVOIRS_H
#define PFM_DEVOIRS_H

#include <QWidget>

class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class DevoirsPage;
}

QT_END_NAMESPACE

class DevoirsPage : public QWidget {
    Q_OBJECT

public:
    explicit DevoirsPage(QWidget *parent = nullptr,User* user = nullptr);
    ~DevoirsPage() override;
    void afficherFiles(User* user);
private slots:
    void on_poster_clicked();
    void on_choisirFichier_clicked();

private:
    Ui::DevoirsPage *ui;
    User* user;
};


#endif //PFM_DEVOIRS_H
