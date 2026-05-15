//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

#ifndef PFM_HOME_H
#define PFM_HOME_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Home;
}

QT_END_NAMESPACE

class Home : public QWidget {
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);

    ~Home() override;

private:
    Ui::Home *ui;
};


#endif //PFM_HOME_H
