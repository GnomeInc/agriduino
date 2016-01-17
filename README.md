# agriduino
Python code for agriduino plant care system

## Description
Currently, this is a sketch running on an arduino uno (frizting files forthcoming). The arduino waits for commands from a raspberry pi which runs python scripts on CRON jobs.  The script pulls sensor data from the arduino and appends it to a CSV file.

## TODO
Set up web server on Pi which will load data from CSV file and display it graphically and have web interface.  Likely done in php/html/css.  Build tables and charts in plot.ly maybe.  Or I'll check out python graphic libraries.

## CRON Jobs currently running
```
* * * * * /usr/bin/python /home/pi/agriduino/read_sensors.py
0 7 * * * /usr/bin/python /home/pi/agriduino/water_plants.py
````
