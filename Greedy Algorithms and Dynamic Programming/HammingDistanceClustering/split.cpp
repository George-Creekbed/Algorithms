/* splits a sentence into its single words
and stores these words ina vector */
#ifndef SPLIT_cpp_INCLUDED
#define SPLIT_cpp_INCLUDED
#include <cctype>
#include <vector>
#include <string>
#include <iostream>
#include "split.h"

using std::vector;      using std::string;
using std::cout;        using std::endl;

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    // invariant: we have processed characters [original value of i, i)
    while ( i != s.size() )
    {
        // ignore leading blanks
        // invariant: characters in range [original i, current i) are all spaces
        while ( i != s.size() && ( isspace(s[i]) || ispunct(s[i]) ) )
            ++i;

        // find end of next word
        string_size j = i;
        // invariant: none of the characters in range [original j, current j) is a space //or a comma
        while ( j != s.size() && !isspace(s[j]) && !ispunct(s[j]) ) // ispunct finds all punctuations, included commas
            j++;

        // if we found some nonwhitespace characters
        if (i != j)
        {
            //copy from s starting at i and taking j-i chars
            //ret.push_back(s.substring(i, j-i));
            string word;
            for (string_size index = i; index != j; ++index)
            {
                string aux(1, s[index]);
                word += aux;
            }

            ret.push_back(word);
            i = j;
        }
    }

    return ret;
}

#endif
