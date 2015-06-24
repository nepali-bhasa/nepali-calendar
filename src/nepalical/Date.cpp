#include "nepalical/Date.h"

Ymd Date::addition(int no) const {

    if(no < 0) {
        return difference(-no);
    } else if(no == 0) {
        return this->daet;
    }

    suint y = daet.year(), m = daet.month(), d = daet.day();
    int n = 0;

    for(int i=m+1; i<=12; ++i)
        n += data->get(y,i);

    n += data->get(y,m) - d + 1;


    if(n <= no && data->get(y,13) != -1) {
        ++y;
        while(n+data->get(y,13) <= no && data->get(y,13) != -1 ) {
            n+=data->get(y,13);
            ++y;
        }
        m=1;

        if(data->get(y,13) == -1) {
            std::cout << "Out of Bounds in addition()" << std::endl;
            //throw OutOfBound();
            return this->daet;
        }

        while(n+data->get(y,m) <= no && m<12 ) {
            n+=data->get(y,m);
            ++m;
        }
        d=1;
        d += no-n;

    } else {
        n = data->get(y,m)-d+1;
        if (n < no) {
            ++m;
            while(n+data->get(y,m) <= no) {
                n+=data->get(y,m);
                ++m;
            }
            d = no-n+1;
        } else {
            d += no;
        }
    }
    return Ymd(y,m,d);
}

Ymd Date::difference(int no) const {

    if(no < 0) {
        return addition(-no);
    } else if (no == 0) {
        return this->daet;
    }

    suint y = daet.year(), m = daet.month(), d = daet.day();
    int n = 0;

    for(int i=m-1; i>=1; --i)
        n += data->get(y,i);

    n += d;

    if(n <= no ) {

        --y;
        while(n+data->get(y,13) <= no && data->get(y,13) != -1 ) {
            n+=data->get(y,13);
            --y;
        }
        m=12;

        if(data->get(y,13) == -1) {
            std::cout << "Out of Bounds in subtraction()" << std::endl;
            //throw OutOfBound();
            return this->daet;
        }

        while(n+data->get(y,m) <= no && m>1 ) {
            n+=data->get(y,m);
            --m;
        }

        d = data->get(y,m) -(no-n);

    } else {
        n = d;
        if (n <= no) {
            --m;
            while(n+data->get(y,m) <= no) {
                n+=data->get(y,m);
                --m;
            }
            d = data->get(y,m) -(no-n);
        } else {
            d = d - no;
        }
    }
    return Ymd(y,m,d);
}


void Date::checkBounds() {
    if( daet > data->max() )
        daet=data->max();
    else if( daet < data->min() )
        daet=data->min();
}

// TODO what have I done here?
void Date::validate() {
    suint y = daet.year(), m = daet.month(), d = daet.day();

    try {
        if(m > 12)
            throw MonthExceeded();
        else if(d > data->get(y,m))
            throw DayExceeded();
    } catch ( MonthExceeded& e) {
        m  = 12;
    } catch ( DayExceeded& e) {
        d = data->get(y,m);
    }
    daet = Ymd(y,m,d);
}

int Date::difference(const Ymd& sub) const {

    suint y,m,d,y1,m1,d1;
    int sign;
    if (daet > sub) {
        y = daet.year(), m = daet.month(), d = daet.day();
        y1 = sub.year(), m1 = sub.month(), d1 = sub.day();
        sign = 1;
    } else {
        y1 = daet.year(), m1 = daet.month(), d1 = daet.day();
        y = sub.year(), m = sub.month(), d = sub.day();
        sign = -1;
    }

    if (data->get(y,13) == -1)
        return 0;
    if (data->get(y1,13) == -1)
        return 0;

    int no = 0;

    if(y != y1) {

        for (int i=(m1+1); i<=12; ++i)
            no += data->get(y1,i);

        no += data->get(y1,m1) - d1 + 1;

        for(int i=y1+1; i<y; i++)
            no += data->get(i,13);

        for (int i=1; i<m; ++i)
            no += data->get(y,i);

        no += d;
        no--;

    } else if (m!=m1) {

        no += data->get(y,m1) - d1 + 1 ;
        for (int i=m1+1; i<m; ++i)
            no += data->get(y,i);
        no += d;
        no--;

    } else {
        no = d-d1;
    }

    return sign*no;
}


