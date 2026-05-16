//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/parametres.h"
#include "../UI/ui_parametres.h"


Parametres::Parametres(QWidget *parent) : QWidget(parent), ui(new Ui::Parametres) {
    ui->setupUi(this);
}

Parametres::~Parametres() {
    delete ui;
}
