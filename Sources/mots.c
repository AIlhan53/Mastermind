#include "../Includes/common.h"
#include "../Includes/mots.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

// Cette fonction verifie qu'un mot comporte exactement 4 lettres minuscules sans accent
// Paramètres:
// - Le mot à vérifier
// Renvoie:
// - true si le mot est correct, false si le mot n'est pas correct
bool VerifierMot(char *motAVerifier)
{
    char erreur[100];
    if ((motAVerifier) == NULL)
    {
        strcpy(erreur, "La chaine est NULL");
        return false;
    }
    else if (strlen(motAVerifier) != 4)
    {
        strcpy(erreur, "le mot ne fait pas 4 lettre exactement");
        return false;
    }
    else
    {
        for (int cpt = 0; cpt < strlen(motAVerifier); cpt++)
        {
            if (motAVerifier[cpt] < 'a' || motAVerifier[cpt] > 'z')
            {
                strcpy(erreur, "Le mot contient une majuscule ou un caractere incorrecte");
                return false;
                break;
            }
        }
        return true;
    }
}

// Cette fonction initialise la structure avec le dictionnaire
// en l'allouant en memoire et en lisant le dictionnaire à partir d'un fichier
// En cas d'erreur:
// - elle garnit la structure Dico_Message avec l'explication de l'erreur puis renvoie NULL
// - c'est à l'appelant de décider d'afficher le message ou pas
// Paramètres:
// - le nom du fichier
// - l'adresse de la structure Dico_Message
// Renvoie:
// - Une structure Dictionnaire remplie
// - ou NULL s'il y a eu une erreur
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour)
{
    int erreur = 0;
    char buffer[50];
    FILE *fichier = fopen(nomDeFichier, "r");
    if (!fichier)
    {
        erreur = errno;
        switch (erreur)
        {
        case ENOENT:
            strcpy(messageDeRetour->message, strerror(errno));
            messageDeRetour->codeErreur = erreur;
            return NULL;
            break;
        case EEXIST:
            strcpy(messageDeRetour->message, strerror(errno));
            messageDeRetour->codeErreur = erreur;
            return NULL;
            break;
        case EINVAL:
            strcpy(messageDeRetour->message, strerror(errno));
            messageDeRetour->codeErreur = erreur;
            return NULL;
            break;
        default:
            strcpy(messageDeRetour->message, strerror(errno));
            messageDeRetour->codeErreur = erreur;
            return NULL;
            break;
        }
    }

    Dictionnaire *suivant = (Dictionnaire *)malloc(sizeof(Dictionnaire));
    if (!suivant)
    {
        strcpy(messageDeRetour->message, "Erreur de malloc");
        messageDeRetour->codeErreur = -1;
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    suivant->dictio = NULL;
    suivant->nb_Mot = 0;

    while (fscanf(fichier, "%s", buffer) != EOF)
    {
        suivant->dictio = realloc(suivant->dictio, sizeof(char *) * suivant->nb_Mot + 1);
        if (suivant->dictio == NULL)
        {
            strcpy(messageDeRetour->message, "Erreur de réallocation de mémoire");
            messageDeRetour->codeErreur = -1;
            fclose(fichier);
            free(suivant);
            return NULL;
        }
        suivant->dictio[suivant->nb_Mot] = malloc(strlen(buffer) + 1); // +1 pour le caractère nul de fin de chaîne
        if (suivant->dictio[suivant->nb_Mot] == NULL)
        {
            strcpy(messageDeRetour->message, "Erreur d'allocation de mémoire pour la chaîne de caractères");
            messageDeRetour->codeErreur = -1;
            fclose(fichier);
            free(suivant->dictio);
            free(suivant);
            return NULL;
        }
        strcpy(suivant->dictio[suivant->nb_Mot], buffer);
        suivant->nb_Mot++;
    }
    fclose(fichier);
    return suivant;
}

// Cf cours FBD2 pour lire le fichier

// Cette fonction libère la mémoire du dictionnaire passé en Paramètre
// Elle libère d'abord la mémoire des pointeurs internes
// puis libère la mémoire globale du dictionnaire
// A appeler en fin de partie
void EffacerDictionnaire(struct Dictionnaire *dictionnaire)
{
    if (dictionnaire != NULL)
    {
        if (dictionnaire->dictio != NULL)
        {

            for (int i = 0; i < dictionnaire->nb_Mot; i++) // Libere la mémoire pour chaque chaîne
            {
                free(dictionnaire->dictio[i]);
            }
            free(dictionnaire->dictio);
        }
        free(dictionnaire);
    }
}

// Cette fonction compare deux mots pour une ligne de jeu
// en comptant les lettres bien placées et les lettres mal placées
// Parammetres:
// - Solution (mot de reference)
// - Mot placé par le joueur
// - Adresse d'une structure a garnir avec le resultat
// Renvoie:
// - Si la comparaison n'est pas possible, elle renvoie false
// - Si la comparaison est possible, elle garnit la structure ResultatLigne et renvoie true
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat)
{
    // Allouer de la mémoire pour marquer les lettres bien placées
    bool lettreBienPlacee[4];

    if (!VerifierMot(motPlace) || !VerifierMot(solution))
    {
        return false; // Le mot est incorrecte ou la solution est incorrecte
    }
    // Initialiser le tableau à false
    for (int i = 0; i < strlen(solution); i++)
    {
        lettreBienPlacee[i] = false;
    }
    // Parcourir les mots
    for (int i = 0; i < strlen(solution); i++)
    {
        if (motPlace[i] == solution[i])
        {
            // Lettre bien placée
            if (!lettreBienPlacee[i])
            {
                resultat->nblettreOk++;
                lettreBienPlacee[i] = true; // Marquer la lettre comme bien placée
            }
        }
        else
        {
            // Lettre mal placée
            for (int j = 0; j < strlen(solution); j++)
            {
                if (motPlace[i] == solution[j] && !lettreBienPlacee[j])
                {
                    resultat->nblettreNonOk++;
                    break; // Sortir de la boucle interne
                }
            }
        }
    }
    return true ;
}