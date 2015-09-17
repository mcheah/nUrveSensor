/* This file is meant to set up an configure all the sensors when the device first turns on.
 * Process: 
 * 1) Basic Stuff
 * 2) Communication Stuff
 * 3) Location Tracking
 * 4) Ambient Sensors
 * 5) Road Quality Sensor
 * 6) Air Quality Sensor - Gas
 * 7) Air Quality Sensor - Particulates
 * 8) Other / Future
 */
void setupComms() {
  Serial.println("LATER: Comms");
}
void setupDataLogger() {
  if(!SD.begin(10,11,12,13))
  {
    error("Card Fail");
  }

  char filename[] = "AUDIO___.CSV";
    for (uint8_t i = 0; i < 1000; i++) {
      filename[6] = i/10 + '0';
      filename[7] = i%10 + '0';
      if (! SD.exists(filename)) {
        // only open a new file if it doesn't exist
        logfile = SD.open(filename, FILE_WRITE); 
        break;  // leave the loop!
      }
    }
          if (! logfile) 
       {
       error("couldnt create audio file");
      }
        logfile.print("TimeStamp-");logfile.print("location");
        logfile.print("audio_max");logfile.print(",");logfile.print("audio_avg");logfile.print(",");logfile.print("audio_sum");logfile.print(",");logfile.print("audio_count");logfile.print(",");
        logfile.print("accel_max");logfile.print(",");logfile.print("accel_avg");logfile.print(",");logfile.print("accel_sum");logfile.print(",");logfile.print("accel_count");logfile.print(",");
        logfile.print("Lux")    ;logfile.print(",");logfile.print("Humd") ;logfile.print(",");logfile.println("Temp");
        logfile.flush();
}
void setupGPS() {
  Serial.println("Adafruit GPS library basic test!");
  Serial1.begin(9600);
  delay(10);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  //GPS.sendCommand(PMTK_API_SET_FIX_CTL_100_MILLIHERTZ);
  GPS.sendCommand(PGCMD_NOANTENNA);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  //GPS.sendCommand(PMTK_SET_BAUD_9600);
  /*Serial1.end();
  Serial1.begin(115200);*/
  //useInterrupt(false);
  delay(100);
 }
/* +---------------------------------------------------+
 * | 4A) Ambient Sensors - Temperature & Humidity      |
 * +---------------------------------------------------+*/
void setupAmbientTemp() {
  Serial.println("Setup Ambient Temp");
  if (!htu.begin()) {
    Serial.println("[] ERROR: Could not find the Temperature & Humidity sensor. Please check your wiring!");
    //while (1);
  }
}
/* +---------------------------------------------------+
 * | 4B) Ambient Sensors - Luminosity                  |
 * +---------------------------------------------------+*/
void setupAmbientLux() {
  Serial.println("Setup Ambient Lux");
  if(!tsl.begin()) {
    Serial.println("[] ERROR: Could not find the Luminosity Sensor. Please check your wiring!");
    //while (1);
  } 
}
/* +---------------------------------------------------+
 * | 4C) Ambient Sensors - Sound                       |
 * +---------------------------------------------------+*/
// Electret is wired to pin...
void setupAmbientSound() {
  Serial.println("Setup Ambient Sound");
  // There is nothing for the sound sensor
}
/* +---------------------------------------------------+
 * | 5) Road Quality - Accelerometer                   |
 * +---------------------------------------------------+*/
void setupRoadSensor() {
  Serial.println("| ADXL_345: Test & Config...");
  if(!accel.begin())
  {
    // There was a problem detecting the ADXL345 ... check your connections 
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}
