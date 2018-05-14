const int pinTemp = A0;
const int B = 3975;
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
  // if(used==false){
  float tempe = getTemp();
  if(isMagnet(HALL_SENSOR_1)){
    if(tempe>40){
      startRotation();
    }else{
      stopRotation();
    }
  }else if(isMagnet(HALL_SENSOR_2)){
    if(15<=tempe<25){
      startRotation();
    }else{
      stopRotation();
    }
    }else if (isMagnet(HALL_SENSOR_3)){
      if(tempe<15){
      startRotation();
    }else{
      stopRotation();
    }
    }else{
      stopRotation();
    }
  }
     /*if(tempe>40){
      }
  else if(15<=tempe<25){
    
  }
  else if(tempe<15){
    }*/
  //Serial.println(tempe);

void startRotation(){
  //mettre code pour améliorer avancement d'un coté ou autre avec boolean
  digitalWrite(4, HIGH);
digitalWrite(5, LOW);
//else LOW HIGH
}

void stopRotation(){
  if(isMagnet(HALL_SENSOR_1)){
    digitalWrite(4, LOW);
digitalWrite(5, LOW);
  }else if(isMagnet(HALL_SENSOR_3)){
    digitalWrite(4, LOW);
digitalWrite(5, LOW);
  }
  /*digitalWrite(4, LOW);
digitalWrite(5, LOW);
Serial.println("Arret");*/
//delay(time);
}
float getTemp(){
  int val = analogRead(pinTemp);

    // Determine the current resistance of the thermistor based on the sensor value.
    float resistance = (float)(1023-val)*10000/val;

    // Calculate the temperature based on the resistance value.
    float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;
    return temperature;
    // Print the temperature to the serial console.
   /* Serial.println(temperature); 
    delay(1000);*/
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

