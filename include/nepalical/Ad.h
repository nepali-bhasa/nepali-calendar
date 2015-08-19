#ifndef __AD__
#define __AD__

#include "nepalical/Date.h"
#include "nepalical/AdData.h"
class Bs;

class Ad:public Date {
public:
    Ad();
    Ad(suint y,suint m,suint d);
    Ad(const Ymd& a);
    Ad(const Ad& b);
    Ad(const Bs& b);
    int operator-(const Ad& b) const;
    Ad operator-(int no) const;
    Ad operator+(int no) const;
};
#endif
