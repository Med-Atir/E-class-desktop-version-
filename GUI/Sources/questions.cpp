//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Questions.h" resolved

#include "../Includes/questions.h"
#include "../UI/ui_questions.h"


Questions::Questions(QWidget *parent) : QWidget(parent), ui(new Ui::Questions) {
    ui->setupUi(this);
}

Questions::~Questions() {
    delete ui;
}
