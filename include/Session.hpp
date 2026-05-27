#ifndef SESSION_HPP
#define SESSION_HPP

#include "Image.hpp"
#include "Transformation.hpp"

#include <vector>


class Session {
    private:
        int id;
        vector<Image*> images;
        vector<Transformation> transformations;

        void applyTransformation(Image* image, const Transformation& transformation);

    public:
        Session(int id);

        void addImage(Image* image);
        void grayscale();
        void monochrome();
        void negative();
        void rotate(const string& direction);

        void undo();
        void save();
        void saveas(const string& fileName);
        void info() const;

        int getId() const;

        ~Session();
};

#endif