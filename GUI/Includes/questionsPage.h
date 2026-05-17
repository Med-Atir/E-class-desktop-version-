//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1

#ifndef PFM_QUESTIONS_H
#define PFM_QUESTIONS_H

#include <QWidget>

class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class QuestionsPage;
}

QT_END_NAMESPACE

class QuestionsPage : public QWidget {
    Q_OBJECT

public:
    explicit QuestionsPage(QWidget *parent = nullptr,User* user = nullptr);
    ~QuestionsPage() override;
    void afficherQuestion(User*);
private slots:
    void on_poser_clicked();
private:
    Ui::QuestionsPage *ui;
    User* user;
};


#endif //PFM_QUESTIONS_H
