/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
	vector<StringTriple> out;

	ifstream wordsFile(word_list_fname);
	string word;
	if (wordsFile.is_open()) {
		while (getline(wordsFile,word)) {
			if (word.size() > 2) {
				std::string remove1 = word.substr(1);
				std::string remove2 = remove1;
				remove2[0] = word[0]; 
				
				if (d.homophones(word,remove1) && d.homophones(word,remove2) && d.homophones(remove1,remove2)) {
					out.push_back(StringTriple(word, remove1,remove2));
				}
			}
		}
	}

    return out;
}

