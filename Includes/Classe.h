//Created by Mohammed atir on 12/05/2026
//IA S4 / Groupe 1

#ifndef _CLASSE_H_
#define _CLASSE_H_

class Classe {
public:
    int getId();
    std::string getTitre();
    std::string getCode();
    std::string getDescription();
    void setId(int id);
    void setTitre(std::string Titre);
    void setCode(std::string Code);
    void setDescription(std::string Description);
private:
    int Id;
    std::string Titre;
    std::string Code;
    std::string Description;
};

#endif //Cours
