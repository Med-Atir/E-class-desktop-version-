//Created by Mohammed atir on 13/05/2026
//IA S4 / Groupe 1
#ifndef _SIGNWINDOW_H_
#define _SIGNWINDOW_H_
#include <QMainWindow>
#include <qtmetamacros.h>
#include "../../Includes/User.h"
QT_BEGIN_NAMESPACE
namespace Ui { class signupwindow; }
QT_END_NAMESPACE

class SignupWindow : public QMainWindow
{
    Q_OBJECT

public:
    SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void on_signup_clicked(); 
    void on_login_clicked();

private:
    Ui::signupwindow *ui;
};
#endif