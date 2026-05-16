//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#include "../Includes/questionsPage.h"
#include "../UI/ui_questionsPage.h"
#include "../../Includes/User.h"

QuestionsPage::QuestionsPage(QWidget *parent,User* user) : QWidget(parent), ui(new Ui::QuestionsPage) {
    ui->setupUi(this);
}

QuestionsPage::~QuestionsPage() {
    delete ui;
}
