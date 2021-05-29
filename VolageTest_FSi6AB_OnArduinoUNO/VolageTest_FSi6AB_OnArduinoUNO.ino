float curr_val, max_voltage;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
    
    curr_val = analogRead(0);
    if( max_voltage < curr_val)
    {
        max_voltage = curr_val;
        Serial.println((max_voltage/1023.0)*5.0);
    }


}
