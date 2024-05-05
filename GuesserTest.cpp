/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, ConstructorInitializesCorrectly) {
    Guesser guesser("hello");
    ASSERT_EQ(guesser.remaining(), 3); // Check initial guesses count
}

TEST(GuesserTest, ConstructorTruncatesLongSecret) {
    string longSecret(40, 'a'); // Create a string longer than 32 characters
    Guesser guesser(longSecret);
    ASSERT_EQ(guesser.remaining(), 3); // Ensure it still initializes correctly
}

TEST(GuesserTest, MatchDistanceExactMatch) {
    Guesser guesser("hello");
    ASSERT_TRUE(guesser.match("hello"));
    ASSERT_EQ(guesser.remaining(), 3); // Should reset guesses
}

TEST(GuesserTest, MatchDistanceDifferentLengths) {
    Guesser guesser("hello");
    ASSERT_FALSE(guesser.match("hellooo")); // Distance should be 2
    ASSERT_EQ(guesser.remaining(), 2);
}

TEST(GuesserTest, MatchCorrectGuess) {
    Guesser guesser("secret");
    ASSERT_TRUE(guesser.match("secret"));
    ASSERT_EQ(guesser.remaining(), 3); // Should reset guesses
}

TEST(GuesserTest, MatchLockedAfterThreeAttempts) {
    Guesser guesser("secret");
    guesser.match("wrong");
    guesser.match("wrong");
    guesser.match("wrong");
    ASSERT_EQ(guesser.remaining(), 0);
    ASSERT_FALSE(guesser.match("secret")); // Should be locked, even with correct guess
}

TEST(GuesserTest, MatchIncorrectGuess) {
    Guesser guesser("hello");
    ASSERT_FALSE(guesser.match("help"));  // Incorrect guess, but within distance 1
    ASSERT_EQ(guesser.remaining(), 2);  // Should be 2 guesses remaining after one incorrect guess
}


TEST(GuesserTest, RemainingDecrementsProperly) {
    Guesser guesser("test");
    guesser.match("testy");
    ASSERT_EQ(guesser.remaining(), 2);
    guesser.match("tasty");
    ASSERT_EQ(guesser.remaining(), 1);
}
