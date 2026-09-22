#include <mysql.h>
#include "./common.h"

#ifndef _DICO_SCORE
#define _DICO_SCORE
typedef struct Points
{
    // A COMPLETER, CF LPP structures
    char nom[50];
    int score;
    int scoreAffichage;
}Points;
static const char *ServerDB = "127.0.0.1";
#endif
bool CreerDB(bool baseDeTest, struct Dico_Message *messageDeRetour); // Fonction rajouté
MYSQL *ConnecterBaseDeDonnees(bool DBDeTest, struct Dico_Message *messageDeRetour);
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour);
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour);
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore,  struct Dico_Message *messageDeRetour);
