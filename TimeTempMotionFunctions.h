//#include <Adafruit_SSD1306.h>
//#include <splash.h>

//#include <DS1307RTC.h>


/* All Functions Used In This Project Are Found In This Document
 * 
 */

  //*****************************************//
  //*       NECESSARY FILES/LIBRARIES       *//
  //*****************************************//
 #include "TimeTempMotionSetup.h"                           // File Containing Global Variables
 #include "DHT.h"                                           // DHT Zip File For Humidity/Tem
 #include <Wire.h>                                          // Arduino Basic Library
 #include <Adafruit_GFX.h>                                  // OLED Library ?
 #include <Adafruit_SSD1306.h>                              // OLED Screen Display Library
 #include <DS3231.h>                                        // DS1307 Library
 //#include <DS1307RTC.h>



  //*****************************************//
  //*       NECESSARY OBJECTS               *//
  //*****************************************//
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Wire setup with OLED
  
  int motionValue;                                          // Stores output value of the PIR Motion Sensor
  bool motionStatus = true;                                 // Boolean that determines with motion is detected (true) or not (False)
  
  DS3231 clock;                                             // Clock Object
  RTCDateTime dt;                                           // Clock date object data structure
  
  DHT dht(DHT_Pin, DHTTYPE);                                // Communicate DHT Sensor with its pin & type


 //******************************************//
 //*              SETUP FUNCTIONS           *//
 //******************************************//
/**************************************************************************************************************************/
  // SET THE BUZZER AND ALL LEDS AS OUTPUTS
  void buzzerLED_Setup(){
    pinMode(buzzer, OUTPUT);
    pinMode(red_LED, OUTPUT);
    pinMode(green_LED, OUTPUT);
    pinMode(blue_LED, OUTPUT); 
  }

/**************************************************************************************************************************/
  // SETS BUZZERS AND LEDS AS TURNED OFF
  void buzzerLED_OFF(){
    digitalWrite(buzzer, LOW);                              // Turns buzzer Off
    digitalWrite(red_LED, LOW);                             // Turns red LED Off
    digitalWrite(green_LED, LOW);                           // Turns green LED Off
    digitalWrite(blue_LED, LOW);                            // Turns blue LED Off
  }

/**************************************************************************************************************************/
  // SETS THE PIR MOTION SENSOR AS AN INPUT
  void motion_Setup(){
    pinMode(motionSensor, INPUT);                           // Sets motionSensor as an Input
  }

/**************************************************************************************************************************/
 // TURNS OFF ALL LED'S AND BUZZER IF MOTIONBUTTONOFF IS PRESSED
 void motionOff(){
      if(digitalRead(motionButtonOff) == LOW){
      buzzerLED_OFF();
    }
  }
  
/**************************************************************************************************************************/ 
  // SETS BUTTONS AS OUTPUTS
  void button_Setup(){
    pinMode(motionButtonOn, INPUT_PULLUP);                    // Set motionButtonOn as input pullup. Pullup means it just has to be pressed ONCE to activate
    pinMode(motionButtonOff, INPUT_PULLUP);                   // Set motionButton Off as input pullup. With Input, we would have to HOLD the button
    //attachInterrupt(0, motionOff, FALLING);                 // Zero reps D2 bc first intterupt. Uses motionOff as interrupt function
  }
  
/**************************************************************************************************************************/
  // INITIALIZES WIRE LIBRARY FOR I2C & OLED W/ ADDRESS 0X32C & SETS UP OLED DISPLAY & CURSOR
  void OLED_Setup(){
    Wire.begin();
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
          Serial.println(F("SSD1306 allocation failed"));
          for(;;);                                            // Don't proceed, loop forever
    }
    
     display.clearDisplay();                                 // Clears display
     display.setTextColor(WHITE);                            // Always use white?
     display.setTextSize(1);                                 // Font size
     
  }

