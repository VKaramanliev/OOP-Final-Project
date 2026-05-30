#ifndef COMMAND_PROCESSOR_HPP
#define COMMAND_PROCESSOR_HPP

#include "SessionManager.hpp"

class CommandProcessor {
    private:
        SessionManager manager;
        bool running;

        vector<string> split(const string& line) const;
        Image* createImage(const string& fileName) const;

        void help() const;

    public:
        CommandProcessor();

        void run();
};

#endif