#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>


using namespace std;

string from_morse(string text) {
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


string from_cesar(const std::string& word, int shift) {
    std::string result = word;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = ((c - base + shift) % 26) + base;
        }
    }
    return result;
}

string from_ascii(string text){
    stringstream ss(text);
    string character;
    string result = "";

    while (getline(ss, character, ' ')) {
        char c = stoi(character);
        result += c;
    }

    return result;
}

string from_a1z26(string text){
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

string from_polybius(string text){
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


string from_atbash(string text){
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




int main() {

    string inputPath;
    cout << "Введите файл / Enter the file: ";
    cin >> inputPath;

    ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        cerr << "Ошибка при открытии файла / Error opening file" << endl;
        return 1;
    }


    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

    string encodings[] = {"morse", "cesar", "ascii", "a1z26", "polybius", "atbash"};
    cout << "Шифр / Code: " << endl;
    for (int i = 0; i < 6; i++){
        cout << i << ". " << encodings[i] << endl;
    }    

    int code;
    cout << "Введите шифр / Enter the code: ";
    cin >> code;

    if (code < 0 || code > 5)
        cout << "Неверный код / Wrong code" << endl;


    std::ofstream outputFile("decode_" + inputPath);
    if (!outputFile.is_open()) {
        return 1;
    }

    int step;

if (code == 1){
    char flag;
    cout << "Известен ли шаг? / Do you know a step? (+/-): ";
    cin >> flag;

    if (flag == '+'){
        std::cout << "Введите шаг / Enter the step: ";
        std::cin >> step;
        step = 26 - step;
    }
    else{
    std::string word;
    inputFile >> word;

    for (int i = 0; i < 26; ++i)
        std::cout << "Шаг / Step " << i << ": " << from_cesar(word, i) << std::endl;

    std::cout << "Выберите шаг / Choose a step: ";
    std::cin >> step;

    inputFile.clear();
    inputFile.seekg(0);
    }
}

    std::string line;
    while (std::getline(inputFile, line)) {
        if (code == 0)
            outputFile << from_morse(line) << std::endl;
        else if (code == 1)
            outputFile << from_cesar(line, step) << std::endl;
        else if (code == 2)
            outputFile << from_ascii(line) << std::endl;
        else if (code == 3)
            outputFile << from_a1z26(line) << std::endl;
        else if (code == 4)
            outputFile << from_polybius(line) << std::endl;
        else
            outputFile << from_atbash(line) << std::endl;
}

    inputFile.close();
    outputFile.close();

    return 0;
}