/**************************************************************************************************************************/
  // DISPLAYS THE DIFFERENT ASPECTS TIME/DATE/HUMIDITY/TEMP THAT WILL BE SHOWN ON OLED
  void display_Setup(){
     display.setCursor(cursX_Origin,cursY_Time);            // Sets Cursor Top Left
     display.print("Time ");                                // Prints "Time ". 
     
     display.setCursor(cursX_Origin,cursY_Date);            // Brings Cursor down a text size worth of space
     display.print("Date ");                                // Prints "Date ". 
     
     display.setCursor(cursX_Origin,cursY_Humi);            // Brings Cursor another text size worth of space
     display.print("Humi ");                                // Prints "Humi ". 
     
     display.setCursor(cursX_Origin,cursY_Temp);            // Brings Cursor down a text size worth of space
     display.print("Temp ");                                // Prints "Temp ". 

     display.setCursor(cursX_Origin, cursY_Alarm01);        // Brings Cursor down a text size worth of space
     display.print("Alm1 ");                               // Prints "Alm1 "

     display.setCursor(cursX_Origin, cursY_Alarm02);        // Brings Cursor down a text size worth of space
     display.print("Alm2 ");                               // Prints "Alm2 "

     display.display();                                     // Displays all of Above
  }


/**************************************************************************************************************************/
 // BEGINS BOTH CLOCK & DHT SENSOR MODULES
 void clockDHT_Setup() {
    dht.begin();                                             // Activates DHT Sensor
    clock.begin();                                           // Initializes/Activates the DS module
    clock.setDateTime(__DATE__, __TIME__);                   // Sets time to that of computer
    //clock.setDateTime(2021, 6, 19, 20, 25, 30);
 }


  
 //*******************************************//
 //*               FUNCTIONS                 *//
 //*******************************************//
//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//

 //*******************************************//
 //*          LED/BUZZER FUNCTIONS         *//
 //*******************************************//

  // TURNS ON THE BLUE LED SO MOTION SENSOR SETUPS UP. TURNS OFF BLUE & TURNS ON GREEN
  void waitReadyLED(){
    /* Start Function */
    
    digitalWrite(blue_LED, HIGH);                             // Turn ON blue LED
    delay(msMinute );                                         // Milliseconds that blue LED will be on for
    digitalWrite(blue_LED, LOW);                              // Turn OFF blue LED
    delay(cycleTime);
    
    /* End Function */
  }

/**************************************************************************************************************************/
  // FLICKERS BUZZER AND RED LED FOR SOME NUMBER OF CYCLES
  void buzzerLED_ON(int Cycles){
    /* Start Function */
    
     for(int currentCycle = 0; currentCycle < Cycles; currentCycle++){
        buzzerLED_OFF();                                      // Turns OFF all LED's 
        
        digitalWrite(red_LED, HIGH);                          // Turns ON red LED
        digitalWrite(buzzer, HIGH);                           // Turns ON buzzer
        delay(cycleTime);                                     // Waits for CycleTime (.5s)
        
        digitalWrite(red_LED, LOW);                           // Turns OFF red LED
        digitalWrite(buzzer, LOW);                            // Turns OFF buzzer
        delay(cycleTime);                                     // Waits for CycleTime (.5s)

        // If motionButtonOff is pressed, terminate loop & turns everything off
        if(digitalRead(motionButtonOff) == LOW){            
          currentCycle = Cycles;
          buzzerLED_OFF();
        } 
     }
     
     /* End Function */
  }

//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//

 //*******************************************//
 //*          MOTION SENSOR FUNCTIONS        *//
 //*******************************************//
 
  // DETECTS MOTIONS AND SETS OFF BUZZER
  void detectMotion(){
    /* Start Function */
      
      while(motionStatus){                                    // Infinite loop to always search for change in IR; motionStatus is TrRUE
          digitalWrite(green_LED, HIGH);                      // Turns on Green LED
          motionValue = digitalRead(motionSensor);            // Reads the value of the sensor.  
          digitalWrite(red_LED, motionValue);                 // Stores input 
          delay(cycleTime);                                   // Delays by cycleTime (.5s)

          // If both motionButtonOf & motionButtonOn are pressed, turn OFF buzzer & LED & end infinite loop
          if(digitalRead(motionButtonOff) == LOW && digitalRead(motionButtonOn) == LOW){
            motionStatus = false;
            buzzerLED_OFF();
            delay(cycleTime);
          }
          
          // If movement detected, set off alarm/flash with buzzerLed_Active function. HIGH means change/motion in IR          
          if(motionValue == HIGH){
              buzzerLED_OFF();
              buzzerLED_ON(5);
          }        
      }
      buzzerLED_OFF();  
                                
    /* End Function */
  }

