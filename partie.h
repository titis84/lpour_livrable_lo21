#pragma once
#include "joueur.h"
#include "tour.h"
#include "carte.h"
#include "pioche.h"

//*****PARTIE*****

namespace Codex {

    // classe pour gérer les exceptions
    class ManageException {
    private:
        string info;
    public:
        string getInfo() const { return info; }
        ManageException(const string& i) : info(i) {}
    };

    //caractéristiques
    enum class ModePartie { MULTI, SOLO };

    class Partie {
        ModePartie mode;
        bool terminee;
        vector<Joueur*> joueurs;
        vector<Tour*> tours;
        vector<CarteObjectif*> objectifsCommuns;
        Pioche piocheRessource;
        Pioche piocheDorure;
    public:
        Partie();
        ~Partie();
        vector<Joueur*> etablirClassement() const;
        void distribuerCartes();
        void finirPartie();
        void ajouterJoueur(Joueur* j);

    };
}

