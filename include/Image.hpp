#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

using namespace std;

class Image {
    protected:
        string name;
        int width;
        int height;

    public:
        Image(const string& name);

        virtual void load() = 0;
        virtual void save() const = 0;
        virtual void saveas(const string& newName) const = 0;

        virtual void grayscale() {};
        virtual void monochrome() {};
        virtual void negative() = 0;
        virtual void rotate(const string& direction) = 0;

        string getName() const;
        int getWidth() const;
        int getHeight() const;

        virtual ~Image() {}
};

#endif