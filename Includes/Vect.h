// Created by Atir Mohammed on 22-Apr-26
//CNE: K133125030
//Filiere: IA/4 G:1
#ifndef _VECT_H_
#define _VECT_H_

template <typename T>
class Vect {
private:
    T* tableau;
    int capacite;
    int tailleActuelle;
    void redimensionner();
public:
    Vect(int capInitiale = 10);
    ~Vect();
    Vect(const Vect& autre);
    Vect& operator=(const Vect& autre);
    void ajouter(const T& element);
    void supprimer(int index);
    T& obtenir(int index) const;
    int taille() const;
    bool estVide() const;
    void vider();
};

#endif