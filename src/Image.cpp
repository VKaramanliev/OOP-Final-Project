#include "../include/Image.hpp"

Image::Image(const string& name) : name(name), width(0), height(0) {}

string Image::getName() const {
    return name;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}