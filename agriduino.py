"""
file: agriduino.py
description:
    This script polls an arduino for info and builds at as a comma delimited data string to write
    to a csv file.  
    String should be formatted "datestamp, temp, humidity, light_level, soil_moisture, watering

"""

import time, datetime
import csv
import schedule

def poll_sensors():
    print("Poll Sensors")

def send_to_file(data, path):
    """
    Write to CSV file at path
    """
    with open(path, 'a', newline='') as csv_file:
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
    #Constants
    CSV_FILE = "/var/www/agri_data.csv"
    #State
    schedule.every(1).minutes.do(poll_sensors)
    schedule.every().day.at("7:00").do(water_plants)

    while 1:
        schedule.run_pending()
        time.sleep(1)


__main__()
