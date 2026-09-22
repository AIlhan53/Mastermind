#include "./tests.h"
#include "../Includes/mots.h"

// Test qui vérifie (à compléter)
void TestComparerMots_Identiques1()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("abri", "abri", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_Identiques2()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("noir", "noir", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_Identiques3()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("aveu", "aveu", resultat));
    TEST_ASSERT_EQUAL_INT(4, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques1()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("ride", "rire", resultat));
    TEST_ASSERT_EQUAL_INT(3, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques2()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("ride", "dire", resultat));
    TEST_ASSERT_EQUAL_INT(2, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(2, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques3()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("lion", "noir", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(3, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques4()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("joue", "kilo", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(1, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques5()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("elle", "lire", resultat));
    TEST_ASSERT_EQUAL_INT(1, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(1, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_NonIdentiques6()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("miel", "lime", resultat));
    TEST_ASSERT_EQUAL_INT(1, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(3, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_Aucun()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_TRUE(ComparerMots("quoi", "rare", resultat));
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreOk);
    TEST_ASSERT_EQUAL_INT(0, resultat->nblettreNonOk);
    free(resultat);
}
void TestComparerMots_motVide()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect1()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "rie", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect2()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("mort", "mot", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect3()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "mo4t", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect4()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "flr*", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect5()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "k8*d", resultat));
    free(resultat);
}
void TestComparerMots_motIncorrect6()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("ride", "police", resultat));
    free(resultat);
}
void TestComparerMots_solutionIncorrect1()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("pil", "pile", resultat));
    free(resultat);
}
void TestComparerMots_solutionIncorrect2()
{
    struct ResultatLigne *resultat;
    resultat = (struct ResultatLigne *)malloc(sizeof(struct ResultatLigne));
    if (resultat == NULL)
    {
        printf("erreur de malloc");
        exit(EXIT_FAILURE);
    }
    resultat->nblettreNonOk = 0;
    resultat->nblettreOk = 0;
    TEST_ASSERT_FALSE(ComparerMots("route", "roue", resultat));
    free(resultat);
}
// Execute tous les tests de comparaison de mots
void TestsComparaisonDeMots()
{
    RUN_TEST(TestComparerMots_Identiques1);
    RUN_TEST(TestComparerMots_Identiques2);
    RUN_TEST(TestComparerMots_Identiques3);
    RUN_TEST(TestComparerMots_NonIdentiques1);
    RUN_TEST(TestComparerMots_NonIdentiques2);
    RUN_TEST(TestComparerMots_NonIdentiques3);
    RUN_TEST(TestComparerMots_NonIdentiques4);
    RUN_TEST(TestComparerMots_NonIdentiques5);
    RUN_TEST(TestComparerMots_motIncorrect6);
    RUN_TEST(TestComparerMots_Aucun);
    RUN_TEST(TestComparerMots_motVide);
    RUN_TEST(TestComparerMots_motIncorrect1);
    RUN_TEST(TestComparerMots_motIncorrect2);
    RUN_TEST(TestComparerMots_motIncorrect3);
    RUN_TEST(TestComparerMots_motIncorrect4);
    RUN_TEST(TestComparerMots_motIncorrect5);
    RUN_TEST(TestComparerMots_motIncorrect6);
    RUN_TEST(TestComparerMots_solutionIncorrect1);
    RUN_TEST(TestComparerMots_solutionIncorrect2);
}