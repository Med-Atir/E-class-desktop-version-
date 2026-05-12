//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _DEVOIR_H_
#define _DEVOIR_H_
#include "Document.h"

class Devoir :public Document {
public:
    Devoir(int id,std::string titre,std::string consigne,std::string deadline,std::string cheminFichier,QDateTime date,const Professeur& prof,const Classe& cl);
    Devoir(const Devoir&);
    ~Devoir();
    std::string getConsigne();
    std::string getdeadline();
    void setConsigne(std::string consigne);
    void setDeadline(std::string deadline);
private:
    std::string consigne;
    std::string deadline;
};

#endif //Document