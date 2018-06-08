#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A2
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
int ILS = 3;       
int EtatILS = 0;
float RayonDesBras = 0.07;   
float Coef_Etalonnage = 20; 
float VitesseVent = 0;
long chrono = 0;              
long chrono_depart = 0;      
long duree_mesure = 2000;     
volatile long compteur = 0;
const int pinTemp = A0;
const int B = 3975;
int sens = 0;
#define HALL_SENSOR_1 6
#define HALL_SENSOR_2 7
#define HALL_SENSOR_3 8
void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(2, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(ILS, INPUT);
  attachInterrupt(1, impulsions, RISING);

}
void impulsions() 
{
  compteur = compteur + 1 ;
}
void loop() {
  chrono = millis();
  sensors.requestTemperatures();
  float tempe = sensors.getTempCByIndex(0);
  float temp = getTemp();
  int lux = getLux();
  float vent = getVent();
  if(isMagnet(HALL_SENSOR_1)){
    if(temp>40 || tempe>28 || lux<10 || vent>40){
      startRotation(1);
    }else{
      stopRotation();
    }
  /*}else if(isMagnet(HALL_SENSOR_2)){
    if(temp>25 || tempe>25 || lux<10 || vent>40){
      startRotation(1);
    }else if(temp<25 || tempe<25 || lux>10 || vent<40){
      startRotation(0);
    }else{
      stopRotation();
    }*/
    }else if (isMagnet(HALL_SENSOR_3)){
      if(temp<25 || tempe<25 || lux>10 || vent<40){
      startRotation(0);
    }else{
      stopRotation();
    }
    }else{
      stopRotation();
    }
    /*Serial.println(tempe);
    Serial.println(temp);
    Serial.println(lux);
    Serial.println(vent);*/
    
  }

void startRotation(int sens){
  //mettre code pour amÃ©liorer avancement d'un cotÃ© ou autre avec boolean
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
float getVent(){
  //lecture du capteur
    EtatILS = digitalRead(ILS); 
  
  if ((chrono - chrono_depart) >= duree_mesure)     // Test pour voir si temps du chrono >= durÃ©e de mesure
  { 
    VitesseVent = (2 * 3.14 * RayonDesBras * Coef_Etalonnage) * ((compteur/2) / (duree_mesure/1000))/3.6 ;   // compteur/2 (car 2 ILS/tour) et durÃ©e/1000 (car duree est en ms)
                                                                                                             // division par 3,6 pour passer des m/sec en km/h
    chrono_depart = millis();                      // remet le chrono de depart Ã  0
    compteur = 0;
  }
        
    return VitesseVent;
}
int getLux(){
  int valeur = analogRead(A4);
  return valeur/10;
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


