// Created by Atir Mohammed on 22-Apr-26
//CNE: K133125030
//Filiere: IA/4 G:1
#include <stdexcept>
#include "../Includes/Vect.h"
template <typename T>
Vect<T>::Vect(int capInitiale) {
    capacite = capInitiale;
    tailleActuelle = 0;
    tableau = new T[capacite];
}
template <typename T>
Vect<T>::~Vect() {
    delete[] tableau;
}
template <typename T>
Vect<T>::Vect(const Vect& autre) {
    capacite = autre.capacite;
    tailleActuelle = autre.tailleActuelle;
    tableau = new T[capacite];
    for (int i = 0; i < tailleActuelle; i++) {
        tableau[i] = autre.tableau[i];
    }
}
template <typename T>
Vect<T>& Vect<T>::operator=(const Vect& autre) {
    if (this != &autre) {
        delete[] tableau;

        capacite = autre.capacite;
        tailleActuelle = autre.tailleActuelle;
        tableau = new T[capacite];

        for (int i = 0; i < tailleActuelle; i++) {
            tableau[i] = autre.tableau[i];
        }
    }
    return *this;
}
template <typename T>
void Vect<T>::redimensionner() {
    capacite *= 2;
    T* nouveauTableau = new T[capacite];
    for (int i = 0; i < tailleActuelle; i++) {
        nouveauTableau[i] = tableau[i];
    }

    delete[] tableau;
    tableau = nouveauTableau;
}

template <typename T>
void Vect<T>::ajouter(const T& element) {
    if (tailleActuelle == capacite) {
        redimensionner();
    }
    tableau[tailleActuelle] = element;
    tailleActuelle++;
}

template <typename T>
void Vect<T>::supprimer(int index) {
    if (index < 0 || index >= tailleActuelle) {
        throw std::out_of_range("Index hors limites lors de la suppression !");
    }
    for (int i = index; i < tailleActuelle - 1; i++) {
        tableau[i] = tableau[i + 1];
    }
    tailleActuelle--;
}

template <typename T>
T& Vect<T>::obtenir(int index) const {
    if (index < 0 || index >= tailleActuelle) {
        throw std::out_of_range("Index hors limites !");
    }
    return tableau[index];
}

template <typename T>
int Vect<T>::taille() const {
    return tailleActuelle;
}

template <typename T>
bool Vect<T>::estVide() const {
    return tailleActuelle == 0;
}

template <typename T>
void Vect<T>::vider() {
    tailleActuelle = 0;
}