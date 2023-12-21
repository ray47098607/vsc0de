//DHT
#include <Adafruit_Sensor.h> //DHT先導
#include <DHT_U.h> 
#include <DHT.h>

#define dhtPin 4
#define dhtType DHT11
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

float h = dht.readHumidity();//讀取濕度
float t = dht.readTemperature();//讀取攝氏溫度
float f = dht.readTemperature(true);//讀取華氏溫度

//PZEM004Tv30
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

#if defined(ESP32)
    #error "Software Serial is not supported on the ESP32"
#endif

#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 12
#define PZEM_TX_PIN 13
#endif

SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);





void setup() {
	Serial.print("Custom Address:");
    Serial.print(pzem.readAddress(), HEX);
  	Serial.begin(115200);
	Serial.println("Humidity,Temp,Voltage,Power,Energy,Frequency,PF");

}

void loop() {
//DHT
	float h = dht.readHumidity();//讀取濕度
	float t = dht.readTemperature();//讀取攝氏溫度
	float f = dht.readTemperature(true);//讀取華氏溫度
    
	char lineHum[100];//濕度
	char lineTemp[100];//濕度

	sprintf(lineHum, "%d.%02d%%,", (int)h, (int)(h * 100) % 100);
	sprintf(lineTemp, "%d.%02d,", (int)t, (int)(t * 100) % 100);

	Serial.print(lineHum);
	Serial.print(lineTemp);


//PZEM004Tv30
	
      // Read the data from the sensor
     float voltage = pzem.voltage();
      float current = pzem.current();
      float power = pzem.power();
      float energy = pzem.energy();
      float frequency = pzem.frequency();
      float pf = pzem.pf();
  
      // Check if the data is valid
      if(isnan(voltage)){
          Serial.println("Error reading voltage");
      } else if (isnan(current)) {
          Serial.println("Error reading current");
      } else if (isnan(power)) {
          Serial.println("Error reading power");
      } else if (isnan(energy)) {
          Serial.println("Error reading energy");
      } else if (isnan(frequency)) {
          Serial.println("Error reading frequency");
      } else if (isnan(pf)) {
          Serial.println("Error reading power factor");
      } else {
        Serial.print(voltage);      Serial.print(",");
        Serial.print(current);      Serial.print(",");
        Serial.print(power);        Serial.print(",");
        Serial.print(energy);		Serial.print(",");
        Serial.print(frequency, 1); Serial.print(",");
        Serial.print(pf);
      
          // Print the values to the Serial console
          /*Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
          Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
          Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
          Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
          Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
          Serial.print("PF: ");           Serial.println(pf);*/
      }
  
      Serial.println();
      delay(2000);
}
