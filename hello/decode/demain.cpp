#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "fromwifr.hpp"


using namespace std;



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

    string encodings[] = {"morse", "cesar", "vignere", "ascii", "a1z26", "polybius", "atbash"};
    cout << "Шифр / Code: " << endl;
    for (int i = 0; i < 7; i++){
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
    string key;
    From_Wifr eng;

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
            std::cout << "Шаг / Step " << i << ": " << eng.from_cesar(word, i) << std::endl;

        std::cout << "Выберите шаг / Choose a step: ";
        std::cin >> step;

        inputFile.clear();
        inputFile.seekg(0);
        }

    }

    if (code == 2){
        std::cout << "Введите ключ / Enter the key: ";
        std::cin >> key;
    }


    std::string line;
    while (std::getline(inputFile, line)) {
        if (code == 0)
            outputFile << eng.from_morse(line) << std::endl;
        else if (code == 1)
            outputFile << eng.from_cesar(line, step) << std::endl;
        else if (code == 2)
            outputFile << eng.from_vignere(line, key) << std::endl;
        else if (code == 3)
            outputFile << eng.from_ascii(line) << std::endl;
        else if (code == 4)
            outputFile << eng.from_a1z26(line) << std::endl;
        else if (code == 5)
            outputFile << eng.from_polybius(line) << std::endl;
        else
            outputFile << eng.from_atbash(line) << std::endl;
}

    inputFile.close();
    outputFile.close();

    return 0;
}