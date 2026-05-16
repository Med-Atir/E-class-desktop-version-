//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/home.h"
#include "../UI/ui_home.h"
#include "../../Includes/User.h"

Home::Home(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);
}

Home::~Home() {
    delete ui;
}
