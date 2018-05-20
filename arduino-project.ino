const int pinTemp = A0;
const int B = 3975;
int sens = 0;
#define HALL_SENSOR_1 2
#define HALL_SENSOR_2 7
#define HALL_SENSOR_3 8
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  float temp = getTemp();
  if(isMagnet(HALL_SENSOR_1)){
    if(temp>25||15<temp<25){
      startRotation(1);
    }else{
      stopRotation();
    }
  }else if(isMagnet(HALL_SENSOR_2)){
    if(temp>25){
      startRotation(1);
    }else if(temp<15){
      startRotation(0);
    }else{
      stopRotation();
    }
    }else if (isMagnet(HALL_SENSOR_3)){
      if(temp<15||15<temp<25){
      startRotation(0);
    }else{
      stopRotation();
    }
    }else{
      stopRotation();
    }
    Serial.println(temp);
  }

void startRotation(int sens){
  //mettre code pour améliorer avancement d'un coté ou autre avec boolean
  if(sens == 0){
    digitalWrite(4, LOW);
digitalWrite(5, HIGH);
  }else if(sens == 1){
    digitalWrite(4, HIGH);
digitalWrite(5, LOW);
  }
}

void stopRotation(){
  if(isMagnet(HALL_SENSOR_1)){
    digitalWrite(4, LOW);
digitalWrite(5, LOW);
  }else if(isMagnet(HALL_SENSOR_3)){
    digitalWrite(4, LOW);
digitalWrite(5, LOW);
  }
}
float getTemp(){
  int val = analogRead(pinTemp);

    // Determine the current resistance of the thermistor based on the sensor value.
    float resistance = (float)(1023-val)*10000/val;

    // Calculate the temperature based on the resistance value.
    float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;
    return temperature;
    // Print the temperature to the serial console.
}
boolean isMagnet(uint8_t magnet)
{
  int sensorValue = digitalRead(magnet);
  if(sensorValue == LOW)//if the sensor value is LOW?
  {
    return true;//yes,return ture
  }
  else
  {
    return false;//no,return false
  }
}

