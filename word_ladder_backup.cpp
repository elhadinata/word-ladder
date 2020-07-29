
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <set>

#include "assignments/wl/word_ladder.h"

bool firstLadder = false;

std::set<std::string> neighbourList(std::string& input,
                                    const std::unordered_set<std::string>& lexicon) {
  std::set<std::string> neighbourSet = {};
  const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

  for (std::string::size_type index = 0; index < input.size(); index++) {
    for (char currLetter : alphabet) {
      std::string curr = input;
      curr.at(index) = currLetter;
      // If in lexicon, not in resultSet, not input,  then add to resultSet
      if ((lexicon.find(curr) != lexicon.end()) &&
          (neighbourSet.find(curr) == neighbourSet.end()) && (input.compare(curr))) {
        neighbourSet.insert(curr);
      }
    }
  }
  // for (const auto& neighbour : neighbourSet) {
  //  std::cout << neighbour << ' ';
  //}
  // std::cout << "\n";
  return neighbourSet;
}

void printWLFromPred(std::map<std::string, std::string>& predMap, std::string& endWord) {
  std::vector<std::string> wordLadder;
  wordLadder.push_back(endWord);

  auto temp = predMap.find(endWord);
  std::string previous;
  if (!(temp == predMap.end())) {
    previous = temp->second;
  } else {
    previous = "";
  }

  while (!previous.empty()) {
    wordLadder.push_back(previous);
    temp = predMap.find(previous);
    previous = temp->second;
  }

  if (!firstLadder) {
    std::cout << "Found ladder: ";
    firstLadder = true;
  }

  for (auto iter = wordLadder.crbegin(); iter != wordLadder.crend(); iter++) {
    std::cout << *iter << ' ';
  }
  std::cout << "\n";
}

bool predMapContains(std::map<std::string, std::string>& predMap,
                     std::string& target,
                     std::string& endWord) {
  if (!endWord.compare(target)) {
    std::cout << "!endWord.compare(target)\n";
    return true;
  }

  const int count = predMap.count(endWord);

  if (count) {
    std::cout << "PredMap has endWord[" << endWord << "]["<<count<<"]\n";
    auto temp = predMap.find(endWord);
    std::string previous = temp->second;
    // std::cout << "Endword[" << endWord << "] Previous[" << previous << "] Target[" << target <<
    // "]\n";
    return true;
  } else {
    std::cout << "PredMap DOESN'T have endWord \n";
  }

  return false;
}
