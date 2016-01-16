"""
file: agriduino.py
python version: 2.7
description:
    This script polls an arduino for info and builds at as a comma delimited data string to write
    to a csv file.  
    String should be formatted "datestamp, temp, humidity, light_level, soil_moisture, watering

"""

import time, datetime
import csv
import schedule
import serial

def poll_sensors():
    """
    Read from sensors
    """
    print("Polling sensors\n")
    ser = serial.Serial('/dev/ttyACM0',9600)
    time.sleep(10)
    ser.write('1')
    time.sleep(1)
    data = ser.readline()
    data = data.strip()
    data = time.strftime("%c") + "," + data
    out = data.split(',')
    print(out)
    print("\n")
    send_to_file(out)


def send_to_file(data):
    """
    Write to CSV file at path
    """
    CSV_FILE = '/home/pi/agridata/agri_data.csv'
    with open(CSV_FILE, 'a') as csv_file:
        writer = csv.writer(csv_file, delimiter=',')
        for line in data:
            writer.writerow(line)
        csv_file.close()

def water_plants():
    """
    Set flag on Arduino to water plants
    """
    print("Water Plants")


def __main__():
    #State
    schedule.every(1).minutes.do(poll_sensors)
    schedule.every().day.at("7:00").do(water_plants)

    while 1:
        schedule.run_pending()
        time.sleep(1)


__main__()
