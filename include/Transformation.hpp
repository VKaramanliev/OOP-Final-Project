#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include <string>

using namespace std;

struct Transformation {
    string name;
    string argument;

    Transformation(const string& name, const string& argument) : name(name), argument(argument) {}

    string toString() const {
        if (argument.empty()) {
            return name;
        }

        return name + " " + argument;
    }
};

#endif