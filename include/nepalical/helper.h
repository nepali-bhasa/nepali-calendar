#ifndef __HELPER__
#define __HELPER__

#include <cmath>
#include <iostream>
#include <string>

// Select the output language
enum Lipi {ENG,NEP,UNI};

inline std::string month(suint i) {
    static const std::string eng[] = {
        "Jan", "Feb", "Mar", "Apr", "May",
        "Jun", "Jul", "Aug", "Sep", "Oct",
        "Nov", "Dec"
    };

    if(i<=0 || i > 12)
        throw OutOfBound();
    return eng[i-1];
}

inline std::string mahina(suint i,Lipi mode) {
    static const std::string eng[] = {
        "Baisakh", "Jestha", "Ashad", "Shrawan", "Bhadra",
        "Ashoj", "Kartik", "Mangsir", "Poush", "Magh",
        "Falgun", "Chaitra"
    };
    static const std::string uni[] = {
        "बैशाख", "जेष्ठ", "आषाढ", "श्रावन", "भाद्र", "असोज",
        "कार्तिक", "मंसिर", "पौष", "माघ", "फागुन", "चैत्र"
    };
    static const std::string nep[] = {
        "a}zfv", "h]i7", "cfiff9", ">fjg", "efb|", "c;f]h",
        "sflt{s","d+l;/", "kf}if", "df3", "kmfu'g", "r}q"
    };

    if(i<=0 || i > 12)
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

    if(i<=0 || i > 7)
        throw OutOfBound();

    if (mode == UNI)
        return uni[i-1];
    else if (mode ==NEP)
        return nep[i-1];
    else //if(mode == ENG)
        return eng[i-1];
}

inline std::string anka(suint x,Lipi mode, suint space=0) {
    static const std::string eng[] = {
        "0","1","2","3","4","5","6","7","8","9"
    };
    static const std::string nep[] = {
        ")","!","@","#","$","%","^","&","*","("
    };
    static const std::string uni[] = {
        "०","१","२","३","४","५","६","७","८","९"
    };

    const std::string* fmt;
    switch(mode){
        case ENG: fmt = eng; break;
        case NEP: fmt = nep; break;
        case UNI: fmt = uni; break;
        default: fmt = eng;
    }

    // Return if x is 0
    if (x==0)
        return fmt[0];

    std::string word("");
    for(int i=x; i>0;i/=10)
        word = fmt[i%10]+word;

    // Padding output with extra zeros
    int fill = space-((int)std::log10(x)+1);
    for (int i=0; i< fill;i++)
        word = fmt[0] + word;
    return word;
}

#endif
