#pragma once
#include "carte.h"

namespace Codex {
    //*****MAIN*****

    class Main {
        vector<CarteJouable*> cartes; // 0 à 3 cartes
    public:
        Main() = default;
        ~Main() = default;
        const vector<CarteJouable*>& getCartes() const;
        void ajouterCarte(CarteJouable* c);//après avoir pioché, ajoute la carte à la main
        CarteJouable* retirerCarte(int index); //retire carte de la main avant de la poser sur le plateau
    };
}

