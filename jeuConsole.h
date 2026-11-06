#pragma once
#include "partie.h"

namespace Codex {
    class JeuConsole {
    private:
        Partie* partie;
        int demanderEntierSecurise(int min, int max);
    public:
        JeuConsole();
        ~JeuConsole();
        void lancerPartie();
    };
}
