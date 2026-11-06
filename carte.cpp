#include "carte.h"
#include "partie.h"

using namespace std;
namespace Codex {
    //définir les couleurs pour la console
    const string ROUGE = "\033[31m";
    const string VERT = "\033[32m";
    const string BLEU = "\033[34m";
    const string VIOLET = "\033[35m";
    const string DORURE = "\033[38;5;220m";
    const string RESET = "\033[0m";

    string couleurRessource(Regne r) {
        switch (r) {
        case ANIMAL:
            return BLEU;
        case VEGETAL:
            return VERT;
        case ENTOMOLOGIQUE:
            return VIOLET;
        case FONGIQUE:
            return ROUGE;
        default:
            return RESET;
        }
    }

    //enumeration
    ostream& operator<<(ostream& f, Regne r) {
        switch (r) {
        case VEGETAL:       return f << VERT << "V" << RESET;
        case ANIMAL:        return f << BLEU << "A" << RESET;
        case FONGIQUE:      return f << ROUGE << "F" << RESET;
        case ENTOMOLOGIQUE: return f << VIOLET << "E" << RESET;
        default:            return f << "?";
        }
    }

    ostream& operator<<(ostream& f, Objet o) {
        switch (o) {
        case PLUME:     return f << "Plu";
        case ENCRIER:   return f << "Enc";
        case PARCHEMIN: return f << "Par";
        default:        return f << "?";
        }
    }
    ostream& operator<<(ostream& f, TypePoint p) {
        switch (p) {
        case NB_ANGLES_RECOUVERTS: return f << "AR";
        case NB_OBJETS_VISIBLES: return f << "OV";
        default: return f;
        }
    }

    //*****COIN*****

    bool Coin::getEstVisible() const { return estVisible; }
    void Coin::setEstVisible(bool v) { estVisible = v; } //à déterminer ultérieurement selon nos besoins : mettre en private et ajouter plateau en amie ?

    bool Coin::estInexistant() const { return holds_alternative<Inexistant>(contenu); }
    bool Coin::estVide() const { return holds_alternative<Vide>(contenu); }
    bool Coin::hasRessource() const { return holds_alternative<Regne>(contenu); }
    bool Coin::hasObjet() const { return holds_alternative<Objet>(contenu); }

    Regne Coin::getRessource() const {
        if (!hasRessource()) throw ManageException("Ce coin ne contient pas de ressource !");
        return get<Regne>(contenu);
    }

    Objet Coin::getObjet() const {
        if (!hasObjet()) throw ManageException("Ce coin ne contient pas d'objet !");
        return get<Objet>(contenu);
    }

    ostream& operator<<(ostream& f, const Coin& coin) {
        const auto& contenu = coin.getContenu();

        if (const auto* r = get_if<Regne>(&contenu)) {
            f << " " << *r << " ";
        }
        else if (const auto* o = get_if<Objet>(&contenu)) {
            f << *o;
        }
        else f << "   ";
        return f;
    }


    //*****CARTE*****

    FaceCarte Carte::getFace() const { return face; }
    void Carte::retourner() {
        face = (face == FaceCarte::RECTO) ? FaceCarte::VERSO : FaceCarte::RECTO;
    }

    //*****CARTE JOUABLE*****

    //Constructeur avec coins détaillés
    CarteJouable::CarteJouable(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, FaceCarte f)
        : Carte(f), regne(r), coinsRecto{ hg, hd, bg, bd }, points(p) {
        if (p < 0) throw ManageException("Les points négatifs n'existent pas dans le jeu !");
    }

    //Constructeur avec array
    CarteJouable::CarteJouable(Regne r, const array<Coin, 4>& cRecto, int p, FaceCarte f)
        : Carte(f), regne(r), coinsRecto(cRecto), points(p) {
        if (p < 0) throw ManageException("Les points négatifs n'existent pas dans le jeu !");
    }
    //à voir si on garde les deux constructeurs ou qu'un seul

    Regne CarteJouable::getRegne() const { return regne; }
    int CarteJouable::getPoints() const {
        return (face == FaceCarte::RECTO) ? points : 0;
    }

    const array<Coin, 4>& CarteJouable::getCoinsActuels() const {
        return (face == FaceCarte::RECTO) ? coinsRecto : coinsVerso;
    }
    //quid poserCarte ??

