//Created by Mohammed atir on 13/05/2026
//IA S4 / Groupe 1
#include "../Includes/loginwindow.h"
#include "../UI/ui_loginwindow.h"
#include "../Includes/dashboard.h"
#include "../Includes/signupwindow.h"
#include "../Database/Db.h"
#include "../Includes/Professeur.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->email->setPlaceholderText("Veuillez enter votre email ici....");
    ui->password->setPlaceholderText("Veuillez enter votre mot de passe ici....");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::on_login_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();
    User* user = DB::Login(email.toStdString(),password.toStdString());
    if (user != nullptr) {
            QMessageBox::information(this,"Succes","Mrhba bik");
            Dashboard *dashboard = new Dashboard();
            dashboard->setAttribute(Qt::WA_DeleteOnClose);
            dashboard->setUser(user);
            dashboard->showMaximized();
            this->close();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Email ou mot de passe incorrect.");
    }
}
void LoginWindow::on_signup_clicked()
{
    SignupWindow *signup = new SignupWindow();
    signup->setAttribute(Qt::WA_DeleteOnClose);
    signup->showMaximized();
    this->close();
}