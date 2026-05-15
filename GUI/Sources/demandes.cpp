//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#include "../Includes/demandes.h"
#include "../UI/ui_demandes.h"

Demandes::Demandes(QWidget *parent) : QWidget(parent), ui(new Ui::Demandes) {
    ui->setupUi(this);
}

Demandes::~Demandes() {
    delete ui;
}