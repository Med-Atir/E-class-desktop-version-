//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/devoirsPage.h"
#include "../UI/ui_devoirsPage.h"
#include "../../Includes/User.h"

DevoirsPage::DevoirsPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::DevoirsPage) {
    ui->setupUi(this);
}

DevoirsPage::~DevoirsPage() {
    delete ui;
}
