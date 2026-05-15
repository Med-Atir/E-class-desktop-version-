//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Parametres.h" resolved

#include "../Includes/parametres.h"
#include "../UI/ui_parametres.h"


Parametres::Parametres(QWidget *parent) : QWidget(parent), ui(new Ui::Parametres) {
    ui->setupUi(this);
}

Parametres::~Parametres() {
    delete ui;
}
