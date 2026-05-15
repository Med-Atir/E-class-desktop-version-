//Created by Mohammed atir on 13/05/2026
//IA S4 / Groupe 1

#ifndef _LOGINWINDOW_H_
#define _LOGINWINDOW_H_

#include <QMainWindow>
#include <qtmetamacros.h>
#include "../../Includes/User.h"
QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_login_clicked();
    void on_signup_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
