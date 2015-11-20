# Nepali Calendar

Nepalical is a calendar widget built using GTK.

![image](https://cloud.githubusercontent.com/assets/4928045/11301994/c059a502-8fc2-11e5-99fc-9875167f4eba.png)


## Overview
The calendar widget appears on the bottom-left corner of the screen on startup and includes two modes: *compact* and *full*. The modes can be toggled using a click event. You can manually run the calendar using:

    nepalical

A command-line conversion tool is also installed to convert Gregorian date to Nepali date and vice versa. You can run the converter using:

    nepaliconv


## Installing
Checkout the latest sources with:

    git clone https://github.com/tnagorra/nepalical

Install the application with:

```bash
# Get dependencies and fonts
sudo apt-get install libgtkmm-3.0-dev
sudo apt-get install ttf-indic-fonts

# Installation
make
sudo make install
```

## License
It is distributed under [GNU GPL][1]. A copy of the license is available in the distributed LICENSE file.


[1]: http://www.gnu.org/licenses/gpl.txt


