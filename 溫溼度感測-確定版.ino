//溫溼度感測配合按鈕切換-確定版

#include<LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(9,DHT11);

int BlockFrist = 0;//LCD螢幕的起始
int BlockLast = 15;//LCD螢幕的終點

int BlockCnt;
int RowCnt;


bool lcdClean = false;

int button1 = 6;
int button2 = 7;

float humidity = 0;
float tempture = 0;

int pgmstate = 1;
int pgmstate_A = 0;

int i; 
int j ;
bool comfrim = false;

bool readstate = true;

boolean lastButtonState = LOW;
boolean reading;


void setup()
{

    
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    lcd.init();
    lcd.backlight();
    lcd.print("Wellcome!!");
    delay(1000);
    dht.begin();
    lcd.clear();
    delay(1000);
    Serial.begin(115200);
    for(int i = 0; i <=100; i++)
    {
        humidity = dht.readHumidity();
        tempture = dht.readTemperature();
        if(humidity != dht.readHumidity() || tempture != dht.readTemperature())
        {
            
            Serial.println("SENSOR偵測中斷");
            delay(500);
            i = 0;
            continue;
        }
        else
        {
            i = 99;
            Serial.println("SENSOR偵測完成");
            delay(500);
            break;
        }

    }
    
    delay(200);
    
}

void loop()
{

humidity = dht.readHumidity();
tempture = dht.readTemperature();

digitalRead(button1);
digitalRead(button2);


reading = digitalRead(button1);
debunce();
int reading1 = reading;
if(reading1 == LOW)
    {
        //Serial.println("按鈕1=");
        //Serial.println(i);
        //i = i+1;
        pgmstate++;
        if(pgmstate >2)
        {
            pgmstate = 1;
        }
    //Serial.println("PGM");
    //Serial.println(pgmstate);
    }

reading = digitalRead(button2);
debunce();
int reading2 = reading;
if(reading2 == LOW)
    {
        //Serial.println("按鈕2=");
        //Serial.println(j);
        //j = j+1;
        pgmstate--;
        if(pgmstate < 1)
        {
            pgmstate = 2;
        }
    //Serial.println("PGM");
    //Serial.println(pgmstate);
    }
    
if(humidity != dht.readHumidity() || tempture != dht.readTemperature())
{
    erroDisplay();
    //Serial.println("sensor 異常");
    delay(100);
    return;
}

if(humidity == dht.readHumidity() || humidity == dht.readTemperature())
{
    //Serial.println("sensor 正常作動");
    delay(100);
}

switch(pgmstate)
    {
    
    case 1:
    lcd.setCursor(0,0);
    lcd.print("Temprature:    ");
    lcd.setCursor(0,1);
    TempratureShow();
    break;   
    
    case 2 :
    lcd.setCursor(0,0);
    lcd.print("Humidity:      ");
    HumidityShow();
    break;

    }


}

void lcdclear()
{
for(BlockCnt = BlockFrist; BlockCnt <= BlockLast; BlockCnt++)
{
    lcd.setCursor(BlockCnt,0);
    lcd.print(" ");
    lcd.setCursor(BlockCnt,1);
    lcd.print(" ");

}


}


void debunce()//按鈕debunce的function
{

if(reading != lastButtonState)
{
delay(20);

}

if(reading == lastButtonState)
{
    reading != lastButtonState;
    delay(200);
}

}

void TempratureShow()
{
    lcd.setCursor(0,1);
    lcd.print("      ");
    lcd.setCursor(6,1);
    lcd.print(tempture);
    lcd.setCursor(11,1);
    lcd.print((char)223);
    lcd.setCursor(12,1);
    lcd.print("C   ");
    delay(100);

}


void HumidityShow()
{
    lcd.setCursor(0,1);
    lcd.print("      ");
    lcd.setCursor(6,1);
    lcd.print(humidity);
    lcd.setCursor(11,1);
    lcd.print("%    ");
    delay(100);

}

void erroDisplay()
{
    lcd.setCursor(0,0);
    lcd.print("SENSOR ERRO!!!!");
    lcd.setCursor(0,1);
    lcd.print("               ");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("PLEASE CHECK   ");
    lcd.setCursor(0,1);
    lcd.print("               ");
    delay(2000);
}