//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef PFM_CLASSESWIDGET_H
#define PFM_CLASSESWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Classes;
}

QT_END_NAMESPACE

class Classes: public QWidget {
    Q_OBJECT

public:
    explicit Classes(QWidget *parent = nullptr);

    ~Classes() override;

private:
    Ui::Classes *ui;
};


#endif //PFM_CLASSESWIDGET_H
