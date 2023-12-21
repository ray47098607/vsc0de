#include <Adafruit_Sensor.h> //DHT先導
#include <DHT_U.h> 
#include <DHT.h>
#define dhtPin 37
#define dhtType DHT11
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

float h = dht.readHumidity();//讀取濕度
float t = dht.readTemperature();//讀取攝氏溫度
float f = dht.readTemperature(true);//讀取華氏溫度


void setup() {
    	Serial.begin(600);

pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
Serial.println("--");
Serial.println(mills());

	float h = dht.readHumidity();//讀取濕度
	float t = dht.readTemperature();//讀取攝氏溫度
	float f = dht.readTemperature(true);//讀取華氏溫度
    if (isnan(h) || isnan(t) || isnan(f)) {
		lcd.clear();  //清除螢幕
		lcd.setCursor(0, 0);   //游標移到左上角
		lcd.println("DHT ERROR!!");
		return;
	}
	char lineHum[100];//濕度
	char lineTemp[100];//濕度

	sprintf(lineHum, "Humidity: %d.%02d%%", (int)h, (int)(h * 100) % 100);
	sprintf(lineTemp, "Temp:   %d.%02d *c", (int)t, (int)(t * 100) % 100);

	Serial.print(lineHum);
	Serial.print("   ");
	Serial.println(lineTemp);

}
