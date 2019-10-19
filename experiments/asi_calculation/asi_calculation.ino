/*
 * This code may or may not work. Untested. It is meant to write the actual airspeed to serial for verification.
 */

// The offset voltage is 1.0V when there is no pressure difference.
const float offset = 1.0;

// The sensitivity is 1.0V per kPa for the sensor.
const float sensitivity = 1.0;

// assume the analog pressure sensor is connected to A0.
const int pinSensor = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  int rawADC = analogRead (pinSensor);
  float voltage = (float) rawADC / 1023.0 * 5.0;   // voltage at Arduino pin. Range is 5V, 10 bits.
  float pressure = (voltage - offset) / sensitivity;   // differential pressure in kPa

  // Some magical calcuation for the windspeed (just as an example)
  float windspeed = sqrt ( 2.0 * pressure / 1.2 );
  Serial.println(windspeed);
  delay(100);
}
