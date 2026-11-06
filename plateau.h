#pragma once
#include "carte.h"

namespace Codex {
    //*****PLATEAU*****

    class PlateauJoueur {
        vector<CarteJouable*> cartes;
    public:
        PlateauJoueur() = default;
        ~PlateauJoueur() = default; // Gérer la libération si nécessaire

        void ressourcesVisibles() const;
        void objetsVisibles() const;
    };
}

