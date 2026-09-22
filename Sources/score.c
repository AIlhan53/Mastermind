#include "../Includes/common.h"
#include "../Includes/score.h"

#define NBMAXESSAIS 10

// Fonction pour executer une instruction SQL
// En cas d'erreur, affiche la cause a la console, mais continue toujours
//
// Paramètres:
// - Pointeur vers la structure de connexion MYSQL
// - Chaine de caracteres avec l'instruction a executer
// - Structure pour ecrire un message et un code en cas d'erreur
// Renvoie:
// - booleen qui indique le resultat
bool ExecuterInstructionSQL(MYSQL *sqlConnection, char *instructionSQL, struct Dico_Message *messageDeRetour)
{
    if (mysql_query(sqlConnection, instructionSQL))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(messageDeRetour->message, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = -1;
        return false;
    }
    return true;
}
// Fonction permettant de créer une DB si elle n'existe pas
// Paramètres
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie:
// TRUE si la DB à été créée
// False si la DB eciste déjà
bool CreerDB(bool baseDeTest, struct Dico_Message *messageDeRetour)
{
    MYSQL *sqlConnection;
    sqlConnection = mysql_init(NULL);
    if (!sqlConnection)
    {

        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(messageDeRetour->message, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = -1;
        return NULL;
    }
    if (!mysql_real_connect(sqlConnection, "127.0.0.1", "root",
                            NULL, NULL, 3306, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(messageDeRetour->message, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = -1;
        return NULL;
    }
    // Création de la base de données si elle n'existe pas
    if (baseDeTest == 0)
    {

        char createDBQuery[100];
        ExecuterInstructionSQL(sqlConnection, "DROP DATABASE IF EXISTS la227472 ", messageDeRetour);

        sprintf(createDBQuery, "CREATE DATABASE la227472");
        ExecuterInstructionSQL(sqlConnection, createDBQuery, messageDeRetour);

        // Utilisation de la base de données
        ExecuterInstructionSQL(sqlConnection, "USE la227472", messageDeRetour);

        // Création des tables si elles n'existent pas
        ExecuterInstructionSQL(sqlConnection, "CREATE TABLE Joueur (id_joueur INT AUTO_INCREMENT,nom_joueur VARCHAR(50) NOT NULL,PRIMARY KEY(id_joueur))", messageDeRetour);
        ExecuterInstructionSQL(sqlConnection, "CREATE TABLE Partie (num_partie INT AUTO_INCREMENT,score_partie INT NOT NULL,id_joueur INT NOT NULL,PRIMARY KEY(num_partie),FOREIGN KEY(id_joueur) REFERENCES Joueur(id_joueur))", messageDeRetour);
        return true;
    }
    else
    {
        char createDBQuery[100];
        ExecuterInstructionSQL(sqlConnection, "DROP DATABASE IF EXISTS testmastermind ", messageDeRetour);
        sprintf(createDBQuery, "CREATE DATABASE testmastermind");
        ExecuterInstructionSQL(sqlConnection, createDBQuery, messageDeRetour);

        // Utilisation de la base de données
        ExecuterInstructionSQL(sqlConnection, "USE testmastermind", messageDeRetour);

        // Création des tables si elles n'existent pas
        ExecuterInstructionSQL(sqlConnection, "CREATE TABLE Joueur (id_joueur INT AUTO_INCREMENT,nom_joueur VARCHAR(50) NOT NULL,PRIMARY KEY(id_joueur))", messageDeRetour);
        ExecuterInstructionSQL(sqlConnection, "CREATE TABLE Partie (num_partie INT AUTO_INCREMENT,score_partie INT NOT NULL,id_joueur INT NOT NULL,PRIMARY KEY(num_partie),FOREIGN KEY(id_joueur) REFERENCES Joueur(id_joueur))", messageDeRetour);
        return true;
    }

    return false;
}
// Fonction pour se connecter a la base de donnees en la creant si elle n'existe pas
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie:
// - Pointeur vers la structure MYSQL de la connexion
MYSQL *ConnecterBaseDeDonnees(bool baseDeTest, struct Dico_Message *messageDeRetour)
{
    MYSQL *sqlConnection;
    int connec = 0;
    sqlConnection = mysql_init(NULL);
    if (!sqlConnection)
    {

        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(messageDeRetour->message, mysql_error(sqlConnection));
        messageDeRetour->codeErreur = -1;
        return NULL;
    }
    do
    {
        if (!mysql_real_connect(sqlConnection, "127.0.0.1", "root",
                                NULL, baseDeTest ? "testmastermind" : "la227472", 3306, NULL, 0))
        {
            CreerDB(baseDeTest, messageDeRetour);
        }
        else
        {
            connec = 1;
        }
    } while (connec == 0);

    return sqlConnection;
}

// Fonction lire l'identifiant unique du joueur dans la base de donnees
// Si le joueur n'est pas déjà present, il est ajoute puis la fonction
// se rapelle en recursif pour obtenir l'identifiant auto incremente dans la base de donnees
// Paramètres:
// - Pointeur vers la structure de connexion MYSQL
// - Le nom du joueur
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - L'identifiant unique du joueur dans la base de donnees
int LireIDJoueur(MYSQL *sqlConnection, char *nomJoueur, struct Dico_Message *messageDeRetour)
{
    MYSQL_RES *sqlResult;
    MYSQL_ROW sqlRow;

    if (strlen(nomJoueur) < 1 || strlen(nomJoueur) > 50)
    {
        strcpy(messageDeRetour->message, "Nom de joueur invalide");
        messageDeRetour->codeErreur = -1;
        return 0;
    }
    // Construire l'instruction SQL pour rechercher le joueur par nom
    char query[150];
    snprintf(query, sizeof(query), "SELECT id_joueur FROM Joueur WHERE nom_joueur = '%s'", nomJoueur);

    if (!ExecuterInstructionSQL(sqlConnection, query, messageDeRetour))
    {
        return 0;
    }

    // Récupérer le résultat de la requête
    sqlResult = mysql_store_result(sqlConnection);
    if (sqlResult == NULL)
    {
        strcpy(messageDeRetour->message, "Erreur lors de la récupération du résultat.");
        messageDeRetour->codeErreur = -1;
        return 0; // Valeur d'erreur
    }

    // Si le joueur existe déjà dans la base de données
    if (mysql_num_rows(sqlResult) > 0)
    {
        sqlRow = mysql_fetch_row(sqlResult);
        int idJoueur = atoi(sqlRow[0]); // Convertir l'identifiant du joueur en entier
        mysql_free_result(sqlResult);   // Libérer le résultat de la requête
        return idJoueur;
    }
    else
    {
        // Le joueur n'existe pas encore dans la base de données, l'ajouter
        snprintf(query, sizeof(query), "INSERT INTO Joueur (nom_joueur) VALUES ('%s')", nomJoueur);
        if (!ExecuterInstructionSQL(sqlConnection, query, messageDeRetour))
        {
            // Erreur lors de l'insertion du joueur
            return 0;
        }

        // Appel récursif pour obtenir l'identifiant auto-incrémenté du joueur
        return LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour);
    }
}

// Fonction pour sauver un score dans la base de donnees
// Le score se calcule comme etant (nombre maximum d'essais + 1 - nombre d'essais)
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nom du joueur
// - Le nombre d'essai.
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un booleen qui indique si le sauvetage s'est fait ou pas
bool SauverScore(bool baseDeTest, char *nomJoueur, int nombreDEssais, struct Dico_Message *messageDeRetour)
{

    // Connexion à la base de données
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour);
    if (sqlConnection == NULL)
    {
        return false;
    }
    // Récupération de l'identifiant du joueur
    int idJoueur = LireIDJoueur(sqlConnection, nomJoueur, messageDeRetour);
    if (idJoueur == 0)
    {
        // Erreur lors de la récupération de l'identifiant du joueur
        mysql_close(sqlConnection);
        return false;
    }

    // Calcul du score
    int score = NBMAXESSAIS + 1 - nombreDEssais;

    // Construction de l'instruction SQL pour sauvegarder le score
    char query[100];
    int num_partie;
    snprintf(query, sizeof(query), "INSERT INTO Partie (num_partie, score_partie, id_joueur) VALUES (%d, %d, %d)", num_partie, score, idJoueur);

    // Exécution de l'instruction SQL
    if (!ExecuterInstructionSQL(sqlConnection, query, messageDeRetour))
    {
        // Erreur lors de l'exécution de l'instruction SQL
        mysql_close(sqlConnection);
        return false;
    }

    mysql_close(sqlConnection);
    // Le score a été sauvegardé avec succès
    return true;
}

// Fonction pour les meilleurs scores dans la base de donnees
// Paramètres:
// - Booleen qui indique si c'est la base de donnees pour les tests unitaires ou pas (et donc: de production)
// - Le nombre de scores maximum à lire
// - Pointeur vers la structure pour remplir un message d'erreur et un eventuel code d'erreur
// Renvoie
// - Un pointeur vers le nombre demandé de Points (pointeur vers un tableau)
//   ou bien NULL en cas d'erreur
struct Points *LireMeilleursScores(bool baseDeTest, int nombreDeScore, struct Dico_Message *messageDeRetour)
{

    // Connexion à la base de données
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(baseDeTest, messageDeRetour);
    if (!sqlConnection)
    {
        return NULL;
    }

    // Exécution de l'instruction SQL pour obtenir les meilleurs scores
    char instructionSQL[250];
    sprintf(instructionSQL, "SELECT Joueur.nom_joueur, Partie.score_partie FROM Joueur JOIN Partie ON Joueur.id_joueur = Partie.id_joueur WHERE Joueur.nom_joueur IS NOT NULL AND Joueur.nom_joueur != '' ORDER BY Partie.score_partie DESC LIMIT %d", nombreDeScore);
    MYSQL_RES *resultat;
    if (!ExecuterInstructionSQL(sqlConnection, instructionSQL, messageDeRetour))
    {
        // Erreur lors de l'insertion du joueur
        mysql_close(sqlConnection);
        return NULL;
    }
    resultat = mysql_store_result(sqlConnection);
    if (!resultat)
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        mysql_close(sqlConnection);
        return NULL;
    }

    int nombresReelDeScore = mysql_num_rows(resultat);

    // Allocation dynamique de la mémoire pour stocker les meilleurs scores
    struct Points *meilleursScores = malloc(nombreDeScore * sizeof(struct Points));
    if (!meilleursScores)
    {
        // Gestion de l'erreur de l'allocation mémoire
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        mysql_free_result(resultat);
        mysql_close(sqlConnection);
        return NULL;
    }
    // Récupération des données et stockage dans la structure Points
    MYSQL_ROW ligne;
    int i = 0;
    while ((ligne = mysql_fetch_row(resultat)) && i < nombresReelDeScore)
    {
        if (ligne[0] && ligne[1] != NULL)
        {
            strcpy(meilleursScores[i].nom, ligne[0]);
            meilleursScores[i].score = atoi(ligne[1]);
        }
        i++;
        meilleursScores->scoreAffichage = i;
    }
    // Libération des ressources et fermeture de la connexion
    mysql_free_result(resultat);
    mysql_close(sqlConnection);

    return meilleursScores;
}
