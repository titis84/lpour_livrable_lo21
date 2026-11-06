#include "partie.h"
#include "pioche.h"

namespace Codex {
    //*****PARTIE*****

    Partie::Partie() : mode(ModePartie::SOLO), terminee(false), piocheRessource(TypePioche::RESSOURCE), piocheDorure(TypePioche::DORURE) {}
    Partie::~Partie() {
        for (auto j : joueurs) delete j;
        for (auto t : tours) delete t;
        for (auto o : objectifsCommuns) delete o;
    }

    /*void Partie::demarrerPartie(){
        if (joueurs.empty()) {
            throw ManageException("Impossible de démarrer la partie sans joueurs !");
        }

        int numeroTourActuel = 1;
        //Ag : j'ai écrit un début mais en soit jsp si ça c'est pas plutôt dans le main, j'ai peur de m'embrouiller

    };//==============à définir !!==================*/
    //vector<Joueur*> Partie::etablirClassement() const;//==============à définir !!==================
    //void Partie::distribuerCartes();//==============à définir !!==================
    //void Partie::finirPartie();//==============à définir !!==================
    //void Partie::ajouterJoueur(Joueur* j);//==============à définir !!==================
    /*
    ostream& operator<<(ostream& f, CarteObjectif cO) {
        return f;
    }*/

}


