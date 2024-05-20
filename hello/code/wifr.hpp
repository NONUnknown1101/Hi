#ifndef WIFR_HPP
#define WIFR_HPP

#include <iostream>

using namespace std;

class Wifr {
    public:
        string morse(string text);
        string cesar(string text, int shift);
        string vignere(string text, string key);
        string a1z26(string text);
        string ascii(string text);
        string polybius(string text);
        string atbash(string text);
    };

#endif