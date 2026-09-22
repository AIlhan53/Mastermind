#include "../Includes/common.h"
#include "../Includes/ecran.h"

// ***************************************//
// FONCTIONS DECLAREES DANS LE FICHIER .h //
// ***************************************//

// Initialise la console ncurses
void InitialiserEcran()
{
    initscr();
}

// Terminer la console ncurses
void TerminerEcran()
{
    endwin();
}

// Efface l'ecran de la console ncurses
void EffacerEcran()
{
    clear();
}

// Va a la ligne dans la console ncurses
void RetourALaLigne()
{
    printw("\n");
    refresh();
}

// Affiche dans la console ncurses un texte avec indentation en cas d'erreur
// a partir de la position courante
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteErreurIndenteSansRetour(char *texteAAfficher)
{
    printw("%s", texteAAfficher);
}
// Affiche dans la console ncurses un texte avec indentation
// a partir de la position courante
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteIndenteSansRetour(char *texteAAfficher)
{
    printw("%s", texteAAfficher);
    refresh();
}

// Affiche une chaine de caracteres a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - la chaine de caracteres a afficher (pointeur)
void AfficherTexteSansRetour(char *texteAAfficher)
{
    printw("%s", texteAAfficher);
    refresh();
}

// Affiche un caractere a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le caractere a afficher
// - le nombre de fois qu'il faut le repeter
void AfficherCharSansRetour(unsigned char caractereAAfficher, int repetition)
{
    int cpt;
    for (cpt = 0; cpt < repetition; cpt++)
    {
        printw("%c", caractereAAfficher);
    }
}

// Affiche un nombre entier a la position courante dans la console ncurses
// sans retour a la ligne
// Paramètres:
// - le nombre a afficher
void AfficherNombreSansRetour(int nombreAAfficher)
{
    printw("%d", nombreAAfficher);
    refresh();
}

// Affiche un caractere special a la position courante dans la console ncurses
// sans retour a la ligne
// Cette fonction permet notamment de dessiner des bordures/contours
// Liste des codes: https://invisible-island.net/ncurses/man/curs_addch.3x.html
// Paramètres:
// - le caractere a traduire en code special
// - le nombre de fois qu'il faut le repeter
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher, int repetition)
{
    for (int cpt = 0; cpt < repetition; cpt++)
    {

        addch(NCURSES_ACS(caractereAAfficher));
    }
    refresh();
}

// Affiche dans la console ncurses un texte dans un cadre indente d'une tabulation
// Paramètres:
// - la chaine de caracteres a afficher dans le cadre (pointeur)
void AfficherTexteDansCadre(char *texteAAfficher)
{
    int espace;
    espace = strlen(texteAAfficher);
    printw("\n\t\t\t");
    addch(NCURSES_ACS(ACS_ULCORNER));
    AfficherCharSpecialSansRetour(ACS_HLINE, espace);
    addch(NCURSES_ACS(ACS_URCORNER));
    printw("\n\t\t\t");
    addch(NCURSES_ACS(ACS_VLINE));
    printw("%s", texteAAfficher);
    addch(NCURSES_ACS(ACS_VLINE));
    printw("\n\t\t\t");
    addch(NCURSES_ACS(ACS_LLCORNER));
    AfficherCharSpecialSansRetour(ACS_HLINE, espace);
    addch(NCURSES_ACS(ACS_LRCORNER));
    refresh();
}

// Cette fonction efface l'ecran, affiche "Erreur" dans un cadre
// affiche un message et un code d'erreur sous le cadre,
// attend 5 secondes puis termine l'application
// Paramètres:
// - Le texte d'erreur
// - Le code d'erreur eventuel
void AfficherErreurEtTerminer(char *texteDErreur, int codeDErreur)
{
    // FONCTIONS UTILISEES:
    EffacerEcran();
    AfficherTexteDansCadre("ERREUR");
    RetourALaLigne();
    RetourALaLigne();
    AfficherCharSansRetour(' ',20);
    AfficherTexteErreurIndenteSansRetour(texteDErreur);
    RetourALaLigne();
    RetourALaLigne();
    AfficherCharSansRetour(' ',20);
    AfficherTexteErreurIndenteSansRetour("Code de l'erreur : ");
    AfficherNombreSansRetour(codeDErreur);
    RetourALaLigne();

    for (int cpt = 5; cpt >= 0; cpt--) // Compte à rebourd
    {
        move(12, 20);
        printw("Temps restant : %d secondes", cpt);
        refresh();
        sleep(1);
    }
    RetourALaLigne();
    RetourALaLigne();
    TerminerEcran();
}

