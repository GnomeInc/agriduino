/**
 * Agriduino V 0.2
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

const int READ_SIGNAL = 1;

int motor_state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  dht.begin();

}

void LedState(int state){
  digitalWrite(13, state);
}

void loop() {
  while(Serial.available()==0){}

  int sig = Serial.parseInt();

  if(sig == READ_SIGNAL){
    readValues();
    delay(2000);  
  }
  
}

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
  }
  digitalWrite(7,motor_state);
}

void readValues(){
  int moisture = analogRead(VAL_PROBE);
  int light = analogRead(LIGHT_SENSOR);
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  setMotor(moisture);

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
