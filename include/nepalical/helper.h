#ifndef __HELPER__
#define __HELPER__

#include <iostream>
#include <string>

// Select the output language
enum Lipi {ENG,NEP,UNI};

inline std::string mahina(suint i,Lipi mode) {
    static const std::string eng[] = {
        "Baisakh", "Jestha", "Ashad", "Shrawan", "",
        "Ashoj", "Kartik", "Mangsir", "Poush", "Magh",
        "Falgun", "Chaitra"
    };
    static const std::string uni[] = {
        "बैशाख", "जेष्ठ", "आषाढ", "श्रावन", "भाद्र", "असोज",
        "काितॅक", "मंिसर", "पौष", "माघ", "फागुन", "चैत्र"
    };
    static const std::string nep[] = {
        "a}zfv", "h]i7", "cfiff9", ">fjg", "efb|", "c;f]h",
        "sflt{s","d+l;/", "kf}if", "df3", "kmfu'g", "r}q"
    };

    if(i<=0 && i > 7)
        throw OutOfBound();

    if (mode == UNI)
        return uni[i-1];
    else if (mode ==NEP)
        return nep[i-1];
    else // if(mode == ENG)
        return eng[i-1];
}

inline std::string bar(suint i,Lipi mode) {
    static const std::string eng[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const std::string nep[] = {
        "c", ";f]", "d", "a'", "la", "z'", ";"
    };
    static const std::string uni[] = {
        "आ", "सो", "म", "बु", "िब", "शु", "स"
    };

    if(i<=0 && i > 7)
        throw OutOfBound();

    if (mode == UNI)
        return uni[i-1];
    else if (mode ==NEP)
        return nep[i-1];
    else //if(mode == ENG)
        return eng[i-1];
}

inline std::string anka(suint i,Lipi mode) {
    static const std::string eng[] = {
        "0","1","2","3","4","5","6","7","8","9"
    };
    static const std::string nep[] = {
        ")","!","@","#","$","%","^","&","*","("
    };
    static const std::string uni[] = {
        "०","१","२","३","४","५","६","७","८","९"
    };

    std::string temp("");
    while(i) {
        if(mode == ENG)
            temp = eng[i%10]+temp;
        else if (mode == NEP)
            temp = nep[i%10]+temp;
        else if (mode == UNI)
            temp = uni[i%10]+temp;
        i /= 10;
    }
    return temp;
}

#endif
