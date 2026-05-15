//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Devoirs.h" resolved

#include "../Includes/devoirs.h"
#include "../UI/ui_devoirs.h"


Devoirs::Devoirs(QWidget *parent) : QWidget(parent), ui(new Ui::Devoirs) {
    ui->setupUi(this);
}

Devoirs::~Devoirs() {
    delete ui;
}
