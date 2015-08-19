#ifndef __BSDATA__
#define __BSDATA__

#include "nepalical/Data.h"

class BsData:public Data {
private:
    static const suint data[][13];
    static const Ymd minimum,maximum;
public:
    int get(suint y, suint m) const;
    int get(suint y) const;
    const Ymd& min() const;
    const Ymd& max() const;
};


inline int BsData::get(suint y) const {
    get(y,13);
}

inline int BsData::get(suint y,suint m) const {
    if (m > 12+1 || m == 0 )
        throw OutOfBound();
        // return -1;
    if (y < minimum.year() || y > maximum.year() )
        throw OutOfBound();
        //return -1;
    return data[y - minimum.year()][m-1];
}

inline const Ymd& BsData::min() const {
    return minimum;
}

inline const Ymd& BsData::max() const {
    return maximum;
}
#endif