    ostream& operator<<(ostream& f, const CarteJouable& cj) {
        string couleur = couleurRessource(cj.getRegne());

        if (cj.getFace() == RECTO) {
            f << couleur << " --------------- \n"
                << "|" << RESET << cj.getCoinsActuels()[HAUT_GAUCHE] << couleur;
            (!cj.getCoinsActuels()[HAUT_GAUCHE].estInexistant()) ? f << "|" : f << " ";
            f << "   " << RESET;
            if (cj.getPoints() != 0) {
                f << cj.getPoints();
            }
            else f << " ";
            f << couleur << "   ";
            (!cj.getCoinsActuels()[HAUT_DROIT].estInexistant()) ? f << "|" : f << " ";
            f << RESET << cj.getCoinsActuels()[HAUT_DROIT] << couleur << "|" << "\n"
                << "|---         ---|" << "\n"
                << "|" << RESET << cj.getCoinsActuels()[BAS_GAUCHE] << couleur;
            (!cj.getCoinsActuels()[BAS_GAUCHE].estInexistant()) ? f << "|" : f << " ";
            f << "       ";
            (!cj.getCoinsActuels()[BAS_DROIT].estInexistant()) ? f << "|" : f << " ";
            f << RESET << cj.getCoinsActuels()[BAS_DROIT] << couleur << "|" << "\n"
                << " --------------- " << RESET;
        }
        else {
            f << couleur << " --------------- \n"
                << "|   |" << "       "
                << "|   |" << "\n"
                << "|---    " << cj.getRegne() << couleur << "    ---| " << "\n"
                << "|   |" << "       "
                << "|   |" << "\n"
                << " --------------- " << RESET;
        }

        return f;
    }

    //*****CARTE RESSOURCE*****

    CarteRessource::CarteRessource(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, FaceCarte f)
        : CarteJouable(r, hg, hd, bg, bd, p, f) {
    }
    CarteRessource::CarteRessource(Regne r, int p, const array<Coin, 4>& cRecto, FaceCarte f)
        : CarteJouable(r, cRecto, p, f) {
    }
    //quid poserCarte ??

    //*****CARTE DORURE*****

    CarteDorure::CarteDorure(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, const vector<Regne>& cond, TypePoint tp, FaceCarte f)
        : CarteJouable(r, hg, hd, bg, bd, p, f), conditions(cond), typePoint(tp) {
    }
    CarteDorure::CarteDorure(Regne r, const std::array<Coin, 4>& cRecto, int p, const vector<Regne>& cond, TypePoint tp, FaceCarte f)
        : CarteJouable(r, cRecto, p, f), conditions(cond), typePoint(tp) {
    }

    const vector<Regne>& CarteDorure::getConditions() const { return conditions; }
    TypePoint CarteDorure::getTypePoint() const { return typePoint; }
    //quid poserCarte ??

    ostream& operator<<(ostream& f, const CarteDorure& cd) {
        string couleur = couleurRessource(cd.getRegne());

        if (cd.getFace() == RECTO) {
            f << couleur << " --------------- \n"
                << "|" << RESET << cd.getCoinsActuels()[HAUT_GAUCHE] << DORURE;
            (!cd.getCoinsActuels()[HAUT_GAUCHE].estInexistant()) ? f << "|" : f << " ";
            f << "  " << RESET;
            if (cd.getPoints() != 0) {
                f << cd.getPoints();
                if (cd.getTypePoint() != FLAT) {
                    f << cd.getTypePoint();
                }
                else f << "  ";
            }
            else f << " ";
            f << DORURE << "  ";
            (!cd.getCoinsActuels()[HAUT_DROIT].estInexistant()) ? f << "|" : f << " ";
            f << RESET << cd.getCoinsActuels()[HAUT_DROIT] << couleur << "|" << "\n"
                << "|" << DORURE << "---         ---" << couleur << "|" << "\n"
                << "|" << RESET << cd.getCoinsActuels()[BAS_GAUCHE] << DORURE;
            (!cd.getCoinsActuels()[BAS_GAUCHE].estInexistant()) ? f << "|" : f << " ";

            vector<Regne> cond = cd.getConditions();
            switch (cond.size()) {
            case 0: f << "       "; break;
            case 1: f << "   " << cond.at(0) << "   "; break;
            case 2: f << "  " << cond.at(0) << cond.at(1) << "   "; break;
            case 3: f << "  " << cond.at(0) << cond.at(1) << cond.at(2) << "  "; break;
            case 4: f << " " << cond.at(0) << cond.at(1) << cond.at(2) << cond.at(3) << "  "; break;
            case 5: f << " " << cond.at(0) << cond.at(1) << cond.at(2) << cond.at(3) << cond.at(4) << " "; break;
            }
            f << DORURE;
            (!cd.getCoinsActuels()[HAUT_GAUCHE].estInexistant()) ? f << "|" : f << " ";
            f << RESET << cd.getCoinsActuels()[BAS_DROIT] << couleur << "|" << "\n"
                << " --------------- " << RESET;
        }
        else {
            f << couleur << " --------------- \n"
                << "|   " << DORURE << "|" << "       "
                << "|   " << couleur << "|" << "\n"
                << "|" << DORURE << "---    " << cd.getRegne() << DORURE << "    ---" << couleur << "| " << "\n"
                << "|   " << DORURE << "|" << "       "
                << "|   " << couleur << "|" << "\n"
                << " --------------- " << RESET;
        }

        return f;
    }

