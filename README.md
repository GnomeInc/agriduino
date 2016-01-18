# agriduino
Python code for agriduino plant care system

## Description
* Arduino folder contains a sketch current written for Uno.  It waits for commands from a raspberry pi.
* Raspberry pi runs python scripts set up as CRON jobs which periodically send signals to read data from sensors or water the plants. A more intuitive interface will be forthcoming.
* Hardware folder has current fritzing files and partslist.

## TODO
Set up web server on Pi which will load data from CSV file and display it graphically and have web interface.  Likely done in php/html/css.  Build tables and charts in plot.ly maybe.  Or I'll check out python graphic libraries.

## CRON Jobs currently running
```
* * * * * /usr/bin/python /home/pi/agriduino/read_sensors.py
0 7 * * * /usr/bin/python /home/pi/agriduino/water_plants.py
````
