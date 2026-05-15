//Created by Mohammed atir on 13/05/2026
//IA S4 / Groupe 1
#include "../Includes/signupwindow.h"
#include "../UI/ui_signupwindow.h"
#include "../Includes/loginwindow.h"
#include "../../Database/Db.h"
#include "../../Includes/Professeur.h"
#include "../../Includes/Etudiant.h"
#include <QMessageBox>

SignupWindow::SignupWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signupwindow)
{
    ui->setupUi(this);
    ui->etudiant->setChecked(true);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->email->setPlaceholderText("Veuillez enter votre email ici....");
    ui->password->setPlaceholderText("Veuillez enter votre mot de passe ici....");
    ui->nom->setPlaceholderText("Veuillez enter votre nom ici....");
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_signup_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();
    QString nom = ui->nom->text();
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }
    QString role = "";
    if (ui->professeur->isChecked()) {
        role = "professeur";
    } else if (ui->etudiant->isChecked()) {
        role = "etudiant";
    }
    bool login = DB::Signup(email.toStdString(),nom.toStdString(),password.toStdString(),role.toStdString());
    if (login) {
        QMessageBox::information(this, "Succes", "Compte cree avec succes ! mr7ba bik.");
        on_login_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de creer le compte : " );
    }
}

void SignupWindow::on_login_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->showMaximized();
    this->close();
}