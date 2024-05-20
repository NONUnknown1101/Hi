#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string name = "cat";
    string inputImagePath = name + ".jpg";
    string outputFilePath = name + "_output.txt";

    int targetWidth = 100;
    int targetHeight = 50;

    int width, height, channels;
    unsigned char* image = stbi_load(inputImagePath.c_str(), &width, &height, &channels, STBI_rgb);

    if (!image) {
        cerr << "Ошибка загрузки изображения: " << inputImagePath << endl;
        return 1;
    }

    double widthRatio = (double)targetWidth / width;
    double heightRatio = (double)targetHeight / height;

    char outputImage[targetHeight][targetWidth];

    for (int y = 0; y < targetHeight; y++) {
        for (int x = 0; x < targetWidth; x++) {
            int sourceX = (int)(x / widthRatio);
            int sourceY = (int)(y / heightRatio);

            int brightness = (image[(sourceY * width + sourceX) * 3] +
                             image[(sourceY * width + sourceX) * 3 + 1] +
                             image[(sourceY * width + sourceX) * 3 + 2]) / 3;

            if (brightness < 16) {
                outputImage[y][x] = ' ';
            } else if (brightness < 32) {
                outputImage[y][x] = '.';
            } else if (brightness < 64) {
                outputImage[y][x] = ',';   
            } else if (brightness < 96) {
                outputImage[y][x] = '-';            
            } else if (brightness < 128) {
                outputImage[y][x] = '*';
            } else if (brightness < 170) {
                outputImage[y][x] = 'o';
            } else if (brightness < 210) {
                outputImage[y][x] = 'O';
            } else {
                outputImage[y][x] = '@';
            }
        }
    }

    stbi_image_free(image);

    ofstream outputFile(outputFilePath);

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла для записи: " << outputFilePath << endl;
        return 1;
    }

    for (int y = 0; y < targetHeight; y++) {
        for (int x = 0; x < targetWidth; x++) {
            outputFile << outputImage[y][x];
        }
        outputFile << endl;
    }

    outputFile.close();

    cout << "Символьное представление изображения сохранено в файл: " << outputFilePath << endl;

    return 0;
}