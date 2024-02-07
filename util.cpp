#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> myKeywords;

    // convert rawWords into lowercase
    rawWords = convToLower(rawWords);

    // parse rawWords by whitespaces
    std::istringstream iss(rawWords);
    string myWord;

    while (iss >> myWord) { // while parsing rawWords into myWord
        myWord = trim(myWord); // remove leading and trailing whitespace of my word
        
        // check if myWord has punctuation by iterating through letters
        size_t letterPos = 0;
        while (letterPos < myWord.length()) {
            if (ispunct(myWord[letterPos])) { // if letter is punctuation
                string noPunctWord = myWord.substr(0,letterPos); // split word at punctuation to create substring before punctuation
                if (noPunctWord.length() >= 2) { // add substring to keywords if at least two chars long
                    myKeywords.insert(noPunctWord);
                }
                myWord.erase(0, letterPos + 1); // delete substring from word
                letterPos = 0; // reset letter position to check for punctuation in remaining word
            }
            else { // if no punctuation at current letter
                ++letterPos; // move to next letter
            }
        }
        
        // add remaining word to keywords if at least two chars long
        if (myWord.length() >= 2) {
            myKeywords.insert(myWord);
        }
    }
    
    return myKeywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

