#!/user/bin/python2.7
"""
file: read_sensors.py
python version: 2.7
description:
    This script polls an arduino for info and builds at as a comma delimited data string to write
    to a csv file.  
    String should be formatted "datestamp, temp, humidity, light_level, soil_moisture, watering
"""

import time, datetime
import csv
import serial

#Constants
CSV_FILE = '/home/pi/agridata/agri_data.csv'
ARDUINO_ADDRESS = '/dev/ttyACM0'
BAUD = 9600

def poll_sensors(ser):
    """
    Read from sensors
    """
    print("Polling sensors\n")
    ser.write('1')
    time.sleep(2)
    print("reading data")
    data = ser.readline()
    data = data.strip()
    data = time.strftime("%c") + "," + data
    print(data)
    print("\n")
    send_to_file(data.split(','))


def send_to_file(data):
    """
    Write to CSV file at path
    """
    with open(CSV_FILE, 'a') as csv_file:
        writer = csv.writer(csv_file, delimiter=',')
        writer.writerow(data)
        csv_file.close()

# Connect to Arduino.  This has the unfortunate side effect of causing the
# duino to reset. Will fix in hardware.
ser = serial.Serial(ARDUINO_ADDRESS, BAUD)
time.sleep(2)
poll_sensors(ser)
