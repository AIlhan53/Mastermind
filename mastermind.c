#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/mots.h"
#include "./Includes/partie.h"

int main()
{
    struct Dico_Message leMessage;
    struct Dictionnaire *dico = NULL;
    struct Partie *partie = NULL;
    char *reponse;
    reponse = (char *)malloc(10);
    if (!reponse)
    {
        printw("Erreur de malloc");
        exit(EXIT_FAILURE);
    }
    char *chemin = "/home/ue108/projects/mastermind/Tests/liste_francais_4.txt";
    // FONCTIONS UTILISEES:
    do
    {
        InitialiserEcran();
        EffacerEcran();
        AfficherTexteDansCadre("MASTERMIND");
        RetourALaLigne();
        RetourALaLigne();
        AfficherCharSansRetour(' ', 15);
        AfficherTexteIndenteSansRetour("Appuye sur 1 pour lancer le jeu");
        RetourALaLigne();
        RetourALaLigne();
        AfficherCharSansRetour(' ', 15);
        AfficherTexteIndenteSansRetour("Appuye sur 2 pour Afficher les meilleures scores");
        RetourALaLigne();
        RetourALaLigne();
        AfficherCharSansRetour(' ', 15);
        AfficherTexteIndenteSansRetour("Ou q pour quitter");
        RetourALaLigne();
        RetourALaLigne();
        AfficherCharSansRetour(' ', 15);
        AfficherTexteIndenteSansRetour("Ton choix : ");
        reponse = LireTexte();
        if (strcmp(reponse, "1") == 0)
        {
            dico = LireDictionnaire(chemin, &leMessage);
            if (dico == NULL)
            {
                AfficherErreurEtTerminer(leMessage.message, leMessage.codeErreur);
                return EXIT_FAILURE;
            }
            partie = CreerPartie(dico);
            if (JouerPartie(partie))
            {
                AfficherMeilleursScores();
            }
            EffacerPartie(partie);
            EffacerDictionnaire(dico);
        }
        else if (strcmp(reponse, "2") == 0)
        {
            AfficherMeilleursScores();
            RetourALaLigne();
            AfficherCharSansRetour(' ', 15);
            AfficherTexteIndenteSansRetour("Appuye sur enter pour retourner au menu");
            reponse = LireTexte();
        }
        else if(strcmp(reponse,"q") == 0)
        {
            break;
        }
    } while (reponse[0] < '0' || reponse[0] >'2');
    TerminerEcran();
    free(reponse);
    return EXIT_SUCCESS;
}