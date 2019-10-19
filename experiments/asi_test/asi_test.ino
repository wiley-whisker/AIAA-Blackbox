/*
 * Reads raw data from the airspeed sensor and writes it to serial.
 * 
 * author: Wiley Matthews
 */

int analogPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  int data = analogRead(analogPin);
  Serial.println(data);
  delay(100);

}
