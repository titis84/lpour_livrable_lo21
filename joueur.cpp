#include "joueur.h"
#include "partie.h"

namespace Codex {
    //*****JOUEUR*****

    Joueur::Joueur(const string& n, int ordre, bool premier)
        : nom(n), score(0), premierJoueur(premier), ordreDeJeu(ordre), objectifPerso(nullptr) {
        if (ordre < 1 || ordre > 4) {
            throw ManageException("L'ordre de jeu d'un joueur doit être compris entre 1 et 4 !");
        }
    }

    string Joueur::getNom() const { return nom; }
    int Joueur::getScore() const { return score; }
    bool Joueur::estPremierJoueur() const { return premierJoueur; }
    int Joueur::getOrdreDeJeu() const { return ordreDeJeu; }
}
