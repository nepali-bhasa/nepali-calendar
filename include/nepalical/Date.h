#ifndef __DATEE__
#define __DATEE__

#include "Ymd.h"
#include "Data.h"

class Date {
    protected:
        Ymd daet;
        Data* data;
        int difference(const Ymd& sub) const;
        Ymd difference(int no) const;
        Ymd addition(int no) const;
        int totalDays;
        void checkBounds();
        void validate();
    public:
        virtual ~Date()=0;
        Date();
        Date(Data* p);
        Date(const Ymd&a, Data* p);
        Date(int y,int m,int d,Data* p);
        suint year() const;
        suint month() const;
        suint day() const;
        int week() const;
        int total() const;
        suint daysInMonth() const;
        suint daysInYear() const;
};


inline Date::Date() {}

inline Date::Date(Data* p):data(p) {
    checkBounds();
    validate();
}

inline Date::Date(const Ymd&a, Data* p):daet(a),data(p) {
    checkBounds();
    validate();
    totalDays = difference(data->min());
}

inline Date::Date(int y,int m,int d,Data* p):daet(y,m,d),data(p) {
    checkBounds();
    validate();
    totalDays = difference(data->min());
}

inline Date::~Date() {
    delete data;
}

inline  int Date::total() const {
    return totalDays;
}

inline suint Date::year() const {
    return daet.year();
}

inline suint Date::month() const {
    return daet.month();
}

inline suint Date::day() const {
    return daet.day();
}
inline int Date::week() const {
    return  ( totalDays + 6) % 7 + 1;
}

inline suint Date::daysInMonth() const {
    return data->get(daet.year(),daet.month());
}

inline suint Date::daysInYear() const {
    return data->get(daet.year(),13);
}

#endif
