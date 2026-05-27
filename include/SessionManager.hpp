#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include "Session.hpp"

class SessionManager {
    private:
        vector<Session*> sessions;
        int current;
        int next;

    public:
        SessionManager();

        void createSession(const vector<Image*>& images);
        void switchSession(int id);
        void closeSession();

        Session* getCurrentSession() const;

        bool hasCurrentSession() const;

        ~SessionManager();
};

#endif