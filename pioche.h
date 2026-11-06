#pragma once
#include "carte.h"

namespace Codex {

    //caractéristiques
    enum class TypePioche { RESSOURCE, DORURE };

    //*****PIOCHE*****

    class Pioche {
        TypePioche typePioche;
        vector<CarteJouable*> cartesCachees;   //Le paquet face cachée
        vector<CarteJouable*> cartesVisibles;  //Les 2 cartes face visible
    public:
        Pioche(TypePioche tp);

        CarteJouable* piocherCarteCachee();
        void remplirDepuisPioche(Pioche& autrePioche);
        bool estVide() const;
        void prendreCarteVisible(CarteJouable* carte);
    };
}

