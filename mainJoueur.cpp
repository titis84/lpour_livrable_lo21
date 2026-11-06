
#include "mainJoueur.h"
#include "partie.h"
#include "carte.h"

namespace Codex {
    //*****MAIN*****

    const vector<CarteJouable*>& Main::getCartes() const { return cartes; }

    void Main::ajouterCarte(CarteJouable* c) {
        if (c == nullptr) {
            throw ManageException("Impossible d'ajouter une carte nulle dans la main !");
        }
        if (cartes.size() >= 3) {  //max 3 cartes en main
            throw ManageException("La main est déjà pleine !");
        }
        cartes.push_back(c);
    }


    CarteJouable* Main::retirerCarte(int index) { //le joueur indique la combientième carte il veut retirer de sa main, d'où le int index
        if (index < 0 || index >= static_cast<int>(cartes.size())) {
            throw ManageException("Index de carte invalide dans la main !");
        }
        CarteJouable* c = cartes[index]; // récupère le pointeur avant de l'effacer
        cartes.erase(cartes.begin() + index); // supprime la carte de la main
        return c; //renvoie la carte pour pouvoir la jouer sur le plateau
    }
}
