#include <algorithm>
#include <iostream>
#include <string>

#include "nepalical/Ad.h"
#include "nepalical/Bs.h"
#include "nepalical/helper.h"

std::string getCmdOption(char ** begin, char ** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);
void printDate(Date& d, std::string& format, Lipi lipi);

const std::string helptxt = \
"USAGE:\n\
    nepaliconv (-bs (-e|-u|-n) [yyyy.mm.dd] | -ad [yyyy.mm.dd])\n\
    [-f FORMAT] [-h]\n\
\n\
OPTIONS:\n\
    -h              Show help\n\
    -bs YYYY.MM.DD  Convert to B.S.\n\
    -ad YYYY.MM.DD  Convert to A.D.\n\
    -e              Display in English\n\
    -u              Display in Nepali Unicode\n\
    -n              Display in Nepali Bakaman\n\
    -f FORMAT       Define display format\n\
\n\
FORMAT:\n\
    y   year\n\
    m   month\n\
    d   day\n\
    w   weekday\n\
    M   month name\n\
    W   weekday name\n\
\n\
EXAMPLES:\n\
    Show today's Nepali date in Unicode\n\
        nepaliconv -bs -u\n\
\n\
    Show today's Gregorian date wth year and month\n\
        nepaliconv -ad -f y.m\n\
\n\
    Convert given Gregorian date to Nepali date\n\
        nepaliconv -bs 2012.10.14    \n\
\n\
    Convert given Nepali date to Gregorian date\n\
        nepaliconv -ad 2061.11.12\n\
";

int main(int argc, char* argv[]) {

    // Display help
    if (cmdOptionExists(argv, argv + argc, "-h")) {
        std::cout << helptxt << std::endl;
        exit(0);
    }

    // Get the language for output
    Lipi lipi = ENG;
    if (cmdOptionExists(argv, argv + argc, "-n"))
        lipi = NEP;
    else if (cmdOptionExists(argv, argv + argc, "-e"))
        lipi = ENG;
    else if (cmdOptionExists(argv, argv + argc, "-u"))
        lipi = UNI;

    // Get the format for output
    std::string format = "y.m.d W";
    if (cmdOptionExists(argv, argv + argc, "-f")){
        std::string fmt = getCmdOption(argv, argv + argc, "-f");
        if (fmt!="")
            format = fmt;
    }

    if (cmdOptionExists(argv, argv + argc, "-bs")) {
        Bs* b;
        std::string date = getCmdOption(argv, argv + argc, "-bs");
        if (date == "") {
            b = new Bs();
        } else {
            Ymd x(date);
            Ad a(x);
            b = new Bs(a);
        }
        printDate(*b, format, lipi);
        delete b;

    } else if (cmdOptionExists(argv, argv + argc, "-ad")) {
        Ad* a;
        std::string date = getCmdOption(argv, argv + argc, "-ad");
        if (date == "") {
            a = new Ad();
        } else {
            Ymd x(date);
            Bs b(x);
            a = new Ad(b);
        }
        printDate(*a, format, ENG);
        delete a;

    } else {
        std::cout << "Looks like you need some help! Try -h" << std::endl;
    }

    return 0;
}

void printDate(Date& d, std::string& format, Lipi lipi){
    for(int i=0; i<format.length(); i++){
        switch (format[i]){
            case 'y': std::cout << anka(d.year(), lipi); break;
            case 'm': std::cout << anka(d.month(), lipi, 2); break;
            case 'd': std::cout << anka(d.day(), lipi, 2); break;
            case 'w': std::cout << anka(d.week(), lipi); break;
            case 'M': std::cout << mahina(d.month(), lipi); break;
            case 'W': std::cout << bar(d.week(), lipi); break;
            default: std::cout << format[i]; break;
        }
    }
    std::cout << std::endl;
}

std::string getCmdOption(char ** begin, char ** end, const std::string & option) {
    char ** itr = std::find(begin, end, option);
    // '-' check to see if it is not an option
    if (itr != end && ++itr != end and *itr[0] != '-') {
        return std::string(*itr);
    }
    return "";
}

bool cmdOptionExists(char** begin, char** end, const std::string& option) {
    return std::find(begin, end, option) != end;
}
