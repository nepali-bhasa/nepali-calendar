#ifndef __ADDATA__
#define __ADDATA__

#include "nepalical/Data.h"

class AdData:public Data {
private:
    static const suint data[][13];
    // minumum,maximum date
    static const Ymd minimum,maximum;
    // returns if it is a leap year
    bool leap(suint y) const;
public:
    int get(suint y, suint m) const;
    const Ymd& min() const;
    const Ymd& max() const;
};

inline bool AdData::leap(suint y) const {
    return  ((y%4 == 0) && (y%100 != 0)) || (y%400 == 0);
}

inline int AdData::get(suint y,suint m) const {
    if(m > 12+1 || m == 0)
        return -1;
        //throw OutOfBound();
    return data[leap(y)][m-1];
}

inline const Ymd& AdData::min() const {
    return minimum;
}

inline const Ymd& AdData::max() const {
    return maximum;
}

#endif

