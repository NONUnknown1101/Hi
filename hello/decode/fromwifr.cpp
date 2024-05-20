#include "fromwifr.hpp"
#include <sstream>
#include <map>
#include <vector>


string From_Wifr::from_morse(string text) {
    map<string, char> morseCode = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
        {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
        {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},
        {"...", 'S'}, {"-", 'T'}, {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
        {"-.--", 'Y'}, {"--..", 'Z'}, {" ", ' '}, {"-----", '0'}, {".----", '1'}, {"..---", '2'},
        {"...--", '3'}, {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}
        };

    stringstream ss(text);
    string character;
    string result = "";

    while (getline(ss, character, ' ')) {
        if (character.empty()) {
        result += ' ';
        } else {
            if (character == "/")
                result += " ";
            else
                result += morseCode[character];
        }
    }
    return result;
}


string From_Wifr::from_cesar(string text, int shift) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = ((c - base + shift) % 26) + base;
        }
    }
    return result;
}

string From_Wifr::from_vignere(string text, string key) {
    std::string result = "";
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = (c - base - (key[keyIndex] - 'a') + 26) % 26 + base;
            result += decryptedChar;
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += c;
        }
    }

    return result;
}


string From_Wifr::from_ascii(string text){
    stringstream ss(text);
    string character;
    string result = "";

    while (getline(ss, character, ' ')) {
        char c = stoi(character);
        result += c;
    }

    return result;
}

string From_Wifr::from_a1z26(string text){
    stringstream ss(text);
    string character;
    vector<string> wordTokens;
    
    while (getline(ss, character, ' ')) {
        wordTokens.push_back(character);
    }
    
    string result = "";
    
    for (const string& word : wordTokens) {
        stringstream words(word);
        string decodedWord = "";
        
        while (getline(words, character, '-')) {
            int code = stoi(character);
            char c = static_cast<char>(code + 64);
            decodedWord += c;
        }
        result += decodedWord + " ";
    }
    
    return result;
}

string From_Wifr::from_polybius(string text){
    stringstream ss(text);
    string character;
    string result = "";

    while (getline(ss, character, ' ')) {
        if (character.empty()) {
            result += ' ';
        } 
        else {
            int c = stoi(character);
            if (c % 10 == 5){
                if (c/10 == 1)
                    result += (c/10 * 5 - 1) + 65;
                else
                    result += (c/10 * 5) + 65;
            }
            else {
                if (c <= 24)
                    result += ((c/10 - 1) * 5 + c % 10 - 1) + 65;
                else
                    result += (c/10 - 1) * 5 + c % 10 + 65;
            }
        }
    }
    return result;
}


string From_Wifr::from_atbash(string text){
    char mirroredLetter;
string result;
for(int i = 0; i < text.length(); i++) {
    if(isalpha(text[i])) {
        if (text[i] <= 'Z' & text[i] >= 'A')
            mirroredLetter = 'A' + ('Z' - toupper(text[i]));
        else   
            mirroredLetter = 'a' + ('z' - tolower(text[i]));
        result += mirroredLetter;
    } 
    else
        result += text[i];
}

return result;
}