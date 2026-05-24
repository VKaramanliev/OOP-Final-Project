#include "../include/PGMImage.hpp"

#include <iostream>
#include <fstream>

PGMImage::PGMImage(const string& name) : Image(name), maxValue(255) {}

void PGMImage::load() {
    ifstream file(name);

    if (!file.is_open()) {
        cout << "Cannot open file: " << name << endl;
        return;
    }

    string format;
    file >> format;

    if (format != "P2") {
        cout << "Invalid file format!" << endl;
        file.close();
        return;
    }

    file >> width >> height >> maxValue;
    pixels.clear();
    pixels.resize(height, vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file >> pixels[i][j];
        }
    }

    file.close();
}

void PGMImage::save() const {
    saveas(name);
}

void PGMImage::saveas(const string& newName) const {
    ofstream file(newName);

    if (!file.is_open()) {
        cout << "Cannot save file: " << newName << endl;
        return;
    }

    file << "P2" << endl;
    file << width << height << endl;
    file << maxValue << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file << pixels[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}

void PGMImage::negative() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j] = maxValue - pixels[i][j];
        }
    }
}

void PGMImage::rotate(const string& direction) {
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
    height = oldWidth;
}