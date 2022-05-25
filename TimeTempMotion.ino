/* Name: Erick Arcos
 * Last Updated: 06/ 10/20221
 * Project: This Project Is An Attachment for The SmartCar Project Where Here
 *          We Display Both The Current Time & Temperature & Humidity on OLED.
 *          Can Also Set Alarms & Have Them Go Off Using A Buzzer. Also 
 *          Contains A Motion Sensor That Can Be Initiated With A Button. The
 *          Motion Sensor Sets Off Red LED & Buzzer When Change In IR Is Detected
 */

  //*****************************************//
  //*       NECESSARY FILES/LIBRARIES       *//
  //*****************************************//
  #include "TimeTempMotionSetup.h"                   // Contains Global Variables
  #include "TimeTempMotionFunctions.h"               // Contains Functions
  


  void setup() {
    buzzerLED_Setup();                               // Sets Buzzer & LED's as outputs
    buzzerLED_OFF();                                 // Sets Buzzer & LED'S OFF
    button_Setup();                                  // Sets buttons as inputs
    motion_Setup();                                  // Sets PIR motion sensor as input
    OLED_Setup();                                    // Sets up OLED & clears screen
    clockDHT_Setup();                                // Sets up DHT & clock modules to begin reading
    display_Setup();                                 // Sets up basic display for time, date, hum, temp & alarms
    
    
    
  }

  void loop() {
    motionOn();                                       // Function for motion sensor 
    displayAll();                                     // Function that displays all time, date, temp & hum
    alarm01(7,0);                                     // Function sets up Alarm 01
    alarm02(26, -3);                                  // Function that sets up Alarm 02

  }


  /* HOW THE ALARM FUNCTION WORKS: 
    alarm(int hour, int minute)
        hours:
              0 = 12   AM        12 = 12  PM
              1 = 1    AM        13 = 1   PM
              2 = 2    AM        14 = 2   PM
              3 = 3    AM        15 = 3   PM
              4 = 4    AM        16 = 4   PM
              5 = 5    AM        17 = 5   PM
              6 = 6    AM        18 = 6   PM
              7 = 7    AM        19 = 7   PM
              8 = 8    AM        20 = 8   PM
              9 = 9    AM        21 = 9   PM
              10 = 10  AM        22 = 10  PM
              11 = 11  AM        23 = 11  PM
  */
  
