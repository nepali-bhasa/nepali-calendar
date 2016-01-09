# Nepali Calendar

Nepalical is a calendar widget built using GTKmm and also includes a date converter.

![image](https://cloud.githubusercontent.com/assets/4928045/11301994/c059a502-8fc2-11e5-99fc-9875167f4eba.png)


## Overview
The calendar widget appears on the bottom-left corner of the screen on startup and includes two modes: *compact* and *full*. The modes can be toggled using a click event. You can manually run the calendar using:

    nepalical

A command-line conversion tool is also installed to convert Gregorian date to Nepali date and vice versa. To display current Nepali date, run:

    nepaliconv -n -format "y.m.d"

To display help and learn about other options, use a ```-h``` option.

## Installing
Checkout the latest sources with:

    git clone https://github.com/tnagorra/nepalical

Install the application with:

```bash
# Get dependencies
sudo apt-get install libgtkmm-3.0-dev ttf-indic-fonts

# Installation
make
# Install nepali calendar widget
sudo make install
# Install nepali converter tool
sudo make install-nepaliconv
```

## License
It is distributed under [GNU GPL][1]. A copy of the license is available in the distributed LICENSE file.


[1]: http://www.gnu.org/licenses/gpl.txt

