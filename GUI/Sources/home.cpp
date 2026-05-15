//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Home.h" resolved

#include "../Includes/home.h"
#include "../UI/ui_home.h"


Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);
}

Home::~Home() {
    delete ui;
}
