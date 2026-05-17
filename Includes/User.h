// Created by Atir Mohammed on 18-Apr-26
//CNE: K133125030
//Filiere: IA/4 G:1
# ifndef _USER_H_
#define _USER_H_
#include <string>
class User {
public:
    User();
    User(int Id,std::string Nom,std::string Email);
    User(const User& p);
    virtual  ~User();//j'ai mette tous les getters comme constante pour que je peux manupiler les classes contants aussi
    User& operator=(const User& p);
    std::string getNom() const;
    std::string getEmail() const;
    void setNom(std::string name) ;
    void setEmail(std::string email) ;
    int getId() const;
    void setId(int id);
    bool DeleteAcc();
    bool changerNom(std::string);
    bool changeremail(std::string);
protected:
    int Id;
    std::string Nom;
    std::string Email;
};

#endif