    //*****CARTE DEPART*****

    CarteDepart::CarteDepart(const array<Coin, 4>& cRecto, const array<Coin, 4>& cVerso, const vector<Regne>& resCentre, FaceCarte f)
        : Carte(f), coinsRecto(cRecto), coinsVerso(cVerso), ressourcesCentreRecto(resCentre) {
    };

    const array<Coin, 4>& CarteDepart::getCoinsRecto() const { return coinsRecto; }
    const array<Coin, 4>& CarteDepart::getCoinsVerso() const { return coinsVerso; }

    const array<Coin, 4>& CarteDepart::getCoinsActuels() const {
        return (face == FaceCarte::RECTO) ? coinsRecto : coinsVerso;
    }

    const vector<Regne>& CarteDepart::getRessourcesCentreRecto() const {
        if (face != FaceCarte::RECTO) {
            throw ManageException("Recto : pas de ressource au milieu !");
        }
        return ressourcesCentreRecto;
    }

    ostream& operator<<(ostream& f, const CarteDepart& c) {
        const auto& coins = c.getCoinsActuels();

        f << " --------------- \n";

        f << "|" << coins.at(HAUT_GAUCHE);
        (!coins.at(HAUT_GAUCHE).estInexistant()) ? f << "|" : f << " ";
        f << "       ";

        (!coins.at(HAUT_DROIT).estInexistant()) ? f << "|" : f << " ";

        f << coins.at(HAUT_DROIT) << "|\n";

        if (c.getFace() == RECTO) {
            f << "|";

            // Trait horizontal uniquement si le coin existe
            const auto& hg = coins.at(HAUT_GAUCHE).getContenu();
            const auto& bg = coins.at(BAS_GAUCHE).getContenu();
            const auto& hd = coins.at(HAUT_DROIT).getContenu();
            const auto& bd = coins.at(BAS_DROIT).getContenu();

            if (!holds_alternative<Inexistant>(hg) ||
                !holds_alternative<Inexistant>(bg)) {
                f << "---";
            }
            else {
                f << "   ";
            }

            const auto& ressources = c.getRessourcesCentreRecto();

            switch (ressources.size()) {
            case 1:
                f << "    " << ressources.at(0) << "    ";
                break;
            case 2:
                f << "   " << ressources.at(0)
                    << ressources.at(1) << "    ";
                break;
            case 3:
                f << "   " << ressources.at(0)
                    << ressources.at(1)
                    << ressources.at(2) << "   ";
                break;
            default:
                f << "         ";
                break;
            }

            if (!holds_alternative<Inexistant>(hd) ||
                !holds_alternative<Inexistant>(bd)) {
                f << "---";
            }
            else {
                f << "   ";
            }

            f << "|\n";
        }
        else {
            f << "|---         ---|\n";
        }

        f << "|" << coins.at(BAS_GAUCHE);
        (!coins.at(BAS_GAUCHE).estInexistant()) ? f << "|" : f << " ";
        f << "       ";
        (!coins.at(BAS_DROIT).estInexistant()) ? f << "|" : f << " ";
        f << coins.at(BAS_DROIT) << "|\n";

        f << " --------------- ";

        return f;
    }

    //*****CARTE OBJECTIF*****

    //Constructeur pour un objectif de Ressources (3 fois la même ressource)
    CarteObjectif::CarteObjectif(int p, Regne r, bool sec)
        : Carte(FaceCarte::RECTO), points(p), typeObjectif(TypeObjectif::RESSOURCES_IDENTIQUES),
        secret(sec), ressourceCible(r), objetCible(nullopt) {
    }

    //Constructeur pour un objectif d'Objets Identiques (2 fois le même objet)
    CarteObjectif::CarteObjectif(int p, Objet o, bool sec)
        : Carte(FaceCarte::RECTO), points(p), typeObjectif(TypeObjectif::OBJETS_IDENTIQUES),
        secret(sec), ressourceCible(nullopt), objetCible(o) {
    }

    //Constructeur pour Série d'objets (chacun des 3 objets apparait une fois) ou Placement
    CarteObjectif::CarteObjectif(int p, TypeObjectif to, bool sec)
        : Carte(FaceCarte::RECTO), points(p), typeObjectif(to),
        secret(sec), ressourceCible(nullopt), objetCible(nullopt) {
    }

    int CarteObjectif::getPoints() const { return points; }
    TypeObjectif CarteObjectif::getTypeObjectif() const { return typeObjectif; }
    bool CarteObjectif::estSecret() const { return secret; }

    //int CarteObjectif::nbFoisAtteint(const PlateauJoueur& plateau) const;  //==============à définir !!==================

    void CarteObjectif::retourner() {
        throw ManageException("On ne peut pas retourner une carte objectif !");
    }
}
