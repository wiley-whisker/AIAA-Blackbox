/*
 * This code may or may not work. Untested. It is meant to write the actual airspeed to serial for verification.
 * 
 * An explination to the calculation can be found here:
 * https://stackoverflow.com/questions/44007108/calculating-wind-speed-with-pitot-tube-using-arduino
 * 
 * Basically, analogRead() returns an integer in [0,1023]? that is a scallar of the pressure difference between
 * the dynamic and static pressure readings of the sensor. 
 * 
 * What this line:
 *     float voltage = (float) rawADC / 1023.0 * 5.0;
 * is doing is dividing by the range of the possible retun values in order to get a float [0,1]. Then multiplying by 5V
 * since that's the sensor's reference voltage. So at the end of this line we end up with: V_reading = percentage_diff * 5V
 * 
 * Next, we take that voltage reading and subtract the offset value specified by the sensor. This gives us dynamic pressure.
 * 
 * Finally, we perform the calculation for airspeed using the formula:
 *     airspeed [m/s]? = sqrt(2 * dynamic-pressure [N/m^2]? / air-density [kg/m^3])
 * 
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
