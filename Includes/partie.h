// Fonctions publiques
#include "./common.h"
#include "./mots.h"

#ifndef _DICO_PARTIE
#define _DICO_PARTIE
typedef struct Partie
{
    // A COMPLETER (Cf. LPP2 structures)
    // La stucture contient tout le jeu en cours:
    char *solution;
    char **motEssai;
    struct ResultatLigne *resultat;
    char nomJoueur[50];
    char signes[10][2];
    int Essaie;
    bool issue;
}Partie;
#endif

struct Partie *CreerPartie(struct Dictionnaire *dictionnaire);
void EffacerPartie(struct Partie *partieEnCours);
bool JouerPartie(struct Partie *partieEnCours);
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug);
bool MotDejaJoue(struct Partie *partieEnCours, char *mot); // Fonction rajouté
void AfficherMeilleursScores();