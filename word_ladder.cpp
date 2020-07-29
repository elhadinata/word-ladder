#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "assignments/wl/word_ladder.h"

bool firstLadder = false;

std::set<std::string> NeighbourList(std::string& input,
                                    const std::unordered_set<std::string>& lexicon) {
  std::set<std::string> neighbourSet = {};
  const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

  for (std::string::size_type index = 0; index < input.size(); index++) {
    for (const char& currLetter : alphabet) {
      std::string curr = input;
      curr.at(index) = currLetter;
      if ((lexicon.find(curr) != lexicon.end()) &&
          (neighbourSet.find(curr) == neighbourSet.end()) && (input.compare(curr))) {
        neighbourSet.insert(curr);
      }
    }
  }
  return neighbourSet;
}

void PrintCurrPath(std::vector<std::string>& currPath) {
  if (!firstLadder) {
    std::cout << "Found ladder: ";
    firstLadder = true;
  }
  for (const auto& currWord : currPath) {
    std::cout << currWord << ' ';
  }
  std::cout << "\n";
}

std::vector<std::vector<std::string>>
BreadthFirstSearch(std::string& start_word,
                   std::string& dest_word,
                   const std::unordered_set<std::string>& lexicon) {
  std::vector<std::vector<std::string>> result;

  std::queue<std::vector<std::string>> bfs_queue;
  std::map<std::string, size_t> dead_ends;
  bool found_ladder = false;
  size_t smallest_path = INT_MAX;

  std::vector<std::string> curr_path;
  curr_path.push_back(start_word);
  bfs_queue.push(curr_path);
  dead_ends.insert(std::pair<std::string, size_t>(start_word, curr_path.size()));

  std::string current;
  while (!bfs_queue.empty()) {
    curr_path = bfs_queue.front();
    bfs_queue.pop();
    current = curr_path.back();

    if (found_ladder && (curr_path.size() > smallest_path)) {
      break;
    }

    if (!current.compare(dest_word)) {
      if (!found_ladder) {
        smallest_path = curr_path.size();
        found_ladder = true;
      }
      result.push_back(curr_path);
    }

    std::set<std::string> neighbourSet = NeighbourList(current, lexicon);
    for (std::string next : neighbourSet) {
      if (std::find(curr_path.begin(), curr_path.end(), next) == curr_path.end()) {
        if (!dead_ends.count(next) || (dead_ends.find(next)->second > curr_path.size())) {
          std::vector<std::string> newPath(curr_path);
          newPath.push_back(next);
          bfs_queue.push(newPath);
          dead_ends.insert(std::pair<std::string, size_t>(next, newPath.size()));
        }
      }
    }
  }

  if (!found_ladder) {
    std::cout << "No ladder found\n";
  }

  return result;
}
