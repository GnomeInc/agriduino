/**
 * Agriduino V 0.3
 * 
 * Requires 10 µF capacitor from 5v in to reset pin, otherwise it will lose state every time it restarts.
 */
//Temp Sensor
#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


//initialize variables
const int VAL_PROBE = 0;
const int MOISTURE_LEVEL = 500;
const int LIGHT_SENSOR = A5;

//Signal constants.  Read these 
const int READ_SIGNAL = 1;
const int WATER_SIGNAL = 2;

//watering variables.  When watering == false, it doesn't water the plants until it receives the water signal.
int motor_state = LOW;
bool watering = false;

/**
 * Begins serial input, sets pin13 LED, pin 7 to the motor transistor pin, sets up dht, and light sensor pins.
 */
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  dht.begin();

}

/**
 * Sets the Pin 13 LED to state input.
 */
void LedState(int state){
  digitalWrite(13, state);
}

/**
 * Waits for serial input.  When it receives signal to water plants, it flips a bool.
 * When it receives a signal to read sensors, it does so.
 */
void loop() {
  while(Serial.available()==0){}

  int sig = Serial.parseInt();

  if(sig == READ_SIGNAL){
    readValues();
    delay(2000);  
  }
  if(sig == WATER_SIGNAL){
    watering = true;
  }
}

/**
 * Turns motor on or off based on moisture level.  Also flips the watering bool when moisture level has reached predetermined level.
 */
void setMotor(int moisture){
  if(moisture > MOISTURE_LEVEL){
    LedState(HIGH);
    //Serial.write("Turn on Pump");
    motor_state = HIGH;
  }
  else
  {
    LedState(LOW);
    //Serial.write("Turn off pump");
    motor_state = LOW;
    watering = false;
  }
  digitalWrite(7,motor_state);
}

/**
 * Reads values from all sensors and, if watering == true, sends moisture level to setMotor() function.
 */
void readValues(){
  int moisture = analogRead(VAL_PROBE);
  int light = analogRead(LIGHT_SENSOR);
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  if(watering == true){
    setMotor(moisture); //this function also turns off the motor.
  }

  Serial.print(f);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(light);
  Serial.print(",");
  Serial.print(moisture);
  Serial.print(",");
  Serial.println(motor_state);
}
