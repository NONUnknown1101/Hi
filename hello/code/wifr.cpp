#include "wifr.hpp"
#include <map>


string Wifr::morse (string text) {
    map<char, string> morseCode = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
        {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
        {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
        {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
        {'Y', "-.--"}, {'Z', "--.."}, {' ', "       "}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, 
        {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'0', "----."}
    };

    string result = "";
    for (char c : text) {
        if (morseCode.find(toupper(c)) != morseCode.end()){
            if (c == ' ')
                result += "/ ";
            else
                result += morseCode[toupper(c)] + " ";
        }
    }
    return result;
}


string Wifr::cesar(string text, int shift) {
    std::string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += static_cast<char>((c - base + shift) % 26 + base);
        } else {
            result += c;
        }
    }

    return result;
}

string Wifr::vignere(string text, string key) {
    std::string result = "";
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = (c - base + key[keyIndex] - 'a') % 26 + base;
            result += encryptedChar;
            keyIndex = (keyIndex + 1) % key.length();
        } else {
            result += c;
        }
    }
    return result;
}


string Wifr::a1z26 (string text){
    string result = "";
    bool flag = 1;
    for (char c : text) {
        if (c == ' ' || (int)c == 39){
            result += " ";
            flag = 1;
        }
        else if ((c > 'Z' || c < 'A') & (c > 'z' || c < 'a') ){
            result += "";
            flag = 1;
        }

        if (!flag)
            result += "-";

        if (c <= 'Z' & c >= 'A'){
            result += to_string((int)c - 64);
            flag = 0;
        }
        else if (c <= 'z' & c >= 'a'){
            result += to_string((int)c - 96);
            flag = 0;
        }

        else
            result += "";
    }
    return result;
}


string Wifr::ascii (string text){
    string result = "";
    for (char c : text) 
        result += to_string((int)c) + " ";
    return result;
}

string Wifr::polybius (string text){
    string result = "";
    for (char c : text){
        if (c <= 'I' & c >= 'A'){
            if (((int)c - 64) % 5 == 0){
                result += to_string(((int)c - 64) / 5);
                result += "5";
            }
            else{
                result += to_string(((int)c - 64) / 5 + 1);   
                result += to_string(((int)c - 64) % 5);
            }
            result += " ";
        }
        else if (c <= 'Z' & c >= 'J'){
            if (((int)c - 65) % 5 == 0){
                result += to_string(((int)c - 65) / 5);
                result += "5";
            }
            else{
                result += to_string(((int)c - 65) / 5 + 1);   
                result += to_string(((int)c - 65) % 5);
            }
            result += " ";
        }
        else if (c <= 'i' & c >= 'a'){
            if (((int)c - 96) % 5 == 0){
                result += to_string(((int)c - 96) / 5);
                result += "5";
            }
            else{
                result += to_string(((int)c - 96) / 5 + 1);   
                result += to_string(((int)c - 96) % 5);
            }
            result += " ";
        }
        else if (c <= 'z' & c >= 'j'){
            if (((int)c - 97) % 5 == 0){
                result += to_string(((int)c - 97) / 5);
                result += "5";
            }
            else{
                result += to_string(((int)c - 97) / 5 + 1);   
                result += to_string(((int)c - 97) % 5);
            }
            result += " ";
        }
        else if (c == ' ')
            result += "   ";
        else
            result += "";
    }
    return result;
}

string Wifr::atbash (string text){
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

