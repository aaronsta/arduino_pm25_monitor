#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "Adafruit_PM25AQI.h"


#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
 // For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
// color definitions
const uint16_t  color_black        = 0x0000;
const uint16_t  color_blue         = 0x001F;
const uint16_t  color_white        = 0xFFFF;
uint16_t text_color         = color_blue;
uint16_t background_color    = color_white;
const uint16_t  color_red          = 0xF800;
uint16_t font_size = 3 ;


// If your PM2.5 is UART only, for UNO and others (without hardware serial) 
// we must use software serial...
// pin #2 is IN from sensor (TX pin on sensor), leave pin #3 disconnected
// comment these two lines if using hardware serial
//#include <SoftwareSerial.h>
//SoftwareSerial pmSerial(2, 3);

Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
bool hasLED;

void setup() {

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
   delay(500);
	tft.setFont();
	tft.fillScreen(background_color);
	tft.setTextColor(text_color);
	tft.setTextSize(font_size);
   tft.setCursor(0, 0);
//  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print("are you ready to measure AIR QUALITY!?");
  delay(500);
  tft.fillScreen(background_color);

  if(hasLED){
  // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
  }
  // Wait for serial monitor to open
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Adafruit PMSA003I Air Quality Sensor");

  // Wait one second for sensor to boot up!
  delay(1000);

  // If using serial, initialize it and set baudrate before starting!
  // Uncomment one of the following
  //Serial1.begin(9600);
  //pmSerial.begin(9600);

  // There are 3 options for connectivity!
  if (! aqi.begin_I2C()) {      // connect to the sensor over I2C
  //if (! aqi.begin_UART(&Serial1)) { // connect to the sensor over hardware serial
  //if (! aqi.begin_UART(&pmSerial)) { // connect to the sensor over software serial 
    Serial.println("Could not find PM 2.5 sensor!");
    while (1) delay(10);
  }

  Serial.println("PM25 found!");
}

void loop() {

  PM25_AQI_Data data;
  
  if (! aqi.read(&data)) {
    Serial.println("Could not read from AQI");
    delay(500);  // try again in a bit!
    return;
  }

 //levels per https://www.epa.gov/system/files/documents/2024-02/pm-naaqs-air-quality-index-fact-sheet.pdf
  if(data.pm25_env >= 35.5){//Unhealthy for Sensitive Groups level per https://en.wikipedia.org/wiki/Air_quality_index
  if(hasLED){
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
   }
    Serial.print("AQI: Unhealthy for Sensitive Groups. PM2.5: ");
    Serial.println(data.pm25_env);
    tft.setTextColor(color_red);
    tft.setCursor(0, 0);
    tft.print("Unhealthy for Sensitives: ");
    tft.print(data.pm25_env);
    delay(2000);
    tft.fillScreen(background_color);

  }
  else if(data.pm25_env > 9 && data.pm25_env < 35.5){
    if(hasLED){
       digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    }
    Serial.print("AQI: Moderate. PM2.5: ");
    Serial.println(data.pm25_env);
    tft.setTextColor(color_blue);
    tft.setCursor(0, 0);
    tft.print("Moderate: ");
    tft.print(data.pm25_env);
    delay(2000);
    tft.fillScreen(background_color);

  }
  else{
     if(hasLED){
       digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
     }
     Serial.print("AQI: Good. PM 2.5: ");
     Serial.println(data.pm25_env);
     tft.setTextColor(color_blue);
     tft.setCursor(0, 0);
     tft.print("Good: ");
     tft.print(data.pm25_env);
     delay(2000);
     tft.fillScreen(background_color);

  }
  

  delay(2000);
}
