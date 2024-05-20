#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string encryptVigenere(string text, string key) {
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

string decryptVigenere(string text, string key) {
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

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream encryptedFile("encrypted.txt");
    std::ofstream decryptedFile("decrypted.txt");

    std::string text;
    std::string key = "key";

    if (inputFile.is_open()) {
        while (getline(inputFile, text)) {
            std::string encryptedText = encryptVigenere(text, key);
            encryptedFile << encryptedText << std::endl;
            decryptedFile << decryptVigenere(encryptedText, key) << std::endl;
        }

        inputFile.close();
        encryptedFile.close();
        decryptedFile.close();
        std::cout << "Encryption and decryption completed successfully." << std::endl;
    } else {
        std::cerr << "Error opening the input file." << std::endl;
    }

    return 0;
}