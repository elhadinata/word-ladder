#include <iostream>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string start_word;
  std::string dest_word;

  std::cout << "Enter start word (RETURN to quit): ";
  std::getline(std::cin, start_word);
  if (start_word.empty()) {
    return 0;
  }
  std::cout << "Enter destination word: ";
  std::cin >> dest_word;

  std::vector<std::vector<std::string>> paths = BreadthFirstSearch(start_word, dest_word, lexicon);

  for (auto& path : paths) {
    PrintCurrPath(path);
  }

  return 0;
}
