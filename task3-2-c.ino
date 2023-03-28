// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>

// This #include statement was automatically added by the Particle IDE.


// This #include statement was automatically added by the Particle IDE.



// initialize the BH1750 library object
BH1750 lightMeter(0X23,Wire);


void setup() {
    
    // Starts the sensor
    lightMeter.begin();
    
    
    // sets the sensor mode and resolution
    lightMeter.set_sensor_mode(BH1750::forced_mode_high_res2);


}

void loop() {
    
    // Makes the sensor to measure when requested
    lightMeter.make_forced_measurement();
    
    
    //the light intensity is store in the variable lux
    float lux = lightMeter.get_light_level();
    
    
    //if light over 400 messages that the sunlight is out
    if(lux > 400){
        
        //triggers the webhook to post on IFTTT 
        Particle.publish("terrarium", "Sunlight Here", PRIVATE);
        
        
        while(lux > 400){
            
            lightMeter.make_forced_measurement();
            lux = lightMeter.get_light_level();
            
            // this function publishes the lux amount on the event page of particle console
            Particle.publish("Light", String(lux), PRIVATE);
            
            // Delay for 4 seconds before measuring again
            delay(4000);
        }
    }
    
    
    // if the light is below 400 we receieve a notification that the sunlight is out
    if(lux < 400){
        
        //triggers the webhook to post on IFTTT 
        Particle.publish("terrarium", "Sunlight Out", PRIVATE);
        
        // we stay in for loop till the light passes the 400. this is to avoid constantly receiving messages 
        while(lux < 400){
            
            lightMeter.make_forced_measurement();
            lux = lightMeter.get_light_level();
            
            // this function publishes the lux amount on the event page of particle console
            Particle.publish("Light", String(lux), PRIVATE);
            
            // Delay for 4 seconds before measuring light again
            delay(4000);
        }
        
    }
    
    
    
    //Particle.publish("temp", String(lux), PRIVATE);
    
    //delay(3000);
    
}

/*
#include "BH1750.h"
BH1750 sensor(0x23, Wire);

void setup()
{
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  Serial.begin();
}

void loop()
{
  sensor.make_forced_measurement();

  
  Particle.publish("temp", String::format("%f", sensor.get_light_level()), PRIVATE);

  delay(1000);
}*/