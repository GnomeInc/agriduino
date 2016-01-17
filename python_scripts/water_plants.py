#!/user/bin/python2.7
"""
file: water_plants.py
python version: 2.7
description:
    This script is designed to be run as a CRON job to send a signal to 
    the arduino to flip a flag which will tell it to water the plants.
"""

import serial

#Constants
ARDUINO_ADDRESS = '/dev/ttyACM0'
BAUD = 9600
WATER_PLANTS_SIGNAL = '2'


# Connect to Arduino.  This has the unfortunate side effect of causing the
# duino to reset and lose state.  Requires a hardware fix.
ser = serial.Serial(ARDUINO_ADDRESS, BAUD)
time.sleep(2)
ser.write(WATER_PLANTS_SIGNAL)
