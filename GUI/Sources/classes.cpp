//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#include "../Includes/classes.h"
#include "../UI/ui_classes.h"

Classes::Classes(QWidget *parent) : QWidget(parent), ui(new Ui::Classes) {
    ui->setupUi(this);
}
Classes::~Classes() {
    delete ui;
}
