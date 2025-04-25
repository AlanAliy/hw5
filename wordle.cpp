#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <fstream>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::set<std::string> words;
    return wordle_helper(in, floating, dict, in.size(), "", alphabet, words);
}



// Define any helper functions here

std::set<std::string> wordle_helper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    uint word_size,
    std::string word,
    std::string& alphabet,
    std::set<std::string>& words
) 
{
    uint curr_size = word.size();
    
    //word has correct size, word has all floating letters, word is in dictionary
    if( curr_size == word_size &&
        floating_checker(word, floating) &&
        dict.find(word) != dict.end())
        {words.insert(word);}
   
    
    else if(isalpha(in[word.size()])) {
        word.push_back(in[word.size()]);
        wordle_helper(in, floating, dict, word_size, word, alphabet, words);
    }

    else if (word.size() < word_size){
        for (char c : alphabet) {
            word.push_back(c);
            wordle_helper(in, floating, dict, word_size, word, alphabet, words);
            word.pop_back();
        }
    }
    return words;
}




bool floating_checker(std::string word, const std::string& floating) {
    for (char c : floating) {
        size_t pos = word.find(c);
        if (pos == std::string::npos) {
            return false;
        }
        word.erase(pos, 1);  // remove matched char so it's not double-counted
    }
    return true;
}





//this function will take in the details of the word given
//and return a vector of pairs with each pair containing the psoition of the letter
//and the letter itself
// std::vector<std::pair<int, char>> pos_finder(
//     const std::string& in
// )
// {
//     std::vector<std::pair<int, char>> letter_loc_pairs;

//     for(int i = 0; i < in.size(); i++) {
//         if(isalpha(in[i])) {
//             std::pair<int, char> letter_loc_pair = {i,in[i]};
//             letter_loc_pairs.push_back(letter_loc_pair);
//         }
//     }
//     return letter_loc_pairs;
// }






