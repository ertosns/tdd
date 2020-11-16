#include <string>
#include "gmock/gmock.h"
#include "soundex.hpp"

using namespace testing;

class SoundexFixture : public testing::Test {
public:
  Soundex soundex;
};
  
TEST_F(SoundexFixture, RetainSoleFirstCharAndCaseInsensitive) {
  auto encoded = soundex.encode("A");
  ASSERT_THAT(encoded, Eq("a000"));
}

TEST_F(SoundexFixture, EmptyString) {
  auto encoded = soundex.encode("");
    ASSERT_THAT(encoded, Eq(""));
}

TEST_F(SoundexFixture, ReplaceVowels) {
  auto encoded = soundex.encode("wow");
  ASSERT_THAT(encoded, Eq("w000"));
}

TEST_F(SoundexFixture, RemoveNonAlphabet) {
  auto encoded = soundex.encode("$#./\{}[]`~1234567890");
  ASSERT_THAT(encoded, Eq(""));
}

TEST_F(SoundexFixture, EncodeSixGroups) {   
  auto encoded = soundex.encode("abcdef");
  ASSERT_THAT(encoded, Eq("a123"));
}

TEST_F(SoundexFixture, ResolveSimilarAdjacent) {
  auto encoded = soundex.encode("Scientist");
  ASSERT_THAT(encoded, Eq("s532"));
  encoded = soundex.encode("zzz...");
  ASSERT_THAT(encoded, Eq("z200"));
}

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  //how to run_specific_test
  //how to run a specific group of tests?
  return RUN_ALL_TESTS();
}
