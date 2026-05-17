//IA S4 / Groupe 1

#ifndef PFM_HOME_H
#define PFM_HOME_H

#include <QWidget>

class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class Home;
}

QT_END_NAMESPACE

class Home : public QWidget {
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr,User* user = nullptr);
    ~Home() override;
    void afficherStats(User* currentUser);

private:
    Ui::Home *ui;
    User* user;
};


#endif //PFM_HOME_H
