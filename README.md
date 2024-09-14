# Background and Resources Used:
1. See ArduinoCircuit_PM25_LED.txt for circuit connections for this project
2. [PM2.5 Air Quality Sensor and Breadboard Adapter Kit - PMS5003](https://www.adafruit.com/product/3686) /  - uses a Plantower PMS5003 sensor ([manual](https://cdn-shop.adafruit.com/product-files/3686/plantower-pms5003-manual_v2-3.pdf))
3. [Adafruit PM 2.5 Monitor Tutorial for Arduino and other microcontrollers](https://learn.adafruit.com/pm25-air-quality-sensor/overview)
4. [Adafruit_PM25AQI library (github)](https://github.com/adafruit/Adafruit_PM25AQI)
5. [Analysis of using Plantower sensor in a lab](https://forums.adafruit.com/viewtopic.php?f=48&t=136528&p=767725#p767725)

# What It Does 
**(This is not intended to be used for any kind of production applications.)**

Using an Arduino (or presumably other microcontroller tools),this turns on an LED light once a certain threshold of PM 2.5 is crossed. Currently hard-coded for Unhealth for Sensitive Groups level
 35.5 mg / m2 per [US EPA as of 2/2024](https://www.epa.gov/system/files/documents/2024-02/pm-naaqs-air-quality-index-fact-sheet.pdf)

[Using pm25_env per this forum thread ](https://forum.arduino.cc/t/abnormal-sensor-readings-from-a-pm2-5-sensor-by-plantower-solved/1277321/2)

If you want to log data to a file, run the following python script (set up file name in script otherwise it uses airquality.log)
```python3 airQualityReadingsToSerialPort.py