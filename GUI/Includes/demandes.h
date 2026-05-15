//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#ifndef PFM_DEMANDES_H
#define PFM_DEMANDES_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Demandes;
}

QT_END_NAMESPACE

class Demandes : public QWidget {
    Q_OBJECT

public:
    explicit Demandes(QWidget *parent = nullptr);

    ~Demandes() override;

private:
    Ui::Demandes *ui;
};


#endif //PFM_DEMANDESWIDGETS_H
