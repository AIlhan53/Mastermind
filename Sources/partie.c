#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/mots.h"
#include "../Includes/partie.h"
#include "../Includes/score.h"

#define NBMAXESSAIS 10
// Fonction pour créer une partie
// Paramètre:
// - Le dictionnaire contenant tous les mots
// Renvoie
// - Une structure Partie allouée en memoire, avec un mot choisi au hasard
//   et toute l'information mise à zero pour commencer la partie
struct Partie *CreerPartie(struct Dictionnaire *dictionnaire)
{
    char erreur[100];
    int codeErreur;
    Partie *partieEnCours = (Partie *)malloc(sizeof(Partie));
    if (!partieEnCours)
    {
        strcpy(erreur, "Erreur de malloc au niveau de partieEnCours");
        codeErreur = -1;

        AfficherErreurEtTerminer(erreur, codeErreur);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    // Création d'une nouvelle structure partie
    int cpt = 0;
    int numeroMot = rand() % dictionnaire->nb_Mot;
    partieEnCours->solution = (char *)malloc(5);

    if (!partieEnCours->solution)
    {
        strcpy(erreur, "Erreur de malloc au niveau de la solution ou du mot essayé");
        codeErreur = -1;
        AfficherErreurEtTerminer(erreur, codeErreur);
        exit(EXIT_FAILURE);
    }
    strcpy(partieEnCours->solution, dictionnaire->dictio[numeroMot]);
    int LongueurSolut = strlen(partieEnCours->solution);
    partieEnCours->Essaie = 0;

    return partieEnCours;
}

// Fonction pour libérer la memoire liee a une partie
// Paramètre:
// - Pointeur vers la strcuture Partie a libérer de la memoire
void EffacerPartie(struct Partie *partieEnCours)
{
    int cpt;
    free(partieEnCours->solution);
    for (cpt = 0; cpt < partieEnCours->Essaie; cpt++)
    {
        partieEnCours->motEssai[cpt];
    }
    free(partieEnCours->motEssai);
    free(partieEnCours);
}

// Fonction pour afficher une partie en cours
// Pour chaque mot déjà essayé, on affiche
// - Le mot
// - Le resultat: un + par lettre bien placée et un - par lettre mal placée
// Paramètre:
// - Pointeur vers la structure Partie
// - Booleen qui indique si on est en mode debug (qui affiche la solution)
void AfficherPartie(struct Partie *partieEnCours, bool modeDebug)
{
    int EssaieRestant = NBMAXESSAIS - partieEnCours->Essaie;
    int posver = 1;
    EffacerEcran();
    if (modeDebug == true)
    {
        AfficherHautDeJeu(partieEnCours->solution);

        AfficherSeparateurDeJeu();

        AfficherBasDeJeu();
        sleep(1);
        EffacerEcran();
    }
    AfficherHautDeJeu("");

    AfficherSeparateurDeJeu();

    AfficherBasDeJeu();
    move(4, 50);
    printw("LE MASTERMIND");
    move(6, 47);
    printw("Essaies restant : %d", EssaieRestant);
    if (EssaieRestant == 10 && partieEnCours->issue == 0)
    {
        AfficherMotDeJeu("", 0, 0);
    }

    else
    {
        struct ResultatLigne *resultat;
        int lettreok = 0;
        int lettrenonOk = 0;
        lettrenonOk = partieEnCours->resultat->nblettreNonOk;
        lettreok = partieEnCours->resultat->nblettreOk;
        partieEnCours->signes[partieEnCours->Essaie - 1][0] = partieEnCours->resultat->nblettreOk;
        partieEnCours->signes[partieEnCours->Essaie - 1][1] = partieEnCours->resultat->nblettreNonOk;
    }
    for (int cpt = 0; cpt < partieEnCours->Essaie; cpt++)
    {
        move(posver, 18);
        AfficherMotDeJeu(partieEnCours->motEssai[cpt], partieEnCours->signes[cpt][0], partieEnCours->signes[cpt][1]);
        posver += 2;
    }

    refresh();
}
// Fonction pour vérifier si un mot a déjà été joué
// Renvoie vrai si le mot est déjà joué ou false si il est pas joué
bool MotDejaJoue(struct Partie *partieEnCours, char *mot)
{
    for (int i = 0; i < partieEnCours->Essaie; i++)
    {
        if (strcmp(partieEnCours->motEssai[i], mot) == 0)
        {
            return true; // Le mot a déjà été joué
        }
    }
    return false; // Le mot n'a pas encore été joué
}
// Fonction pour jouer une partie
// Paramètre:
// - Pointeur vers la structure Partie préablement initialisée avec une nouvelle partie
// Renvoie:
// - false si abandon, true si fin de partie (gagnée ou perdue)
// Fonctionnement:
// - Affiche la partie (mots déjà joués)
// - Demande un nouveau mot de 4 lettres ou ENTER pour abandonner le jeu
// - Verifier le mot et s'il est correct, calculer le resultat
//   (10 si trouve en 1 coup, 9 en 2 coups... 1 en 10 coups)
// - Si le mot n'est pas correct, le resultat est 0.
// A la fin de la partie:
// - Si gagne ou perdu: on demande le nom du jour et on sauve le résultat
// - Si abandon: fin de partie, on affiche la solution
bool JouerPartie(struct Partie *partieEnCours)
{
    char erreur[100];
    int codeErreur;
    char *mot;
    bool Modedebug;
    bool triche;
    int EssaieRestant = NBMAXESSAIS;
    bool DB = 0; // 0 = base de données de jeu , 1 = base de données de test

    mot = (char *)malloc(10);
    if (!mot)
    {
        strcpy(erreur, "Erreur de malloc");
        codeErreur = -1;
        AfficherErreurEtTerminer(erreur, codeErreur);
        exit(EXIT_FAILURE);
    }

    partieEnCours->resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (!partieEnCours->resultat)
    {
        strcpy(erreur, "Erreur de malloc");
        codeErreur = -1;
        AfficherErreurEtTerminer(erreur, codeErreur);
        exit(EXIT_FAILURE);
    }

    struct Points *joueur;
    joueur = malloc(sizeof(Points));
    if (!joueur)
    {
        strcpy(erreur, "Erreur de malloc au niveau de la solution ou du mot essayé");
        codeErreur = -1;
        AfficherErreurEtTerminer(erreur, codeErreur);
        exit(EXIT_FAILURE);
    }
    struct Dico_Message leMessage;
    partieEnCours->Essaie = 0;
    partieEnCours->issue = 0;
    Modedebug = triche = 0;
    for (partieEnCours->Essaie = 0; partieEnCours->Essaie < NbreMaxDEssais; partieEnCours->Essaie++)
    {
        do
        {
            AfficherPartie(partieEnCours, Modedebug);
            move(22, 15);
            AfficherTexteIndenteSansRetour("Entre un mot de 4 lettres ( q POUR Abandonner): ");
            strcpy(mot, LireTexte());
            if (strcmp(mot, "*") == 0)
            {
                Modedebug = true;
                triche = true;
                AfficherPartie(partieEnCours, Modedebug);
                Modedebug = false;
            }

            if ((strcmp(mot, "q") == 0 && triche == false))
            {
                partieEnCours->issue = 1;
                AfficherPartie(partieEnCours, Modedebug);
                move(22, 15);
                AfficherTexteIndenteSansRetour("Tu as déclaré forfait (Noob)! le mot était : ");
                AfficherTexteIndenteSansRetour(partieEnCours->solution);
                move(23, 15);
                AfficherTexteIndenteSansRetour("Tape sur une touche pour arréter");
                getch();
                return false;
            }
            else if (strcmp(mot, "q") == 0 && triche == true)
            {
                partieEnCours->issue = 1;
                AfficherPartie(partieEnCours, Modedebug);
                move(21, 15);
                AfficherTexteIndenteSansRetour("Donc tu abandonne après avoir triché ?");
                move(22, 15);
                joueur->score = 0;          // le score qui va s'afficher
                partieEnCours->Essaie = 11; // Cela permet de porter le score à 0
                printw("Tes points : %d", joueur->score);
                move(23, 15);
                AfficherTexteIndenteSansRetour("Incris ton pseudo (50 caractères max) : ");
                scanw("%s", partieEnCours->nomJoueur);
                refresh();
                if (SauverScore(DB, partieEnCours->nomJoueur, partieEnCours->Essaie, &leMessage))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            refresh();
        } while (!VerifierMot(mot));
        if (MotDejaJoue(partieEnCours, mot)) // On va vérifier si le mot n'as pas déjà été jouéé
        {
            partieEnCours->Essaie--; // on résuit l'essaie de 1
            continue;                // Demander un autre mot
        }
        partieEnCours->motEssai = realloc(partieEnCours->motEssai, (sizeof(char *) * partieEnCours->Essaie) + 1);
        if (!partieEnCours->motEssai)
        {
            strcpy(erreur, "Erreur de malloc");
            codeErreur = -1;
            AfficherErreurEtTerminer(erreur, codeErreur);
            exit(EXIT_FAILURE);
        }
        partieEnCours->motEssai[partieEnCours->Essaie] = (char *)malloc(strlen(partieEnCours->solution) + 1);
        if (!partieEnCours->motEssai[partieEnCours->Essaie])
        {
            strcpy(erreur, "Erreur de malloc");
            codeErreur = -1;
            AfficherErreurEtTerminer(erreur, codeErreur);
            exit(EXIT_FAILURE);
        }
        strcpy(partieEnCours->motEssai[partieEnCours->Essaie], mot);
        partieEnCours->resultat->nblettreOk = 0;
        partieEnCours->resultat->nblettreNonOk = 0;
        if (ComparerMots(partieEnCours->solution, mot, partieEnCours->resultat))
        {
            joueur->score = EssaieRestant;
            EssaieRestant--;
            if (strcmp(mot, partieEnCours->solution) == 0 && triche == 0)
            {
                partieEnCours->issue = 1;
                partieEnCours->Essaie++;
                AfficherPartie(partieEnCours, Modedebug);
                move(21, 15);
                AfficherTexteIndenteSansRetour("Bravo tu as trouvé le mot ");
                move(22, 15);
                printw("Tes points : %d", joueur->score);
                move(23, 15);
                AfficherTexteIndenteSansRetour("Incris ton pseudo (50 caractères max) : ");
                scanw("%s", partieEnCours->nomJoueur);
                refresh();
                if (SauverScore(DB, partieEnCours->nomJoueur, partieEnCours->Essaie, &leMessage))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (strcmp(mot, partieEnCours->solution) == 0 && triche == true)
            {
                partieEnCours->issue = 1;
                partieEnCours->Essaie++;
                AfficherPartie(partieEnCours, Modedebug);
                move(21, 15);
                AfficherTexteIndenteSansRetour("t'as cru quoi ? ");
                move(22, 15);
                joueur->score = 0;          // le score qui va s'afficher
                partieEnCours->Essaie = 11; // Cela permet de porter le score à 0
                printw("Tes points : %d", joueur->score);
                move(23, 15);
                AfficherTexteIndenteSansRetour("Incris ton pseudo (50 caractères max) : ");
                scanw("%s", partieEnCours->nomJoueur);
                refresh();
                if (SauverScore(DB, partieEnCours->nomJoueur, partieEnCours->Essaie, &leMessage))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    if (partieEnCours->Essaie == 10)
    {
        joueur->score = 0;
        AfficherPartie(partieEnCours, Modedebug);
        move(21, 15);
        AfficherTexteIndenteSansRetour("LOOSER ! le mot était : ");
        AfficherTexteIndenteSansRetour(partieEnCours->solution);
        move(22, 15);
        printw("Tes points : %d", joueur->score);
        move(23, 15);
        AfficherTexteIndenteSansRetour("Incris ton pseudo (50 caractères max) : ");
        scanw("%s", partieEnCours->nomJoueur);
        free(mot);
        refresh();
        partieEnCours->issue = 1;
        partieEnCours->Essaie = 11;
        if (SauverScore(DB, partieEnCours->nomJoueur, partieEnCours->Essaie, &leMessage))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
// Fonction pour afficher les meilleurs scores
// Le nombre de scores est une constante du code, on peut la modifier et recompiler
// La fonction LireMeilleursScores() est appellée pour obtenir les meilleurs scores
// Son résultat est un tableau alloué en mémoire, qu'il faut libérer a la fin
void AfficherMeilleursScores()
{
    bool DB = 0; // 0 = base de données de jeu , 1 = base de données de test
    int affichaScore = 10;
    struct Dico_Message *leMessage;
    struct Points *points;
    points->scoreAffichage = 0;
    leMessage = malloc(sizeof(struct Dico_Message));
    if (!leMessage)
    {
        AfficherErreurEtTerminer(leMessage->message, -1);
        exit(EXIT_FAILURE);
    }
    points = LireMeilleursScores(DB, affichaScore, leMessage);
    if (points == NULL)
    {
        AfficherErreurEtTerminer(leMessage->message, leMessage->codeErreur);
        exit(EXIT_FAILURE);
    }
    EffacerEcran();
    AfficherTexteDansCadre("Meilleurs score");
    RetourALaLigne();
    // Compter le nombre réel de scores disponibles
    for (int cpt = 0; cpt < points->scoreAffichage && points->scoreAffichage <= affichaScore; cpt++)
    {

        AfficherCharSansRetour(' ', 25);
        AfficherTexteSansRetour(points[cpt].nom);
        AfficherCharSansRetour(':', 1);
        AfficherNombreSansRetour(points[cpt].score);
        RetourALaLigne();
    }
    AfficherTexteIndenteSansRetour("\t\tAppuye sur une touche pour continuer");
    getch();
    free(leMessage);
    free(points);
}