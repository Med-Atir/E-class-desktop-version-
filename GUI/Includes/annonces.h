//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#ifndef PFM_ANNONCES_H
#define PFM_ANNONCES_H
#include <QWidget>
QT_BEGIN_NAMESPACE

namespace Ui {
    class Annonces;
}

QT_END_NAMESPACE

class Annonces : public QWidget {
    Q_OBJECT

public:
    explicit Annonces(QWidget *parent = nullptr);

    ~Annonces() override;

private:
    Ui::Annonces *ui;
};


#endif //PFM_ANNONCES_H
