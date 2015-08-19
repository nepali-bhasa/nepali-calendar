#include "nepalical/AdData.h"

const Ymd AdData::minimum(1944,1,1);
const Ymd AdData::maximum(2034,4,12);

const suint AdData::data[][13] = {
    {31,28,31,30,31,30,31,31,30,31,30,31,365},
    {31,29,31,30,31,30,31,31,30,31,30,31,366}
};

