#include "nepalical/Ad.h"
#include "nepalical/Bs.h"

// Ad::Ad():Date(new AdData()) {}

Ad::Ad(suint y,suint m,suint d):Date(y,m,d,new AdData()) {}

Ad::Ad(const Ymd& a):Date(a,new AdData()) {}

Ad::Ad(const Ad& a):Date(a.daet,new AdData()) {}

Ad::Ad(const Bs& b):Date() {
    data =  new AdData();
    Ad temp( Ad(data->min()) + b.total() );
    daet = temp.daet;
    totalDays = difference(data->min());
}

Ad::Ad():Date() {
    data =  new AdData();

    // Get system date;
    time_t rawtime = time(NULL);
    struct tm * timeinfo = localtime(&rawtime);
    // Create an Ad object using system date and Bs object from Ad
    Ad temp(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    daet = temp.daet;

    totalDays = difference(data->min());
}


int Ad::operator-(const Ad& b) const {
    return difference(b.daet);
}

Ad Ad::operator-(int no) const {
    return difference(no);
}

Ad Ad::operator+(int no) const {
    return Ad(addition(no));
}

