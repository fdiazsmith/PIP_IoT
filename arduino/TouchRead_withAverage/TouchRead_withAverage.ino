#include <RunningAverage.h>
#include "config.h"

// ESP32 Touch Read Setup
// See Touch pins at https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654#target_5

RunningAverage myRA(100);

const uint8_t touchPins[] = { T0, T1, T3, T4, T5, T6 };

void setup()
{
  //for reading the values in the Serial Monitor
  Serial.begin(115200);
  delay(1000); 

  myRA.clear();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  // loop through all the touchPins
  for(int i = 0; i < 6; i++) {
    Serial.println((String)"ID" + BOARDNUM + i + touchRead(touchPins[i]));
    
  }
  
  delay(50);

  myRA.addValue(touchRead(T1));

  
  //this value will need to be tweaked based on cable length & plant size etc. 
  if(myRA.getAverage() - touchRead(T1) > 2) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
}
