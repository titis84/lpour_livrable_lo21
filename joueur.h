#pragma once
#include <string>
#include "carte.h"
#include "plateau.h"
#include "mainJoueur.h"

namespace Codex {
    //*****JOUEUR*****

    class Joueur {
        string nom;
        int score;
        bool premierJoueur;
        int ordreDeJeu;
        PlateauJoueur plateau;
        Main main;
        CarteObjectif* objectifPerso;
    public:
        Joueur(const string& n, int ordre, bool premier = false);
        string getNom() const;
        int getScore() const;
        bool estPremierJoueur() const;
        int getOrdreDeJeu() const;
    };
}
