#pragma once
#include "carte.h"

namespace Codex {
    //*****TYBOR*****

    class Tybor {
        int niveau; // 1, 2 ou 3
        int score;
        vector<vector<CarteJouable*>> plateau; //vecteur de vecteurs pour gérer la plateau spécifique à Tybor
    public:
        Tybor(int niv);
        int getNiveau() const;
        int getScore() const;
        void prendreCarte();
    };
}

