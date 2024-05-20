#ifndef FROMWIFR_HPP
#define FROMWIFR_HPP

#include <iostream>

using namespace std;

class From_Wifr {
    public:
        string from_morse(string text);
        string from_cesar(string text, int shift);
        string from_vignere(string text, string key);
        string from_a1z26(string text);
        string from_ascii(string text);
        string from_polybius(string text);
        string from_atbash(string text);
    };
     
#endif