#include<LowPower.h>
#include<SoftwareSerial.h>
#include<SD.h>
#include<LiquidCrystal.h>
#include<SPI.h> // startar o sd na 10
#include <Adafruit_BMP085.h>
#include <DHT.h>

#define DHTPIN A2 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

SoftwareSerial hc05(0,1);
LiquidCrystal lcd(7,6,5,4,3,2);
File arq;
Adafruit_BMP085 bmp180;
DHT dht(DHTPIN, DHTTYPE);

int pinCS = 10;
char conec = 'b';
char aux = 'd';
bool soninho = true;
float temp1;
float temp2;
float mediat;
float pres;
float alt;
float umi;
float uv;
int chuva;

int UVOUT = A0; //Output from the UV sensor
int REF_3V3 = A1; //3.3V power on the Arduino board

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}

float uvIndex()
{
  
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
  return uvIntensity;

}

int chuvaIndex ()
{
  int chuva;
  chuva = analogRead(A3);
  chuva = map(chuva, 1023, 0, 0, 100);
  return chuva;
}

float mediatem(float media1, float media2)
{
  float media;
  media = ((media1 + media2)/2);
  return media;
}

void lcdTempUmi(float temp, float umi)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Temperatura: "); 
  lcd.write(temp);
  lcd.write("ºC");
  lcd.setCursor(1,0);
  lcd.write("Umidade: "); 
  lcd.write(umi);
  lcd.write("%");
}

void lcdAltPres(float alt, float pres)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Altitude: "); 
  lcd.write(alt);
  lcd.write("M");
  lcd.setCursor(1,0);
  lcd.write("Pressão: "); 
  lcd.write(pres);
  lcd.write("Pa"); 
}

void lcdUvChuva(float uv, float chuva)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Intensidade UV: "); 
  lcd.write(uv);
  lcd.write("%");
  lcd.setCursor(1,0);
  lcd.write("Chuva: "); 
  lcd.write(chuva);
  lcd.write("%");  
}

void AttLcd(float temp, float pres, float alt, float umi, float uv, int chuva)
{
  for (int i = 0; i<10; i++)
  {
    lcdTempUmi(temp,umi);
    delay(10000);
    lcdAltPres(alt,pres);
    delay(10000);
    lcdUvChuva(uv,chuva);
    delay(10000);
  }
}

void logger(float temp, float pres, float alt, float umi, float uv, int chuva)
{
  arq = SD.open("Log.txt",FILE_WRITE);
  arq.seek(EOF);
  arq.println(temp);
  arq.println(pres);
  arq.println(alt);
  arq.println(umi);
  arq.println(uv);
  arq.println(chuva);
  arq.close();
}

void uplog()
{
  arq = SD.open("Log.txt",FILE_READ);
   while (arq.available())
   {
    hc05.write(arq.read());
    delay(2);
   }
  SD.remove("Log.txt");
  arq.close();
}

void vaiDormir()
{
  conec = 'b';
  soninho = true;
  for (int i = 0; i<75; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void setup() {

  pinMode(pinCS, OUTPUT);
  dht.begin();
  bmp180.begin();
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  SD.begin();
  hc05.begin(9600);
  lcd.begin(16,2);
  Serial.begin(9600);

}

void loop() {
  
  temp1 = bmp180.readTemperature();
  temp2 = dht.readTemperature();
  mediat = mediatem(temp1,temp2);
  pres = bmp180.readPressure();
  alt =  bmp180.readAltitude();
  umi = dht.readHumidity();
  uv = uvIndex();
  chuva = chuvaIndex();

  logger(mediat,pres,alt,umi,uv,chuva);

  AttLcd(mediat,pres,alt,umi,uv,chuva);

  if(Serial.available()>0){

    conec = Serial.read();
    
    if (conec == 'a')
    {
    
      soninho = false;
      while (Serial.available()<0)
      {
        delay(100);
      }
     
      if(Serial.available()>0){
      
        conec = Serial.read();
        if (aux == 'd')
        {
          uplog();
        }
      }
      
      if (conec == 'b')
      {
        soninho = true; 
      }

    }

  }
  
  if (soninho) 
  {
    vaiDormir();
  }

}