#include "./tests.h"
#include "../Includes/score.h"

// Fonction pour remettre la base de donnees a zero avant un test
// Ceci est appele dans presque tous les tests de DB mais pas ailleurs
// donc pas d'utilisation de SetUp()
void ViderDBDeTest()
{
    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(1, &Lemessage); // true pour la base de données de test

    // Exécution des instructions SQL pour vider les tables de la base de données
    if (mysql_query(sqlConnection, "DELETE FROM Partie"))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(Lemessage.message, mysql_error(sqlConnection));
        Lemessage.codeErreur = -1;
        exit(EXIT_FAILURE);
    }
    if (mysql_query(sqlConnection, "DELETE FROM Joueur"))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(Lemessage.message, mysql_error(sqlConnection));
        Lemessage.codeErreur = -1;
        exit(EXIT_FAILURE);
    }
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
void test_CREER_DB_Inexistant()
{
    struct Dico_Message Lemessage;
    bool DB;
    // Création de la base de données de test si elle n'existe pas
    DB = CreerDB(true, &Lemessage);
    TEST_ASSERT_TRUE(DB);
}
// Test de connexion a la base de donnees
void test_connexionDB_OK()
{
    ViderDBDeTest();

    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(1, &Lemessage); // true pour la base de données de test
    TEST_ASSERT_NOT_NULL(sqlConnection);
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
// Test de connexion a une base de données inexistante
void test_connexionDB_NON_OK()
{
    ViderDBDeTest();

    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection;

    sqlConnection = mysql_init(NULL);
    if (!sqlConnection)
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(Lemessage.message, mysql_error(sqlConnection));
        Lemessage.codeErreur = -1;
        sqlConnection = NULL;
    }

    else if (!mysql_real_connect(sqlConnection, "127.0.0.1", "root",
                                 NULL, "testMastermind", 3306, NULL, 0)) // Mauvais nom de DB
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(Lemessage.message, mysql_error(sqlConnection));
        Lemessage.codeErreur = -1;
        TEST_ASSERT_EQUAL_STRING(Lemessage.message, "Unknown database 'testMastermind'");
        sqlConnection = NULL;
    }

    TEST_ASSERT_NULL(sqlConnection);
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
void test_Inserer_nom_OK()
{
    ViderDBDeTest();

    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(1, &Lemessage);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    // Exécution des instructions SQL pour vider les tables de la base de données
    if (mysql_query(sqlConnection, "INSERT INTO Joueur (nom_joueur) VALUES('Kyle')"))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        strcpy(Lemessage.message, mysql_error(sqlConnection));
        Lemessage.codeErreur = -1;
        exit(EXIT_FAILURE);
    }
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
void test_nom_NonOK_plus_50_caractere()
{
    ViderDBDeTest();
    int id_joueur;
    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(1, &Lemessage);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    // Exécution des instructions SQL pour vider les tables de la base de données
    id_joueur = LireIDJoueur(sqlConnection, "fbuufiaovnvigbzotunrufofhhgkvozpvnthfhgjtfkfocfphjfj", &Lemessage);
    TEST_ASSERT_EQUAL_INT(0, id_joueur);
    TEST_ASSERT_EQUAL_STRING(Lemessage.message, "Nom de joueur invalide");
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
void test_nom_NonOK_Vide()
{
    ViderDBDeTest();
    int id_joueur;
    struct Dico_Message Lemessage;
    // Connexion à la base de données de test
    MYSQL *sqlConnection = ConnecterBaseDeDonnees(1, &Lemessage);
    TEST_ASSERT_NOT_NULL(sqlConnection);
    // Exécution des instructions SQL pour vider les tables de la base de données
    id_joueur = LireIDJoueur(sqlConnection, "", &Lemessage);
    TEST_ASSERT_EQUAL_INT(0, id_joueur);
    TEST_ASSERT_EQUAL_STRING(Lemessage.message, "Nom de joueur invalide");
    // Fermeture de la connexion à la base de données
    mysql_close(sqlConnection);
}
// Execute tous les tests de scores dans la base de donnees
void TestsScores()
{
    RUN_TEST(test_CREER_DB_Inexistant);
    RUN_TEST(test_connexionDB_OK);
    RUN_TEST(test_connexionDB_NON_OK);
    RUN_TEST(test_Inserer_nom_OK);
    RUN_TEST(test_nom_NonOK_plus_50_caractere);
    RUN_TEST(test_nom_NonOK_Vide);
}
