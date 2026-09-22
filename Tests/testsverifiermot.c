#include "./tests.h"
#include "../Includes/mots.h"

// Test qui vérifie des mots de bonne longueur avec uniquement des minuscules
// Cas testés: à compléter
void TestMot_OK()
{
    TEST_ASSERT_TRUE(VerifierMot("bras"));
    TEST_ASSERT_TRUE(VerifierMot("abri"));
    TEST_ASSERT_TRUE(VerifierMot("sans"));
    TEST_ASSERT_TRUE(VerifierMot("sang"));
    TEST_ASSERT_TRUE(VerifierMot("mort"));
}
// Ajouter d'autres tests, à imaginer
void TestVerifierMot_Majuscule()
{
    TEST_ASSERT_FALSE(VerifierMot("Bras"));
    TEST_ASSERT_FALSE(VerifierMot("bRas"));
    TEST_ASSERT_FALSE(VerifierMot("brAs"));
    TEST_ASSERT_FALSE(VerifierMot("braS"));
    TEST_ASSERT_FALSE(VerifierMot("NIKE"));
    TEST_ASSERT_FALSE(VerifierMot("AHHH"));
}
void TestVerifierMot_troplettre()
{
    TEST_ASSERT_FALSE(VerifierMot("ftrtd"));
    TEST_ASSERT_FALSE(VerifierMot("liberer"));
    TEST_ASSERT_FALSE(VerifierMot("aaaaaaaaaaaaaa"));
    TEST_ASSERT_FALSE(VerifierMot("anticonjesaispas"));
}
void TestVerifierMot_peu_de_lettre()
{
    TEST_ASSERT_FALSE(VerifierMot("edf"));
    TEST_ASSERT_FALSE(VerifierMot("tec"));
    TEST_ASSERT_FALSE(VerifierMot("cgt"));
    TEST_ASSERT_FALSE(VerifierMot("zut"));
}
void TestVerifierMot_caractereIncorrect()
{
    TEST_ASSERT_FALSE(VerifierMot("[()]"));
    TEST_ASSERT_FALSE(VerifierMot("bra!"));
    TEST_ASSERT_FALSE(VerifierMot("!?"));
    TEST_ASSERT_FALSE(VerifierMot("!brd"));
}
void TestVerifierMot_chiffrePresent()
{
    TEST_ASSERT_FALSE(VerifierMot("bra5"));
    TEST_ASSERT_FALSE(VerifierMot("br85"));
    TEST_ASSERT_FALSE(VerifierMot("9854"));
    TEST_ASSERT_FALSE(VerifierMot("14"));
    TEST_ASSERT_FALSE(VerifierMot("0ras"));
}
void TestVerifierMot_NULL()
{
    TEST_ASSERT_FALSE(VerifierMot(""));
}

void TestsVerificationDUnMot()
{
    RUN_TEST(TestMot_OK);
    RUN_TEST(TestVerifierMot_Majuscule);
    RUN_TEST(TestVerifierMot_troplettre);
    RUN_TEST(TestVerifierMot_peu_de_lettre);
    RUN_TEST(TestVerifierMot_caractereIncorrect);
    RUN_TEST(TestVerifierMot_chiffrePresent);
    RUN_TEST(TestVerifierMot_NULL);
}