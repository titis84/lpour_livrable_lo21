#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <variant>
#include <array>
using namespace std;

namespace Codex {

    //caractéristiques
    enum Regne { VEGETAL, ANIMAL, FONGIQUE, ENTOMOLOGIQUE };
    enum Objet { PLUME, ENCRIER, PARCHEMIN };
    enum FaceCarte { RECTO, VERSO };
    enum TypeObjectif { PLACEMENT, OBJETS_IDENTIQUES, SERIE_OBJETS, RESSOURCES_IDENTIQUES };
    enum TypePoint { FLAT, NB_ANGLES_RECOUVERTS, NB_OBJETS_VISIBLES };
    enum PositionCoin { HAUT_GAUCHE, HAUT_DROIT, BAS_GAUCHE, BAS_DROIT }; //HAUT_GAUCHE vaut 0, etc.

    ostream& operator<<(ostream& f, Regne r);
    ostream& operator<<(ostream& os, Objet o);

    //classes
    struct Inexistant {};
    struct Vide {};

    //*****COIN*****

    class Coin {
        bool estVisible;
        variant<Inexistant, Vide, Regne, Objet> contenu;
    public:
        Coin(bool visible, variant<Inexistant, Vide, Regne, Objet> c = Vide{})
            : estVisible(visible), contenu(c) {
        }

        bool getEstVisible() const;
        void setEstVisible(bool v); //à déterminer ultérieurement selon nos besoins : mettre en private et ajouter plateau en amie ?

        bool estInexistant() const;
        bool estVide() const;
        bool hasRessource() const;
        bool hasObjet() const;
        Regne getRessource() const;
        Objet getObjet() const;
        const variant<Inexistant, Vide, Regne, Objet>& getContenu() const { return contenu; }
    };
    ostream& operator<<(ostream& f, const Coin& coin);

    //*****CARTE*****

    class Carte {
    protected:
        FaceCarte face;
    public:
        Carte() : face(FaceCarte::VERSO) {} //constructeur par défaut
        Carte(FaceCarte f) : face(f) {}     //constructeur avec argument
        virtual ~Carte() = default;
        FaceCarte getFace() const;
        virtual  void retourner();
    };

    //*****CARTE JOUABLE*****

    class CarteJouable : public Carte {
    protected:
        Regne regne;
        array<Coin, 4> coinsRecto;
        int points; //nb potentiel de pts du recto, pas de points au verso

        //au verso, toujours quatre coins vides
        inline static const array<Coin, 4> coinsVerso = {
            Coin(true, Vide{}), Coin(true, Vide{}),
            Coin(true, Vide{}), Coin(true, Vide{})
        };

    public:
        //Constructeur avec coins détaillés
        CarteJouable(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, FaceCarte f = FaceCarte::VERSO);
        //Constructeur avec array
        CarteJouable(Regne r, const array<Coin, 4>& cRecto, int p, FaceCarte f = FaceCarte::VERSO);
        //à voir si on garde les deux constructeurs ou qu'un seul

        Regne getRegne() const;
        int getPoints() const;
        const array<Coin, 4>& getCoinsActuels() const;
        //quid poserCarte ??
    };
    ostream& operator<<(ostream& f, const CarteJouable& cj);

    //*****CARTE RESSOURCE*****

    class CarteRessource : public CarteJouable {
    public:
        //Constructeur avec coins détaillés
        CarteRessource(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, FaceCarte f = FaceCarte::VERSO);
        //Constructeur avec array
        CarteRessource(Regne r, int p, const array<Coin, 4>& cRecto, FaceCarte f = FaceCarte::VERSO);

        //quid poserCarte ??
    };

    //*****CARTE DORURE*****

    class CarteDorure : public CarteJouable {
        vector<Regne> conditions;
        TypePoint typePoint;
    public:
        //Constructeur avec coins détaillés
        CarteDorure(Regne r, Coin hg, Coin hd, Coin bg, Coin bd, int p, const vector<Regne>& cond, TypePoint tp, FaceCarte f = FaceCarte::VERSO);
        //Constructeur avec array
        CarteDorure(Regne r, const std::array<Coin, 4>& cRecto, int p, const vector<Regne>& cond, TypePoint tp, FaceCarte f = FaceCarte::VERSO);

        const vector<Regne>& getConditions() const;
        TypePoint getTypePoint() const;
        //quid poserCarte ??
    };
    ostream& operator<<(ostream& f, const CarteDorure& cd);

    //*****CARTE DEPART*****

    class CarteDepart : public Carte {
        array<Coin, 4> coinsRecto;           // Entre 2 et 4 coins existants (les autres sont Inexistant).
        //si 3 ressources au centre, 2 coins vides et 2 coins inexistants
        //si 2 ressources au centre, 4 coins vides
        //si une ressource au centre, 4 coins : 2 vides, et 2 avec ressources
        array<Coin, 4> coinsVerso;           // 4 coins avec chacun une des quatres ressources
        vector<Regne> ressourcesCentreRecto; // Entre 1 et 3 ressources au centre du verso
    public:
        // Constructeur avec des arrays
        CarteDepart(const array<Coin, 4>& cRecto, const array<Coin, 4>& cVerso, const vector<Regne>& resCentre, FaceCarte f = FaceCarte::VERSO);

        const array<Coin, 4>& getCoinsRecto() const;
        const array<Coin, 4>& getCoinsVerso() const;
        const array<Coin, 4>& getCoinsActuels() const;
        const vector<Regne>& getRessourcesCentreRecto() const;
    };
    ostream& operator<<(ostream& f, const CarteDepart& c);

    //*****CARTE OBJECTIF*****

    class PlateauJoueur; // Déclaration anticipée

    class CarteObjectif : public Carte {
        int points;
        TypeObjectif typeObjectif;
        bool secret;
        optional<Regne> ressourceCible;
        optional<Objet> objetCible;
    public:
        //Constructeur pour un objectif de Ressources (3 fois la même ressource)
        CarteObjectif(int p, Regne r, bool sec);
        //Constructeur pour un objectif d'Objets Identiques (2 fois le même objet)
        CarteObjectif(int p, Objet o, bool sec);
        //Constructeur pour Série d'objets (chacun des 3 objets apparait une fois) ou Placement
        CarteObjectif(int p, TypeObjectif to, bool sec);

        int getPoints() const;
        TypeObjectif getTypeObjectif() const;
        bool estSecret() const;
        int nbFoisAtteint(const PlateauJoueur& plateau) const;
        void retourner();
    };
    ostream& operator<<(ostream& f, const CarteObjectif& cO);
}
