#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>


#include "wifr.hpp"

using namespace chrono;

int step;
string key;

void encodeFile(const std::string& inputPath, const std::string& encoding) {
    std::ifstream inputFile(inputPath);
    std::ofstream outputFile("one_" + encoding + "_" + inputPath);

    std::string line;
    Wifr eng;

    while (std::getline(inputFile, line)) {
        if (encoding == "morse")
            outputFile << eng.morse(line) << endl;
        else if (encoding == "cesar")
            outputFile << eng.cesar(line, step) << endl;
        else if (encoding == "vignere")
            outputFile << eng.vignere(line, key) << endl;
        else if (encoding == "ascii")
            outputFile << eng.ascii(line) << endl;
        else if (encoding == "a1z26")
            outputFile << eng.a1z26(line) << endl;
        else if (encoding == "polybius")
            outputFile << eng.polybius(line) << endl;
        else if (encoding == "atbash")
            outputFile << eng.atbash(line) << endl;

    }
    
    inputFile.close();
    outputFile.close();
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
            cout << "Выберите шаг / Choose a step: ";
            cin >> step;

            cout << "Введите ключ / Enter the key: ";
            cin >> key;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    std::vector<std::string> encodings = {"morse", "cesar", "vignere", "ascii", "a1z26", "polybius", "atbash"};

        streampos begin_symb, stop_symb;
        ifstream myfile(inputPath);
        begin_symb = myfile.tellg();
        myfile.seekg(0, ios::end);
        stop_symb = myfile.tellg();

        string low_key;
        for (char k: key){
            if (k <= 'Z' & k >= 'A')
                low_key += tolower(k);
            else if (k <= 'z' & k >= 'a')
                low_key += k;
        }
        key = low_key;
        std::cout << "Новый ключ / New key is: " << key << endl;
        std::cout << endl;

        system_clock::time_point start = system_clock::now();;
        system_clock::time_point end;

        for (const auto& encoding : encodings)
            encodeFile(inputPath, encoding);

        end = system_clock::now();
        duration<float> sec = end - start;

        std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

        std::cout << "Длина файла (символы) / Length of file (symbols): " << (stop_symb - begin_symb) << endl;
        std::cout << endl;

        std::cout << "Прошло " << sec.count() << " сек. /" << sec.count() << " sec. passed" << endl;
    return 0;
}