/**************************************************************************************************************************/
  // OPERATE DETECTMOTION FUNCTION WHEN MOTIONBUTTONON IS PRESSED
  void motionOn(){
    /* Start Function */
    
    // If motionButtonOn is pressed, run detectMotion Operation
    if(digitalRead(motionButtonOn) == LOW){
      // Allow motion sensor to setup
      waitReadyLED();
      
      // Then Detect Motion
      detectMotion();  
    }
    
    /* End Function */
  }

//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//
 //*******************************************//
 //*          TIME & DATE FUNCTIONS          *//
 //*******************************************//

 // THIS FUNCTIONS PRINTS 2 DIGITS IF NUMBER IS LESS THAN 10
 void print2Digits(int number) {
   /* Start Function */
   
   if(number >= 0 && number < 10) {
     display.print("0");
   }
   display.print(number);
   display.display();
   
   /* End Function */
 }

/**************************************************************************************************************************/
 // THIS FUNCTION PRINTS THE HOUR ALONG IN A 12 HOUR SCALE ALONG WITH ITS CORRESPONDING TIME FRAME (AM OR PM)
 void hourTime(int hour, int cursX, int cursY) {
    /* Start Function */
    int cursChange = 35;                                       // Format is "HR:MN _M". Will need to move by 4 digits. Each digit about 5 pixels
    // Write AM if hour is less than 12 in 24hr scale
    if(hour < 12) {
        // If the hour is at 0 set it to 12
        if(hour == 0){         
          hour = 12;
        }
        // Display the hour
        display.setCursor(cursX, cursY);
        print2Digits(hour);
        display.print(":");

        // Change Cursor in Xcoord to Display AM
        display.setCursor(cursX + cursChange, cursY);
        display.print("AM");
        display.display();
    }
    
    // Write PM if hour is more or equal to 12 in 24hr scale
    if(hour >= 12) {
        // Change hour so that it is no longer in 24hr scale
        if(hour > 12) {
          hour = hour - 12;
        }

        // Display the Hour. The print2Digits here is unnecessary
        display.setCursor(cursX, cursY);
        print2Digits(hour); 
        display.print(":");

        // Change Cursor in Xcoord to Display PM
        display.setCursor(cursX + cursChange, cursY);
        display.print("PM");
        display.display();      
    }
    
    /* End Function */
 }

/**************************************************************************************************************************/
 // THIS FUNCTION DISPLAY THE TIME IN THE FORMAT "HR:MIN _M"
 void displayTime () {
   /* Start Function */
   Wire.read();
   int cursDiff = 18;                                    // Variable to change 3 digits worth of text
   
   // Get the time & setup format
   dt = clock.getDateTime();

   // Displays hour
   hourTime(dt.hour, cursX_Start, cursY_Time); 

   // Display minute
   display.setCursor(cursX_Start + cursDiff,cursY_Time);
   print2Digits(dt.minute);
 
   /* End Function */
 }

 /**************************************************************************************************************************/
 // THIS FUNCTION WILL GET THE DATE FROM THE COMPUTER AND DISPLAY IT IN FORMAT MM/DD/YYYY
 void displayDate () {
   /* Start Function */

   // Set cursor to location dedicated for Date
   display.setCursor(cursX_Start, cursY_Date);

   // Display Month, Day, and Year
   print2Digits(dt.month);
   display.print("/");
   print2Digits(dt.day);
   display.print("/");
   display.print(dt.year);
   display.display();
 
   /* End Function */
 }
 

//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//
 //*******************************************//
 //*         HUMIDITY & TEMP FUNCTIONS       *//
 //*******************************************//

 // THIS FUNCTION READS THE HUMIDITY AND DISPLAYS IT
  void displayHumidity(){
     /* Start Function */

     // Set cursor to location dedicated for Humidity
     display.setCursor(cursX_Start, cursY_Humi);

     // Read humidity and store it in value
     float humid = dht.readHumidity();

     // Display Humidity
     display.print(humid);
     display.print(" %");
     display.display();
      
     /* End Function */
  }

  // THIS FUNCTION READS THE TEMPERATURE IN CELCIUS, CONVERTS IT TO FAHRENHEIT & DISPLAYS IT
  void displayTemp(){
     /* Start Function */
     
     // Set cursor to location dedicated for Temp
     display.setCursor(cursX_Start, cursY_Temp);

     // Read temperature in celcius & stores value
     float temp_C = dht.readTemperature();

     // Convert temperature to fahrenheit using conversion equation
     float temp_F = (1.8*temp_C) + 32;

     // Display temperature in fahrenheit
     display.print(temp_F);
     display.print(" F");
     display.display();
     
     /* End Function */
  }
  

