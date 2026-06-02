#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int ledPin = 8;
const float thresholdTemp = 123.0;  

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  
  sensors.begin();
  
  lcd.setCursor(0, 0);
  lcd.print("DS18B20 Temp");
  lcd.setCursor(0, 1);
  lcd.print("Threshold:123C");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures();
  
  float temperature = sensors.getTempCByIndex(0);
  
  if (temperature == -200.00) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    delay(1000);
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C     ");
  
  if (temperature >= thresholdTemp) {
    digitalWrite(ledPin, HIGH);  
    lcd.setCursor(0, 1);
    lcd.print("AAA goryacho!  ");
  } else {
    digitalWrite(ledPin, LOW);   
    lcd.setCursor(0, 1);
    lcd.print(" Normalno      ");
  }
  
  delay(1000); 
}
