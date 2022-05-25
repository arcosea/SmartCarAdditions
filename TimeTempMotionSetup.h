
/* All Global Variables For Each Component & Corresponding Pin connections 
*     Will Be Found In This Document
*/ 

#ifndef _TimeTempMotionSetup_H
#define _TimeTempMotionSetup_H

/*******************************************
 *                 CONNECTIONS             *
 ******************************************/
 /* THE CIRCUIT: ON UNO NANO 
  *   Buzzer Pin  to D5
  *   
  *   Red LED Pin to D4
  *   Green LED Pin to D6
  *   Blue LED Pin to D8
  *   
  *   Motion Button Pressed (ON) Pin to D7
  *   Motion Button Unpressed (OFF) Pin to D3 
  *   
  *   HC PIR Motion Pin to D9
  *   
  *   DS1307 Clock SDA Pin to A4
  *   DS1307 Clock SCL Pin to A5
  *   
  *   DHT Pin to D2
  *   
  *   OLED SDA Pin to A4 Too
  *   OLED SCL Pin to A5 Too
  *   
  *   NOTE: All other pins are connected to Ground or Volt Source Respectively.
  * 
  * 
  */

  /*****************************************
  *                 BUZZER                 *
  *****************************************/
  #define buzzer 5                // Pin that buzzer Is Connected To D5 
  #define cycles 10               // Number of times buzzer & led will flicker ON & OFF for CycleTime increments
  #define cycleTime 500           // Duration (ms) that buzzer & LED will flicker for
  



 /******************************************
 *                    LED'S                *
 ******************************************/
 #define red_LED 4                // Pin D4. DETECTION: Alarms When Movement is 
 #define green_LED 6              // Pin D6.SEARCH: No movement is detected. 
 #define blue_LED 8               // Pin D8. WAITING: Motion Sensor is setting up. 


  /*****************************************
  *                 BUTTONS                *
  *****************************************/
  #define motionButtonOn 7        // Pin of button to turn ON the motion sensor functions
  #define motionButtonOff 3       // Pin to button to turn OFF the motion sensor function OR alarms



  /*****************************************
  *          HC PIR MOTION SENSOR          *
  *****************************************/
  #define motionSensor 9          // Pin of motion sensor
  #define msMinute 60000          // Milliseconds in a minute. Used for setting up Motion sensor


  /*****************************************
  *          OLED, DHT, & CLOCK            *
  *****************************************/
  /* For OLED SCREEN */
  #define SCREEN_WIDTH 128       // OLED display width, in pixels
  #define SCREEN_HEIGHT 64       // OLED display height, in pixels
  #define OLED_RESET     4       // Reset pin # (or -1 if sharing Arduino reset pin)
  #define SCREEN_ADDRESS 0x3C    // Screen Address

  /* For DHT SENSOR */
  #define DHT_Pin 2              // Pin connection
  #define DHTTYPE DHT11          // Type of DHT Sensor

  /* For DS Clock */
  #define delayTime 10000        // Changes Time Every 10 seconds 
  int cursX_Origin = 0;          // X coord of OLED origin
  int cursX_Start = 30;          // X coord of Cursor after displaying "Time/Date/Humi/Temp" is roughly 30. Each digit is about 6 pixels
  int cursY_Time = 0;            // Y coord of OLED display for time
  int cursY_Date = 10;           // Y coord of OLED display for date
  int cursY_Humi = 20;           // Y coord of OLED display for humidity
  int cursY_Temp = 30;           // Y coord of OLED display for temp
  int cursY_Alarm01 = 40;        // Y coord of OLED display for Alarm 01
  int cursY_Alarm02 = 50;        // Y coord of OLED display for Alarm 01
  #define alarmCycles 1000       // Number of cycles that buzzer/LED will flicker















#endif
