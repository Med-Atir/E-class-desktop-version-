//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1

#ifndef PFM_PARAMETRES_H
#define PFM_PARAMETRES_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Parametres;
}

QT_END_NAMESPACE

class Parametres : public QWidget {
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr);

    ~Parametres() override;

private:
    Ui::Parametres *ui;
};


#endif //PFM_PARAMETRES_H
