#pragma once
#include "joueur.h"

namespace Codex {
    //*****TOUR*****

    class Tour {
        int numTourCo;    // Tour de table, dès que ts les joueurs ont joué
        int numTourIndiv; // Tour individuel, dès qu’un joueur à joué et pioché
        Joueur* joueurActuel;

    public:
        Tour(int manche, int action, Joueur* j);
        int getNumeroManche() const;
        int getNumeroActionGlobale() const;
        Joueur* getJoueurActuel() const;
    };
}

