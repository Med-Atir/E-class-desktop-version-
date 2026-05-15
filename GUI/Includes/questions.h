//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

#ifndef PFM_QUESTIONS_H
#define PFM_QUESTIONS_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Questions;
}

QT_END_NAMESPACE

class Questions : public QWidget {
    Q_OBJECT

public:
    explicit Questions(QWidget *parent = nullptr);

    ~Questions() override;

private:
    Ui::Questions *ui;
};


#endif //PFM_QUESTIONS_H
