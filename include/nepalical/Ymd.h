#ifndef __YMD__
#define __YMD__

#include "nepalical/ex.h"
#include <iostream>
#include <cstring>
#include <string>

typedef unsigned short int suint;

class Ymd {
private:
    suint y, m, d;
public:
    // Constructor
    Ymd();

    Ymd(std::string text);

    // Constructor
    Ymd(suint y, suint m, suint d);

    // Copy Constructor
    Ymd(const Ymd& dd);

    // Relational operations
    bool operator==(const Ymd& sub) const;
    bool operator!=(const Ymd& sub) const;
    bool operator<(const Ymd& sub) const;
    bool operator<=(const Ymd& sub) const;
    bool operator>(const Ymd& sub) const;
    bool operator>=(const Ymd& sub) const;

    // Copy for Ymd
    Ymd& operator=(const Ymd& dd);

    // Get year from Ymd
    suint year() const;

    // Get year from Ymd
    suint month() const;

    // Get year from Ymd
    suint day() const;
};

inline Ymd::Ymd(std::string text){
    char* str;
    char* pch;
    try {
        str = strcpy((char*)malloc(text.length()+1), text.c_str());
        y = std::stoi(std::strtok (str,".-/"));
        m = std::stoi(strtok (NULL,".-/"));
        d = std::stoi(strtok (NULL,".-/"));
        delete []str;
    } catch (...) {
        delete []str;
        throw InputNotGood();
    }
}

inline Ymd::Ymd():
    y(1), m(1), d(1) {
}

inline Ymd::Ymd(suint y, suint m, suint d):
    y(y), m(m), d(d) {
}

inline Ymd::Ymd(const Ymd& dd):
    y(dd.y), m(dd.m), d(dd.d) {
}

inline suint Ymd::year() const {
    return y;
}

inline suint Ymd::month() const {
    return m;
}

inline suint Ymd::day() const {
    return d;
}

inline Ymd& Ymd::operator=(const Ymd& dd) {
    if (dd != *this) {
        y = dd.y;
        m = dd.m;
        d = dd.d;
    }
    return *this;
}

inline bool Ymd::operator<(const Ymd& sub) const {
    return  y < sub.y || (y == sub.y && m < sub.m) ||
            (y == sub.y && m == sub.m && d < sub.d);
}

inline bool Ymd::operator>(const Ymd& sub) const {
    return y > sub.y || (y == sub.y && m > sub.m) ||
           (y == sub.y && m == sub.m && d > sub.d);
}

inline bool Ymd::operator==(const Ymd& sub) const {
    return y == sub.y && m == sub.m && d == sub.d;
}

inline bool Ymd::operator!=(const Ymd& sub) const {
    return  y != sub.y || m != sub.m || d != sub.d;
}

inline bool Ymd::operator<=(const Ymd& sub) const {
    return operator==(sub) || operator<(sub);
}

inline bool Ymd::operator>=(const Ymd& sub) const {
    return operator==(sub) || operator>(sub);
}

#endif
