# Nepali Calendar
![image](https://cloud.githubusercontent.com/assets/4928045/11301994/c059a502-8fc2-11e5-99fc-9875167f4eba.png)

## Overview
*Nepalical* is a calendar widget and appears on the bottom-left corner of the screen. It runs automatically on startup and also has an entry in application menu. It has two modes: *compact* and *full* which can be toggeled by mouse click.

```bash
# Manually run Nepalical from terminal
nepalical
```
*Nepaliconv* is a command-line conversion tool that converts Gregorian date to Nepali date and vice versa.

```bash
# Display current Nepali date
nepaliconv -bs -f "y.m.d"

# Convert Nepali to Gregorian
nepaliconv -ad 2072.0925
```

To display help and learn about other options, use a ```-h``` option.

## Installing
Checkout the latest sources:

    git clone https://github.com/tnagorra/nepalical

Install nepaliconv:

```bash
make nepaliconv
sudo make install-conv
```

Install nepalical:

```bash
# Get dependencies
sudo apt-get install libgtkmm-3.0-dev ttf-indic-fonts

# Install
make nepalical
sudo make install-cal
```

## License
It is distributed under [GNU GPL][1]. A copy of the license is available in the distributed LICENSE file.


[1]: http://www.gnu.org/licenses/gpl.txt
