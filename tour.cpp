#include "tour.h"
#include "partie.h"

namespace Codex {
    //*****TOUR*****

    Tour::Tour(int manche, int action, Joueur* j)
        : numTourCo(manche), numTourIndiv(action), joueurActuel(j) {
        if (manche < 1 || action < 1) {
            throw ManageException("Les numéros de manche et d'action doivent commencer à 1 !");
        }
    }

    int Tour::getNumeroManche() const { return numTourCo; }
    int Tour::getNumeroActionGlobale() const { return numTourIndiv; }
    Joueur* Tour::getJoueurActuel() const { return joueurActuel; }

}
