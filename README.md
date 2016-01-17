# agriduino
Python code for agriduino plant care system

# CRON Jobs currently running
* * * * * /usr/bin/python /home/pi/agriduino/read_sensors.py
0 7 * * * /usr/bin/python /home/pi/agriduino/water_plants.py
