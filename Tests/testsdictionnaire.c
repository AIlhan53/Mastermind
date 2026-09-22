#include "./tests.h"
#include "../Includes/mots.h"
char buffer[50];

// Test qui lit un dictionnaire sans erreur
// Il verifie que les informations suivantes sont bien lue:
// - Structure Dictionnaire non nulle
// - Nombre de mots correct
// - Verification que les mots de la liste sont bien lus
void TestDictionnaire_OK()
{
    char *chemin = "./liste_francais_4.txt";
    struct Dico_Message message;
    struct Dictionnaire *motLu;

    motLu = LireDictionnaire(chemin, &message);
    TEST_ASSERT_NOT_NULL(motLu);

    TEST_ASSERT_EQUAL_INT(416, motLu->nb_Mot);

    TEST_ASSERT_EQUAL_STRING("abri", motLu->dictio[0]);
    TEST_ASSERT_EQUAL_STRING("deux", motLu->dictio[104]);
    TEST_ASSERT_EQUAL_STRING("fuir", motLu->dictio[144]);

    EffacerDictionnaire(motLu);
}
/// @brief Lire un fichier inexistant
void LireFichierNomIncorrect()
{
    struct Dico_Message message;
    struct Dictionnaire *motLu;

    motLu = LireDictionnaire("./nexistepas.txt", &message);
    TEST_ASSERT_NULL(motLu);
    EffacerDictionnaire(motLu);
}
/// @brief Test pour lire le contenu d'un dictionnaire avec des mots contenant plus de 4 lettres
void LireDictionnaireTropDelettre()
{
    struct Dico_Message message;
    struct Dictionnaire *motLu;

    motLu = LireDictionnaire("./liste_trop_lettre.txt", &message);

    TEST_ASSERT_EQUAL_STRING("flute", motLu->dictio[14]);
    TEST_ASSERT_EQUAL_STRING("pourquoi", motLu->dictio[128]);
    TEST_ASSERT_EQUAL_STRING("arbre", motLu->dictio[180]);

    EffacerDictionnaire(motLu);
}
/// @brief Test pour lire le contenu d'un dictionnaire avec des mots contenant moins de 4 lettres
void LireDictionnairePeuDeLettre()
{
    struct Dico_Message message;
    struct Dictionnaire *motLu;

    motLu = LireDictionnaire("./liste_mot_peu_lettre.txt", &message);

    TEST_ASSERT_EQUAL_STRING("kfc", motLu->dictio[28]);
    TEST_ASSERT_EQUAL_STRING("tec", motLu->dictio[44]);
    TEST_ASSERT_EQUAL_STRING("zut", motLu->dictio[227]);

    EffacerDictionnaire(motLu);
}
/// @brief Test pour lire le contenu d'un dictionnaire avec des mots contenant des caractere incorrect
void LireDictionnaireIncorrect()
{
    struct Dico_Message message;
    struct Dictionnaire *motLu;

    motLu = LireDictionnaire("./dicoNonOk.txt", &message);

    TEST_ASSERT_EQUAL_STRING("!!!!", motLu->dictio[6]);
    TEST_ASSERT_EQUAL_STRING("air?", motLu->dictio[10]);
    TEST_ASSERT_EQUAL_STRING("!rdu", motLu->dictio[21]);
    TEST_ASSERT_EQUAL_STRING("45fd", motLu->dictio[24]);
    TEST_ASSERT_EQUAL_STRING("#fr8", motLu->dictio[46]);
    TEST_ASSERT_EQUAL_STRING("¨*gtd8", motLu->dictio[78]);

    EffacerDictionnaire(motLu);
}
void TestsDictionnaire()
{
    RUN_TEST(TestDictionnaire_OK);
    RUN_TEST(LireFichierNomIncorrect);
    RUN_TEST(LireDictionnaireTropDelettre);
    RUN_TEST(LireDictionnairePeuDeLettre);
    RUN_TEST(LireDictionnaireIncorrect);
}