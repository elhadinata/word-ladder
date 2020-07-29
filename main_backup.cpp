#include <iostream>
#include <map>
#include <queue>
#include <string>

#include <iterator>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"



// TODO(jez): multiple paths with same size !!!
//TODO(jez) check correct functions
//TODO(jez) tests!

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string startWord;
  std::string destWord;

  std::cout << "Enter start word (RETURN to quit): ";
  std::getline(std::cin, startWord);
  if (startWord.empty()) {
    return 0;
  }
  std::cout << "Enter destination word: ";
  std::cin >> destWord;

  // Breadth First Search
  std::queue<std::string> bfsQueue;
  std::set<std::string> deadEnds;
  std::map<std::string, std::string> pred;
  std::map<std::string, int> dist;
  bool foundLadder = false;

  bfsQueue.push(startWord);
  deadEnds.insert(startWord);
  std::string emptyString = "";
  pred.insert(std::pair<std::string, std::string>(startWord, emptyString));
  dist.insert({startWord, 0});

  std::string current;
  while (!bfsQueue.empty()) {
    current = bfsQueue.front();
    bfsQueue.pop();
    auto currDist = dist.find(current);
    if (currDist == dist.end()) {
      std::cout << "Error: Current word distance undefined\n";
    }

    std::set<std::string> neighbourSet = neighbourList(current, lexicon);
    // std::cout << "Neighbours of ["<<current<<"]: ";
    for (std::string next : neighbourSet) {
      auto nextDist = dist.find(next);
      int currDistPlusOne = currDist->second + 1;
      if (!(nextDist == dist.end()) && (currDistPlusOne <= nextDist->second)) {
        dist.insert({next, currDistPlusOne});
      }

      // std::cout << next << " ";
      if (!next.compare(destWord)) {  // If next is destWord
        foundLadder = true;
        dist.insert({next, currDistPlusOne});
        pred.insert(std::pair<std::string, std::string>(next, current));
        printWLFromPred(pred, next);
        return 0;  // TODO(jez):  remove this by checking predMapContains or adding to deadEnds
      }

      if ((deadEnds.find(next) == deadEnds.end())//) {
         && !(predMapContains(pred, next, current)) ){
        dist.insert({next, currDistPlusOne});
        pred.insert(std::pair<std::string, std::string>(next, current));
        deadEnds.insert(next);
        bfsQueue.push(next);
      }
    }
    // std::cout << "\n";
  }



  if (!foundLadder) {
    std::cout << "No ladder found\n";
  }
  return 0;
}
