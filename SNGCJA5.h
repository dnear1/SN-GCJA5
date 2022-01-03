 /*
  This is a library written for the Panasonic SN-GCJA5 particle sensor
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support open source hardware. Buy a board!
  https://www.sparkfun.com/products/17123

  Written by Daniel Near Jan 2nd, 2022
  
  This library integrates the Sparkfun library for use in ESPHome
  
  SFE Library:
  https://github.com/sparkfun/SparkFun_Particle_Sensor_SN-GCJA5 

MIT License

Copyright (c) 2022 D Near

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include "esphome.h"
#include "SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library.h"
//https://github.com/sparkfun/SparkFun_Particle_Sensor_SN-GCJA5_Arduino_Library
SFE_PARTICLE_SENSOR myAirSensor
class SNGCJA5 : public Component, public Sensor {
    public:
      SNGCJA5() :PollingComponent(1000) {}

      float get_setup_priority() const override { return esphome::setup_priority::BUS; }
      Sensor *pm_1_sensor = new Sensor();
      Sensor *pm_2_5_sensor = new Sensor();
      Sensor *pm_10_sensor = new Sensor();
      static const uint16_t STARTUP_DELAY_MS = 28000;//need to give 28 seconds for readings to normalize per datasheet
      bool delaying_startup = true;

      void setup() override {
        Wire.begin();

        if(myAirSensor.begin() == False)
        {
          ESP_LOGI("SN-GCJA5", "The particle sensor did not respond. Please check wiring!");
          //print The particle sensor did not respond. Please check wiring!
        }
        //this will be called by App.setup
      }
      void loop() override {
        unsigned int pm1_0 = myAirSensor.getPM1_0();
        pm_1_sensor->publish_state(pm1_0);        
        unsigned int pm2_5 = myAirSensor.getPM2_5();
        pm_2.5_sensor->publish_state(pm2_5);       
        unsigned int pm10_0 = myAirSensor.getPM10_0();
        pm_10_sensor->publish_state(pm10_0);        
 
          //this will be called every update_interval milliseconds
      }
};
