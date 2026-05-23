//Created by Mohammed atir on 15/05/2026
//IA S4 / Groupe 1
#ifndef PFM_VIDEOS_H
#define PFM_VIDEOS_H

#include <QWidget>

class User;
QT_BEGIN_NAMESPACE

namespace Ui {
    class VideoPage;
}

QT_END_NAMESPACE

class VideoPage : public QWidget {
    Q_OBJECT

public:
    explicit VideoPage(QWidget *parent = nullptr,User* user = nullptr);
    ~VideoPage() override;
    void afficherVids(User* user);
private slots:
    void on_poster_clicked();
    void on_choisirFichier_clicked();

private:
    Ui::VideoPage *ui;
    User* user;
};


#endif //PFM_DEVOIRS_H