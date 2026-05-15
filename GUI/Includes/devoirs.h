//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 15/05/2026.
//

#ifndef PFM_DEVOIRS_H
#define PFM_DEVOIRS_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Devoirs;
}

QT_END_NAMESPACE

class Devoirs : public QWidget {
    Q_OBJECT

public:
    explicit Devoirs(QWidget *parent = nullptr);

    ~Devoirs() override;

private:
    Ui::Devoirs *ui;
};


#endif //PFM_DEVOIRS_H
