//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1
#ifndef PFM_DEMANDES_H
#define PFM_DEMANDES_H

#include <QWidget>

class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class DemandesPage;
}

QT_END_NAMESPACE

class DemandesPage : public QWidget {
    Q_OBJECT

public:
    explicit DemandesPage(QWidget *parent = nullptr,User* user = nullptr);

    ~DemandesPage() override;

private:
    Ui::DemandesPage *ui;
    User* user;
};


#endif //PFM_DEMANDESWIDGETS_H
