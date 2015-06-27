#include "nepalical/Bs.h"
#include "nepalical/Ad.h"


// Bs::Bs():Date(new BsData()) {}

Bs::Bs(suint y,suint m,suint d):Date(y,m,d,new BsData()) {}

Bs::Bs(const Ymd& a):Date(a,new BsData()) {}

Bs::Bs(const Bs& b):Date(b.daet,new BsData()) {}

Bs::Bs(const Ad& b):Date() {
    data = new BsData();
    Bs temp( Bs(data->min()) + b.total() );
    daet = temp.daet;
    totalDays = difference(data->min());
}

Bs::Bs():Date() {
    data = new BsData();

    Ad temp;
    daet = Bs(temp).daet;
    totalDays = difference(data->min());
}


int Bs::operator-(const Bs& b) const {
    return difference(b.daet);
}

Bs Bs::operator+(int no) const {
    return Bs(addition(no));
}

Bs Bs::operator-(int no) const {
    return difference(no);
}

Ad Bs::firstday() const {
    return Ad(Bs(daet.year(),daet.month(),1));
}
