#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <set>
#include <string>
#include <unordered_set>
#endif

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);


    bool floating_checker(
    std::string word,
    const std::string& floating);


std::set<std::string> wordle_helper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    uint word_size,
    std::string word,
    std::string& alphabet,
    std::set<std::string>& words
);

// std::unordered_set<std::string> load_dictionary(
//     const std::string& in,
//     const std::string& floating,
//     const std::set<std::string>& dict);

// std::vector<std::pair<int, char>> pos_finder(
//      const std::string& in
// );

#endif