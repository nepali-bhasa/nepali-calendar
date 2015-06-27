#include "nepalical/Date.h"

void Date::checkBounds() {
    if ( daet > data->max() )
        daet = data->max();
    else if ( daet < data->min() )
        daet = data->min();
}

void Date::validate() {
    suint y = daet.year(), m = daet.month(), d = daet.day();

    if (m > 12)
        throw MonthExceeded();
    else if (d > data->get(y, m))
        throw DayExceeded();
}

Ymd Date::addition(int no) const {

    if (no == 0)
        return this->daet;
    else if (no < 0)
        return difference(-no);

    suint y = daet.year();
    suint m = daet.month();
    suint d = daet.day();

    // Get number of days 'n' till end of year
    int n = data->get(y, m) - d + 1;
    for (int i = m + 1; i <= 12; ++i)
        n += data->get(y, i);

    // If 'no' exceeds current year
    if (n <= no) {

        // Get year
        ++y;
        while (n + data->get(y) <= no) {
            n += data->get(y);
            ++y;
        }
        // Get month
        m = 1;
        while (n + data->get(y, m) <= no && m < 12 ) {
            n += data->get(y, m);
            ++m;
        }
        // Get day
        d = 1;
        d += no - n;

    } else {

        // Get number of days 'n' till end of month
        n = data->get(y, m) - d + 1;

        // If 'no' exceeds current month
        if (n < no) {
            // Get month
            ++m;
            while (n + data->get(y, m) <= no) {
                n += data->get(y, m);
                ++m;
            }
            // Get day
            d = no - n + 1;
        } else {
            // Get day
            d += no;
        }
    }
    return Ymd(y, m, d);
}



Ymd Date::difference(int no) const {

    if (no == 0)
        return this->daet;
    else if (no < 0)
        return addition(-no);

    suint y = daet.year();
    suint m = daet.month();
    suint d = daet.day();

    // Get number of days 'n' till beginning of year
    int n = d;
    for (int i = m - 1; i >= 1; --i)
        n += data->get(y, i);

    // If 'no' exceeds current year
    if (n <= no ) {

        // Get year
        --y;
        while (n + data->get(y) <= no) {
            n += data->get(y);
            --y;
        }
        // Get month
        m = 12;
        while (n + data->get(y, m) <= no && m > 1) {
            n += data->get(y, m);
            --m;
        }
        // Get date
        d = data->get(y, m) - (no - n);

    } else {

        // Get number of days 'n' till beginning of month
        n = d;

        // If 'no' exceeds current month
        if (n <= no) {
            // Get month
            --m;
            while (n + data->get(y, m) <= no) {
                n += data->get(y, m);
                --m;
            }
            // Get date
            d = data->get(y, m) - (no - n);
        } else {
            // Get date
            d = d - no;
        }

    }
    return Ymd(y, m, d);
}

int Date::difference(const Ymd & sub) const {

    int sign = 1;
    suint y, m, d;
    suint y1, m1, d1;

    if (daet > sub) {
        y = daet.year(), m = daet.month(), d = daet.day();
        y1 = sub.year(), m1 = sub.month(), d1 = sub.day();
        sign = 1;
    } else {
        y1 = daet.year(), m1 = daet.month(), d1 = daet.day();
        y = sub.year(), m = sub.month(), d = sub.day();
        sign = -1;
    }


    int no = 0;
    // If the years differ
    if (y != y1) {

        // Get number of days 'no' till end of year
        no = data->get(y1, m1) - d1 + 1;
        for (int i = (m1 + 1); i <= 12; ++i)
            no += data->get(y1, i);

        // Get number of days till the required year
        for (int i = y1 + 1; i < y; i++)
            no += data->get(i);

        // Get number of days till the required month
        for (int i = 1; i < m; ++i)
            no += data->get(y, i);

        // Get number of days till the required date
        no += d;
        no--;

    }
    // If the months differ
    else if (m != m1) {

        // Get number of days 'no' till end of month
        no = data->get(y, m1) - d1 + 1 ;

        // Get number of days till the required month
        for (int i = m1 + 1; i < m; ++i)
            no += data->get(y, i);

        // Get number of days till the required date
        no += d;
        no--;

    } else {

        // Get number of days till the required date
        no = d - d1;

    }

    return sign * no;
}
