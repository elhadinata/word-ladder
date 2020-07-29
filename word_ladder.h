#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

std::set<std::string> NeighbourList(std::string& input,
                                    const std::unordered_set<std::string>& lexicon);
void PrintCurrPath(std::vector<std::string>&);
std::vector<std::vector<std::string>>
BreadthFirstSearch(std::string& start_word,
                   std::string& dest_word,
                   const std::unordered_set<std::string>& lexicon);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
