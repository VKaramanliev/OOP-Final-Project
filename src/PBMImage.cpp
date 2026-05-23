#include "../include/PBMImage.hpp"

#include <iostream>
#include <fstream>

PBMImage::PBMImage(const string& name) : Image(name) {}

void PBMImage::load() {
    ifstream file(name);

    if (!file.is_open()) {
        cout << "Cannot open file: " << name << endl;
        return;
    }

    string format;
    file >> format;

    if (format != "P1") {
        cout << "Invalid file!" << endl;
        file.close();
        return;
    }

    file >> width >> height;
    pixels.clear(); // изчиства старата снимка преди да се сложи новата
    pixels.resize(height, vector<int>(width));

    int value;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file >> value;

            if (value != 0 && value != 1) {
                cout << "Invalid pixel value!" << endl;
                return;
            }

            pixels[i][j] = value;
        }
    }

    file.close();
}

void PBMImage::save() const {
    ofstream file(name);

    if (!file.is_open()) {
        cout << "Cannot save file: " << name << endl;
        return;
    }

    file << "P1" << endl;
    file << width << " " << height << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << pixels[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}

void PBMImage::saveas(const string& newName) const {
    ofstream file(newName);

    if (!file.is_open()) {
        cout << "Cannot save file: " << newName << endl;
        return;
    }

    file << "P1" << endl;
    file << width << " " << height << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << pixels[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}

void PBMImage::negative() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j] = 1 - pixels[i][j];
        }
    }
}

void PBMImage::rotate(const string& direction) {
    vector<vector<int>> rotated;

    if (direction == "right") {
        rotated.resize(width, vector<int>(height));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                rotated[j][height - 1 - i] = pixels[i][j];
            }
        }
    } else if (direction == "left") {
        rotated.resize(width, vector<int>(height));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                rotated[width - 1 - j][i] = pixels[i][j];
            }
        }
    } else {
        cout << "Invalid rotate direction. You should use only left or right!" << endl;
        return;
    }

    pixels = rotated;

    int oldWidth = width;
    width = height;
    height = width;
}