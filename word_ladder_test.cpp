/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

  To begin testing, I considered what the biggest parts of my program are and
  how they could produce incorrect results.

  I began by thinking about the assumptions my program makes when calling other functions.
  To do this I would try to forget my implementation of my functions and think of the
  assumptions I am making.
  The bigger the assumptions, the more important it is to test this function.

  When considering assumptions, I must consider all possible ways the functions are used.
  Also, the more times a function is called, the more tests it should have.

  I must also consider the types I am using, and the restrictions on these types.
  Are these types the correct types to use?
  For example, NeighbourList returns a set, hence it cannot have any duplicates

  I also need to consider any edge cases for the functions.

  Finally, I included an example from the assignment spec, to double check correctness.
*/

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"
#include "catch.h"

SCENARIO("A word's neighbours have to be the same size and not the original word") {
  GIVEN("A word you want to find the neighbours of") {
    auto lexicon = GetLexicon("assignments/wl/words.txt");
    std::string test_word = "cat";

    WHEN("You find the neighbouring words of a word") {
      std::set<std::string> neighbour_set = NeighbourList(test_word, lexicon);

      THEN("All neighbour words are the same size") {
        for (const auto& word : neighbour_set) {
          REQUIRE(word.size() == test_word.size());
        }
      }

      THEN("All neighbour words are valid words in the lexicon") {
        for (const auto& word : neighbour_set) {
          REQUIRE(lexicon.find(word) != lexicon.end());
        }
      }

      THEN("The neighbour set doesn't have the original word") {
        REQUIRE(neighbour_set.find(test_word) == neighbour_set.end());
      }
    }
  }
}

SCENARIO("BFS returns the shortest paths, hence they must be the same length, with no duplicates") {
  GIVEN("The start_word 'play' and dest_word 'time'") {
    auto lexicon = GetLexicon("assignments/wl/words.txt");
    std::string start_word = "play";
    std::string dest_word = "time";

    WHEN("You perform a BFS to find a word_ladder") {
      std::vector<std::vector<std::string>> paths =
          BreadthFirstSearch(start_word, dest_word, lexicon);

      THEN("All the possible paths should be the same length") {
        bool first_path = true;
        size_t first_size;
        for (const auto& path : paths) {
          if (first_path) {
            first_size = path.size();
            first_path = false;
          } else {
            REQUIRE(path.size() == first_size);
          }
        }
      }

      THEN("There should be no duplicate word ladders") {
        auto it = std::unique(paths.begin(), paths.end());
        REQUIRE(it == paths.end());
      }

      THEN("The word ladders shouldn't have duplicate words") {
        for (std::vector<std::string>& path : paths) {
          auto it2 = std::unique(path.begin(), path.end());
          REQUIRE(it2 == path.end());
        }
      }
    }
  }
}

SCENARIO("Correctness of BFS based on assignment spec") {
  GIVEN("The start_word 'work' and dest_word 'play'") {
    auto lexicon = GetLexicon("assignments/wl/words.txt");
    std::string start_word = "work";
    std::string dest_word = "play";

    WHEN("You perform a BFS to find a word_ladder") {
      std::vector<std::vector<std::string>> paths =
          BreadthFirstSearch(start_word, dest_word, lexicon);
      THEN("The resulting word_ladders should be correct and in lexicographic order") {
        std::vector<std::string> wl0 = {"work", "fork", "form", "foam", "flam", "flay", "play"};
        REQUIRE(wl0 == paths[0]);

        std::vector<std::string> wl1 = {"work", "pork", "perk", "peak", "pean", "plan", "play"};
        REQUIRE(wl1 == paths[1]);

        std::vector<std::string> wl2 = {"work", "pork", "perk", "peak", "peat", "plat", "play"};
        REQUIRE(wl2 == paths[2]);

        std::vector<std::string> wl3 = {"work", "pork", "perk", "pert", "peat", "plat", "play"};
        REQUIRE(wl3 == paths[3]);

        std::vector<std::string> wl4 = {"work", "pork", "porn", "pirn", "pian", "plan", "play"};
        REQUIRE(wl4 == paths[4]);

        std::vector<std::string> wl5 = {"work", "pork", "port", "pert", "peat", "plat", "play"};
        REQUIRE(wl5 == paths[5]);

        std::vector<std::string> wl6 = {"work", "word", "wood", "pood", "plod", "ploy", "play"};
        REQUIRE(wl6 == paths[6]);

        std::vector<std::string> wl7 = {"work", "worm", "form", "foam", "flam", "flay", "play"};
        REQUIRE(wl7 == paths[7]);

        std::vector<std::string> wl8 = {"work", "worn", "porn", "pirn", "pian", "plan", "play"};
        REQUIRE(wl8 == paths[8]);

        std::vector<std::string> wl9 = {"work", "wort", "bort", "boat", "blat", "plat", "play"};
        REQUIRE(wl9 == paths[9]);

        std::vector<std::string> wl10 = {"work", "wort", "port", "pert", "peat", "plat", "play"};
        REQUIRE(wl10 == paths[10]);

        std::vector<std::string> wl11 = {"work", "wort", "wert", "pert", "peat", "plat", "play"};
        REQUIRE(wl11 == paths[11]);
      }
    }
  }
}