// Affiche le haut du cadre de jeu (bordure supérieure)
// Paramètres:
// - Le mot à afficher, ou NULL si rien ne doit etre affiché
void AfficherHautDeJeu(char *motAAfficher)

{
    if (strcmp(motAAfficher, "") == 0)
    {
        printw("\t\t");
        addch(NCURSES_ACS(ACS_ULCORNER));
        AfficherCharSpecialSansRetour(ACS_HLINE, 15);
        printw("%s", motAAfficher);
        addch(NCURSES_ACS(ACS_TTEE));
        AfficherCharSpecialSansRetour(ACS_HLINE, 8);
        addch(NCURSES_ACS(ACS_URCORNER));
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t ");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_LTEE));
        AfficherCharSpecialSansRetour(ACS_HLINE, 15);
        addch(NCURSES_ACS(ACS_PLUS));
        AfficherCharSpecialSansRetour(ACS_HLINE, 8);
        addch(NCURSES_ACS(ACS_RTEE));
        refresh();
    }
    else
    {
        printw("\t\t");
        addch(NCURSES_ACS(ACS_ULCORNER));
        AfficherCharSpecialSansRetour(ACS_HLINE, 11);
        printw("%s", motAAfficher);
        addch(NCURSES_ACS(ACS_TTEE));
        AfficherCharSpecialSansRetour(ACS_HLINE, 8);
        addch(NCURSES_ACS(ACS_URCORNER));
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t ");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_LTEE));
        AfficherCharSpecialSansRetour(ACS_HLINE, 15);
        addch(NCURSES_ACS(ACS_PLUS));
        AfficherCharSpecialSansRetour(ACS_HLINE, 8);
        addch(NCURSES_ACS(ACS_RTEE));
        refresh();
    }
}

// Affiche un separateur entre deux mots du jeu
void AfficherSeparateurDeJeu()
{
    int nbcase = 0;
    while (nbcase < 8) // Le nombre de cases souhaité - 2 pour le haut et le bas donc 8 correspond à 10 cases
    {
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t\t");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\t ");
        addch(NCURSES_ACS(ACS_VLINE));
        printw("\n\t\t");
        addch(NCURSES_ACS(ACS_LTEE));
        AfficherCharSpecialSansRetour(ACS_HLINE, 15);
        addch(NCURSES_ACS(ACS_PLUS));
        AfficherCharSpecialSansRetour(ACS_HLINE, 8);
        addch(NCURSES_ACS(ACS_RTEE));
        nbcase++;
    }
    refresh();
}

// Affiche un mot du jeu et son resultat
// - Un '+' par lettre bien placée
// - Un '-' par lettre mal placée
// - Des espaces pour compléter
void AfficherMotDeJeu(char *motAAfficher, int nbreLettresBienplacées, int nbreLettresMalplacées)
{
    printw("%s", motAAfficher);
    AfficherCharSansRetour(' ',10);
    AfficherCharSpecialSansRetour(ACS_VLINE,1);
    AfficherCharSansRetour(' ',2);
    if (nbreLettresBienplacées > 0)
    {
        AfficherCharSansRetour('+', nbreLettresBienplacées);
    }
    if (nbreLettresMalplacées > 0)
    {
        AfficherCharSansRetour('-', nbreLettresMalplacées);
    }
    
    refresh();
}

// Affiche la bordure inférieure du jeu
void AfficherBasDeJeu()
{
    printw("\n\t\t");
    addch(NCURSES_ACS(ACS_VLINE));
    printw("\t\t");
    addch(NCURSES_ACS(ACS_VLINE));
    printw("\t ");
    addch(NCURSES_ACS(ACS_VLINE));
    printw("\n\t\t");
    addch(NCURSES_ACS(ACS_LLCORNER));
    AfficherCharSpecialSansRetour(ACS_HLINE, 15);
    addch(NCURSES_ACS(ACS_BTEE));
    AfficherCharSpecialSansRetour(ACS_HLINE, 8);
    addch(NCURSES_ACS(ACS_LRCORNER));
    printw("\n");
    refresh();
}