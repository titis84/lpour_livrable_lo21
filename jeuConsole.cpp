#include "jeuConsole.h"
#include <iostream>
#include <limits>

using namespace std;

namespace Codex {
//pour s'assurer d'avoir un entier pour le choix du mode de jeu, et du nombre de joueurs
int JeuConsole::demanderEntierSecurise(int min, int max) {
    int valeur;
    if (!(cin >> valeur)) { //le bloc s'execute que s'il y a une erreur
        cin.clear(); //dès qu'il y a erreur de saisie, cin se met en mode erreur. clear permet de réinitialiser cet état pour pouvoir continuer
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //vide le buffer
        throw ManageException("Entree invalide : veuillez entrer un nombre entier.");
    }

    if (valeur < min || valeur > max) {
        throw ManageException("Veuillez respecter les options proposees.");
    }

    return valeur;
}

void JeuConsole::lancerPartie(){
    char rejouer = 'o';
    do {
        cout<<"CODEX NATURALIS"<<endl;

        //choix du mode de jeu
        int choixMode = 0;
        bool saisieOK = false;

        while (!saisieOK) {
            try {
                cout<<"Modes de jeu possibles : \n 1. Solo\n 2. Multijoueur\n Entrez votre choix : ";
                choixMode = demanderEntierSecurise(1, 2);
                saisieOK = true;
            }
            catch (const ManageException& e) {
                cout << "[ERREUR] " << e.getInfo() << endl; // Affichage direct
            }
        }

        //nombre de joueurs
        int nbJoueurs = 1;
        if (choixMode == 2) {
            saisieOK = false;
            while (!saisieOK) {
                try {
                    cout << "Entrez le nombre de joueurs (entre 2 et 4) : ";
                    nbJoueurs = demanderEntierSecurise(2, 4);
                    saisieOK = true;
                }
                catch (const ManageException& e) {
                    cout << "[ERREUR] " << e.getInfo() << endl; // Affichage direct
                }
            }
            cout<<"Mode Multijoueur selectionne avec " << nbJoueurs << " joueur/\n";
        } else {
            cout << "Mode Solo selectionne.\n";
        }

        //creation des joueurs
        vector<Joueur> listeJoueurs ;
        for(int i = 0 ; i < nbJoueurs ; i++){
            string nomJoueur;
            if(choixMode==1){
                cout << "Nom du joueur : ";
            } else {
                cout << "Nom du joueur " << i + 1 << " : " ;
            }
            cin >> nomJoueur;

            int ordre = i + 1 ;
            bool estPremier = (i==0);

            listeJoueurs.emplace_back(nomJoueur, ordre, estPremier);
            //emplace_back permet de contruire et ajouter le joueur au vecteur en une
            //ligne au lieu d'utiliser le constructeur puis push_back
        }

        //mise en place de la partie : distribution cartes
        Partie partie ;
        partie.miseEnPlacePartie(listeJoueurs, choixMode); //A DEFINIR miseEnPlacePartie

        bool finPartieDeclenchee = false ;
        int indexJoueurDeclencheFin = - 1;

        while(!finPartieDeclenchee){

            for(int i = 0 ; i < nbJoueurs ; i++){
                Joueur& joueurActuel = listeJoueurs[i];

                cout << "------------------------------------------\n";
                cout << "Tour de " << joueurActuel.getNom() << " | Score actuel : " << joueurActuel.getScore() << endl ;
                cout << "------------------------------------------\n";

                partie.jouer(joueurActuel); // A DEFINIR jouer : comprend choix de la carte + dépose de la carte

                //Piocher
                //verif si le joueur a atteint 20 pts ou +
                if (joueurActuel.getScore() >= 20 && !finPartieDeclenchee) {
                    finPartieDeclenchee = true;
                    indexJoueurDeclencheFin = i ;
                    cout << "\nDECLENCHEMENT FIN DE JEU : " << joueurActuel.getNom() << " a atteint ou depasse 20 points.\n";
                }

                cout << "Veuillez piocher une carte.\n" ;
                partie.piocherCarte(joueurActuel); //A DEFINIR piocherCarte

                //verif s'il reste encore des cartes à piocher
                if(partie.piochesVides()){ //A DEFINIR piochesVides
                    finPartieDeclenchee = true ;
                    indexJoueurDeclencheFin = i ;
                    cout << "\nDECLENCHEMENT FIN DE JEU : Il n'y a plus de cartes à piocher.\n";
                }

                if(choixMode==1) partie.jouerTybor(); //A DEFINIR jouerTybor

                if (finPartieDeclenchee) break ; //sortir de la boucle pour entamer le tour final
            }

            //gestion de la fin de partie
            //règle : "Les joueurs terminent le tour en cours, puis chacun joue une dernière fois
            if (finPartieDeclenchee) {
                // 1. Terminer d'abord le tour en cours pour les potentiels joueurs restants
                cout << "\n--- FIN DU TOUR EN COURS ---\n";
                for (int j = indexJoueurDeclencheFin + 1; j < nbJoueurs; j++) {
                    Joueur& joueurSuivant = listeJoueurs[j];
                    cout << "------------------------------------------\n";
                    cout << "Fin du tour en cours pour " << joueurSuivant.getNom() << endl;
                    cout << "------------------------------------------\n";

                    partie.jouer(joueurSuivant);
                    cout << "Veuillez piocher une carte.\n";
                    if (!partie.piochesVides()) partie.piocherCarte(joueurSuivant);
                    if (choixMode == 1) partie.jouerTybor();
                }

                // 2. Tour final complet pour TOUS les joueurs (de J0 à J(nbJoueurs - 1))
                cout << "\n--- DERNIER TOUR POUR TOUS LES JOUEURS ---\n";
                for (int k = 0; k < nbJoueurs; k++) {
                    Joueur& joueurFinal = listeJoueurs[k];
                    cout << "------------------------------------------\n";
                    cout << "Dernier tour de " << joueurFinal.getNom() << endl;
                    cout << "------------------------------------------\n";

                    partie.jouer(joueurFinal);
                    cout << "Veuillez piocher une carte.\n";
                    if (!partie.piochesVides()) partie.piocherCarte(joueurFinal);
                    if (choixMode == 1) partie.jouerTybor();
                }
                break; //fin de la partie
            }
        }

        cout<<"FIN DE LA PARTIE"<<endl;
        cout<<"Resultats : "<<endl;
        //calcul des points de chaque joueur
        //afficher les résulats

        if(choixMode==1){
            //int scoreTybor = methode A DEFINIR
            //int scoreJoueur = methode A DEFINIR
            cout << "Score Tybor : " << scoreTybor << endl ;
            cout << "Votre score : " << scoreJoueur << endl ;

            /*Au moment de comptabiliser les points des cartes objectif, ne
                comptez que les vôtres (les deux objectifs communs et l’objectif
                secret), Tybor ne gagne pas de points grâce aux objectifs en fin de
                partie. Vous gagnez si vous avez plus de points que Tybor.
            */

            if(scoreJoueur>scoreTybor){
                cout << "Vous avez gagne !" << endl;
            } else if(scoreTybor>scoreJoueur){
                cout << "Tybor a gagne !" << endl;
            } else {
                cout<< "Egalite !" << endl;
            }

        } else { //mode multijoueurs
            //je déclare forfait
        }

        cout<<"Voulez-vous refaire une partie ?(o/n) ";
        cin >> rejouer ;

        cout<<endl;

    } while(rejouer == 'o' || rejouer == 'O'); //permet de faire plusieurs partie d'affilée

}
}