//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//
 //*******************************************//
 //*         DISPLAY FUNCTION                *//
 //*******************************************//

 // THIS FUNCTION RUNS ALL THE DISPLAY FUNCTIONS
 void displayAll(){
   /* Start Function */
   
   // Display Time
   displayTime();

   // Display Date
   displayDate();

   // Display Humidity
   displayHumidity();
   
   // Display Temp In Celc
   displayTemp();

   // Print every 10 seconds, reclear screen & reprint b/c digits stack if not recleared.
   display.display();
   buzzerLED_OFF();
   delay(delayTime);
   display.clearDisplay();
   display_Setup();
   
   /* End Function */
 }

//________________________________________________________________________________________________________________________//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||//
//------------------------------------------------------------------------------------------------------------------------//
 //*******************************************//
 //*         ALARM FUCTION                   *//
 //*******************************************//

 // THIS FUNCTION SETS AN ALARM, DISPLAYS THE ALARM AND GOES OFF UNTIL BUTTON IS PRESSED 
 void alarm01(int hour, int minute){
  /* Start Function */
  
  // Difference in cursor space
    int cursDiff = 18;
    
  // Set up cursor and prints alm
  display.setCursor(cursX_Origin, cursY_Alarm01);
  display.print("Alm1");
  
  // Determines if hour and minute given are valid, prints them based on whether they are or not
  if(hour > 23 || hour < 0 || minute > 60 || minute < 0) {
     display.setCursor(cursX_Start, cursY_Alarm01);
     display.print("N/A");
  }
  else {
     // This functions displays the hour in a 12hr scale with AM or PM
     hourTime(hour, cursX_Start, cursY_Alarm01);
     
     // Display minute
     display.setCursor(cursX_Start + cursDiff, cursY_Alarm01);
     print2Digits(minute);
  }

  // Sets off buzzerLED_ON function if current time equals alarm time
  if(dt.hour == hour && dt.minute == minute) {
     buzzerLED_ON(alarmCycles);
  }

  // if Alarm has already gone off, state that it is OFF.
  if(dt.hour >= hour && dt.minute > minute) {
    display.setCursor(cursX_Start + 3* cursDiff, cursY_Alarm01);
    display.print("OFF");
  }

  // Displays
  display.display();
  
  /* End Function */
 }

 
 // THIS FUNCTION IS SAME AS PREVIOUS BUT FOR A SECOND ALARM
 void alarm02(int hour, int minute){
  /* Start Function */
  // Difference in cursor space
     int cursDiff = 18;
     
  // Set up cursor and prints alm
  display.setCursor(cursX_Origin, cursY_Alarm02);
  display.print("Alm1");
  
  // Determines if hour and minute given are valid, prints them based on whether they are or not
  if(hour > 23 || hour < 0 || minute > 60 || minute < 0) {
     display.setCursor(cursX_Start, cursY_Alarm02);
     display.print("N/A");
  }
  else {
     // This functions displays the hour in a 12hr scale with AM or PM
     hourTime(hour, cursX_Start, cursY_Alarm02);
     
     // Display minute
     display.setCursor(cursX_Start + cursDiff, cursY_Alarm02);
     print2Digits(minute);
  }

  // Sets off buzzerLED_ON function if current time equals alarm time
  if(dt.hour == hour && dt.minute == minute) {
     buzzerLED_ON(alarmCycles);
  }

  // if Alarm has already gone off, state that it is OFF.
  if(dt.hour >= hour && dt.minute > minute) {
    display.setCursor(cursX_Start + 3* cursDiff, cursY_Alarm02);
    display.print("OFF");
  }

  // Displays
  display.display();
  
  /* End Function */
 }



 
