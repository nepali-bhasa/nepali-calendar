#include <algorithm>
#include <iostream>
#include <string>

#include "nepalical/Ad.h"
#include "nepalical/Bs.h"
#include "nepalical/helper.h"

std::string getCmdOption(char ** begin, char ** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

// TODO:
// move mahina/bar to respective classes and use virtual functions
// fix padding
// better command line options

// Parse
void printNepaliDate(Date& d, std::string& format, Lipi lipi){
    for(int i=0; i<format.length(); i++){
        switch (format[i]){
            case 'y': std::cout << anka(d.year(), lipi); break;
            case 'm': std::cout << anka(d.month(), lipi); break;
            case 'd': std::cout << anka(d.day(), lipi); break;
            case 'w': std::cout << anka(d.week(), lipi); break;
            case 'M': std::cout << mahina(d.month(), lipi); break;
            case 'W': std::cout << bar(d.week(), lipi); break;
            default: std::cout << format[i]; break;
        }
    }
    std::cout << std::endl;
}

void printEnglishDate(Date& d, std::string& format){
    for(int i=0; i<format.length(); i++){
        switch (format[i]){
            case 'y': std::cout << anka(d.year(), ENG); break;
            case 'm': std::cout << anka(d.month(), ENG); break;
            case 'd': std::cout << anka(d.day(), ENG); break;
            case 'w': std::cout << anka(d.week(), ENG); break;
            case 'M': std::cout << month(d.month()); break;
            case 'W': std::cout << bar(d.week(), ENG); break;
            default: std::cout << format[i]; break;
        }
    }
    std::cout << std::endl;
}

// Parse
void printEnglishDate(Date& d, std::string& format, Lipi lipi){
    for(int i=0; i<format.length(); i++){
        switch (format[i]){
            case 'y': std::cout << anka(d.year(), lipi); break;
            case 'm': std::cout << anka(d.month(), lipi); break;
            case 'd': std::cout << anka(d.day(), lipi); break;
            case 'w': std::cout << anka(d.week(), lipi); break;
            case 'M': std::cout << mahina(d.month(), lipi); break;
            case 'W': std::cout << bar(d.week(), lipi); break;
            default: std::cout << format[i]; break;
        }
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    Lipi lipi = ENG;
    if (cmdOptionExists(argv, argv + argc, "-N")) {
        lipi = NEP;
    } else if (cmdOptionExists(argv, argv + argc, "-E")) {
        lipi = ENG;
    } else if (cmdOptionExists(argv, argv + argc, "-U")) {
        lipi = UNI;
    }

    std::string format;
    if (cmdOptionExists(argv, argv + argc, "-f")) {
        format = getCmdOption(argv, argv + argc, "-f");
    }
    if (format==""){
        format = "W y.m.d";
    }


    if (cmdOptionExists(argv, argv + argc, "-h")) {
        std::cout <<
"Usage:\n\
nepaliconv [-h] (-n [yyyy.mm.dd] (-E | -U | -N) | -e [yyyy.mm.dd]) [-f FORMAT]\n\
\n\
Options:\n\
-h                  Show this help\n\
-n yyyy.mm.dd       Convert to B.S.\n\
-e yyyy.mm.dd       Convert to A.D.\n\
-E                  Display in English\n\
-U                  Display in Nepali (Unicode)\n\
-N                  Display in Nepali (Bakaman)\n\
-f FORMAT           Define display format (Ex. y-m-d M W/w)"
        << std::endl;

    } else if (cmdOptionExists(argv, argv + argc, "-n")) {

        Bs* b;
        std::string date = getCmdOption(argv, argv + argc, "-n");
        if (date == "") {
            b = new Bs();
        } else {
            Ymd x(date);
            Ad a(x);
            b = new Bs(a);
        }
        // Printing part
        printNepaliDate(*b, format, lipi);
        delete b;

    } else if (cmdOptionExists(argv, argv + argc, "-e")) {

        Ad* a;
        std::string date = getCmdOption(argv, argv + argc, "-e");
        if (date == "") {
            a = new Ad();
        } else {
            Ymd x(date);
            Bs b(x);
            a = new Ad(b);
        }
        printEnglishDate(*a, format);
        delete a;

    } else {
        std::cout << "You need help, sucker! Try -h" << std::endl;
    }

    return 0;
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
