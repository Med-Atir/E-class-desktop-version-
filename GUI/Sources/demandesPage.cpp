//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#include "../Includes/demandesPage.h"
#include "../UI/ui_demandesPage.h"
#include "../../Includes/User.h"
DemandesPage::DemandesPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::DemandesPage) {
    ui->setupUi(this);
}

DemandesPage::~DemandesPage() {
    delete ui;
}