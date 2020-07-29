#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <map>
#include <string>
#include <unordered_set>

#include <set>

std::set<std::string> neighbourList(std::string& input,
                                    const std::unordered_set<std::string>& lexicon);

void printWLFromPred(std::map<std::string, std::string>& predMap, std::string& endWord);
bool predMapContains(std::map<std::string, std::string>& predMap,
                     std::string& target,
                     std::string& endWord);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
