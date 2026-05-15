//Created by Mohammed atir on 13/05/2026
//IA S4 / Groupe 1
#include <QApplication>
#include "GUI/Includes/loginwindow.h"
#include "GUI/Includes/signupwindow.h"
#include "Database/Db.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DB baseDeDonnees;
    if (!baseDeDonnees.connect("C:/Users/simoa/Documents/Semestre4/PFM/Database/pfm.db")) {
        return -1;
    }
    SignupWindow s;
    s.showMaximized();

    return a.exec();
}