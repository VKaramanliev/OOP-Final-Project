#include "../include/Session.hpp"

#include <iostream>

Session::Session(int id) : id(id) {}

void Session::copy(const Session& other) {
    id = other.id;
    transformations = other.transformations;

    for (Image* image : other.images) {
        images.push_back(image->clone());
    }
}

Session::Session(const Session& other) {
    copy(other);
}

Session& Session::operator=(const Session& other) {
    if (this != &other) {
        for (Image* image : images) {
            delete image;
        }
        images.clear();

        copy(other);
    }

    return *this;
}

Session::Session(Session&& other) noexcept {
    id = other.id;

    images = move(other.images);
    transformations = move(other.transformations);

    other.images.clear();
}

Session& Session::operator=(Session&& other) noexcept {
    if (this != &other) {
        for (Image* image : images) {
            delete image;
        }

        id = other.id;
        images = move(other.images);
        transformations = move(other.transformations);

        other.images.clear();
    }

    return *this;
}

void Session::addImage(Image* image) {
    images.push_back(image);
    cout << "Image " << image->getName() << " added" << endl;
}

void Session::grayscale() {
    transformations.push_back(Transformation("grayscale", ""));
    cout << "Grayscale transformation added." << endl;
}

void Session::monochrome() {
    transformations.push_back(Transformation("monochrome", ""));
    cout << "Monochrome transformation added." << endl;
}

void Session::negative() {
    transformations.push_back(Transformation("negative", ""));
    cout << "Negative transformation added." << endl;
}

void Session::rotate(const string& direction) {
    if (direction != "left" && direction != "right") {
        cout << "Invalid rotation!" << endl;
        return;
    }

    transformations.push_back(Transformation("rotate", direction));
    cout << "Rotate " << direction << "transformation added." << endl;
}

void Session::applyTransformation(Image* image, const Transformation& transformation) {
    if (transformation.name == "grayscale") {
        image->grayscale();
    } else if (transformation.name == "monochrome") {
        image->monochrome();
    } else if (transformation.name == "negative") {
        image->negative();
    } else if (transformation.name == "rotate") {
        image->rotate(transformation.argument);
    }
}

void Session::undo() {
    if (transformations.empty()) {
        cout << "No transformations to undo." << endl;
        return;
    }

    transformations.pop_back();
}

void Session::save() {
    for (Image* image : images) {
        for (const Transformation& transformation : transformations) {
            applyTransformation(image, transformation);
        }

        image->save();
    }

    transformations.clear();
    cout << "Session saved!" << endl;
}

void Session::saveas(const string& fileName) {
    if (images.empty()) {
        cout << "No images." << endl;
        return;
    }

    for (Image* image : images) {
        for (const Transformation& transformation : transformations) {
            applyTransformation(image, transformation);
        }
    }

    images[0]->saveas(fileName);
    transformations.clear();

    cout << "Image saved as " << fileName << endl; 
}

void Session::info() const {
    cout << "Name of images in the session: ";

    for (Image* image : images) {
        cout << image->getName() << ", ";
    }
    cout << endl;

    cout << "Pending transformations: ";

    if (transformations.empty()) {
        cout << "None" << endl;
        return;
    }

    for (const Transformation& transformation : transformations) {
        cout << transformation.toString() << ", ";
    }
    cout << endl;
}

int Session::getId() const {
    return id;
}

Session::~Session() {
    for (Image* image : images) {
        delete image;
    }

    images.clear();
}