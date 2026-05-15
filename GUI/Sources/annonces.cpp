//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Annonces.h" resolved

#include "../Includes/annonces.h"
#include "../UI/ui_annonces.h"
Annonces::Annonces(QWidget *parent) : QWidget(parent), ui(new Ui::Annonces) {
    ui->setupUi(this);
}
Annonces::~Annonces() {
    delete ui;
}
