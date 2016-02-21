/**
 * This program uses either two sensors to determine if a person is coming toward sensor1 or toward sensor2.
 * Default is using infrared. The closer a person is to the IR sensor the bigger the readings
 * The closer a person is to the ultrasonic sensor the smaller the readings.
 */
// Constants
const int analogInPinIR = A0; // Analog input pin that the sensor is attached to --> can use A2 through A5 on UNO
const int analogInPinIR2 = A5;
int THRESHOLD = 60; // any value below THRESHOLD someone stands in front of the sensor
const int IGNORETHRESHOLD = 200; // ignore readings from sensor that doesn't change at least this amount
const int TIMEOUT = 1000; // reset sensor memories after TIMEOUT
int INTERVAL = 100; // delay INTERVAL in miliseconds
// sensor memory values
int IRSensorVal = 0;
int IRSensorVal2 = 0;
int previous = 0;
int previous2 = 0;
int time1 = 0;
int time2 = 0;
boolean passed1 = false;
boolean passed2 = false;
// oprtional. Counter's used in a loop to stop collecting values after a certain amount of time
int counter = 0;

void setup() {
  // initialize serial communications at 9600 bps: <--- BAUD RATE
  Serial.begin(9600);
  Serial.println("Calliberating...");
//  calliberate();
//  Serial.println(THRESHOLD);
  Serial.println("Collecting data now!");
}

void calliberate() {
  // give it time to stabilize
  delay(5000);
  // collect 50 points and use the average as THRESHOLD
  int count = 0;
  for (int i=0; i<50; i++) {
    IRSensorVal = analogRead(analogInPinIR);
    count += IRSensorVal;
    delay(INTERVAL);
  }
  THRESHOLD = count/50;
}

void loop() {
    IRSensorVal = analogRead(analogInPinIR);
    IRSensorVal2 = analogRead(analogInPinIR2);
//    Serial.print("sensor 1: ");
//    Serial.println(IRSensorVal);
    Serial.print("sensor 2: ");
    Serial.println(IRSensorVal2);

    // setting for ultrasonic
//    if (IRSensorVal < THRESHOLD && (IRSensorVal + IGNORETHRESHOLD < previous)) {
    if (IRSensorVal > THRESHOLD && (IRSensorVal - IGNORETHRESHOLD > previous)) {
      time1 = millis();
      if (passed2 && !passed1 && time1 - time2 < 2000) {
        Serial.println("Coming towards sensor1");
        passed2 = false;
        passed1 = false;
      } else {
        passed1 = true;
        passed2 = false;
      }
      
    } else if (IRSensorVal2 > THRESHOLD && (IRSensorVal2 - IGNORETHRESHOLD > previous2)) {
      time2 = millis();
      if (passed1 && !passed2 && time2 - time1 < 2000) {
        Serial.println("Coming towards sensor2");
        passed2 = false;
        passed1 = false;
      } else {
        passed2 = true;
        passed1 = false;
      }  
    }
    
    delay(INTERVAL);
    previous = IRSensorVal;
    previous2 = IRSensorVal2;
}

