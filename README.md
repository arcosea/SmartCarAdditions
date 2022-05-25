# SmartCarAdditions
Includes additional components that are to be attached to the SmartCar project
Author: Erick Arcos

Notes:
Programmed an Arduino Nano to have various functions. 
The components involved include: 1 OLED, 3 RGB LED's, 1 DHT sensor, 1 HC-SR01 PIR motion sensor, 1 Buzzer and 1 DS3231 real time clock.

The nano has a few functions. It is responsible for setting up the motion sensor, setup is complete when green led is on. If movement is read, buzzer and red led flicker on and off. OLED is used to display temperature, humidity, and time. Two alarms can also be scheduled and will cause buzzer to go off. 

