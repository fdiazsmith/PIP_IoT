// ESP32 Touch Read Setup
// See Touch pins at https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654#target_5


void setup()
{
  //for reading the values in the Serial Monitor
  Serial.begin(115200);
  delay(1000); 
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.println((String)"T0 " + touchRead(T0)); 
  Serial.println((String)"T1 " + touchRead(T1)); 
  //Serial.println((String)"T2 " + touchRead(T2));  //T2 doesn't seem to work
  Serial.println((String)"T3 " + touchRead(T3)); 
  Serial.println((String)"T4 " + touchRead(T4)); 
  Serial.println((String)"T5 " + touchRead(T5)); 
  Serial.println((String)"T6 " + touchRead(T6)); 
  delay(50);

  //this value will need to be tweaked based on cable length & plant size etc. 
  if(touchRead(T1) < 15) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
}
