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