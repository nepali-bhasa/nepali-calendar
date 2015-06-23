#include "../include/Ad.h"
#include "../include/Bs.h"

Ad::Ad():Date(new AdData()) {}

Ad::Ad(suint y,suint m,suint d):Date(y,m,d,new AdData()) {}

Ad::Ad(const Ymd& a):Date(a,new AdData()) {}

Ad::Ad(const Ad& b):Date(b.daet,new AdData()) {}

Ad::Ad(const Bs& b):Date() {
    data =  new AdData();
    Ad temp( Ad(data->min()) + b.total() );
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

