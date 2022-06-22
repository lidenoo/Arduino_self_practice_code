//2022.02.17
//加了一個timer在裡面而且還可以選擇選單同時繼續計時，選擇到最後一頁時timer可以暫停

#include<LiquidCrystal_I2C.h>
#include <Wire.h>
#include<Timer.h>

Timer timer;

LiquidCrystal_I2C lcd(0x27,16,2);


int counter1 = 0;//紀錄分數
int counter2;//紀錄秒數

int button1 = 6;
int button2 = 7;

int pgmstate = 0;


bool pause = false;

boolean lastButtonState = LOW;
boolean reading1;
boolean reading2;


int coun;

int val= 0;
int val2 = 0;
int dt = 0;
int dt2 =0;

void setup()
{

pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
pinMode(0, INPUT);
pinMode(1, INPUT);

timer.every(990,Counter);

lcd.init();
lcd.backlight();
lcd.print("Wellcome!!");
delay(1000);
lcd.clear();
delay(200);
Serial.begin(115200);


}

void loop()
{

digitalRead(button1);
digitalRead(button2);
   
val = analogRead(0);
val2 = analogRead(1);
dt = map(val,0,1023,0,500);
dt2 = map(val2,0,1023,0,33);
//dt2 = map(val2,512,1023,0,16);


reading1 = digitalRead(button1);
debunce(reading1);

if(reading1 == lastButtonState)
    {
        lcd.clear();
        coun++;
        Serial.println(String("按鈕按了")+int(coun)+String("次"));
        Serial.println(String("PROGRAM = ")+int(pgmstate));
        //Serial.println(pause);

        pgmstate++;
        if(pgmstate >=4)
        {
            pgmstate = 3;
        }
    }

reading2 = digitalRead(button2);
debunce(reading2);

if(reading2 == lastButtonState)
    {
        lcd.clear();
        pgmstate--;
        if(pgmstate <0)
        {
            pgmstate = 0;
        }
    }

switch(pgmstate)
    {
    case 0:
    timer.update();
    lcd.setCursor(0,0);
    lcd.print("PROGRAM1");

    break;

    case 1:
    timer.update();
    lcd.setCursor(0,0);
    lcd.print("PROGRAM2");
    break;

    case 2:
    timer.update();
    lcd.setCursor(14,1);
    lcd.print(String("0")+int(counter1));
    
    if(counter1 >9)
    {
        lcd.setCursor(14,1);
        lcd.print(counter1);
    }
    break;
    case 3:
    int result;
    int x = 0;
    int setNum = 17;
    int setCursor;
    result = Caculater(dt,dt2);
    //lcd.setCursor(13,1);
    
    if(dt2<=16)
    {
        if(dt>9)
        {
            //dt2= map(val2,0,1023,0,32);
            setCursor = dt2-1;
        }
        if(dt>99)
        {
            //dt2 = map(val2,0,1023,0,31);
            setCursor = dt2-2;
        }
      
        if(dt<9){
            setCursor = dt2;
        }
            
 
            //


    }
    
    if(dt2>16)
    {
        if(dt>9)
        {
            dt2= map(val2,0,1023,0,32);
            //setCursor = dt2-1;
        }
        if(dt>99)
        {
            dt2= map(val2,0,1023,0,31);
            //setCursor = dt2-1;
        }
        //dt2 = map(val2,0,1023,0,33);
        x = 1;
        setCursor = dt2-setNum;

    }


    lcd.clear();
    lcd.setCursor(setCursor,x);
    
    lcd.print(dt);
    //Serial.println(size);
    break;

    }





delay(1);


}





void debunce(boolean readState)//按鈕debunce的function
{

if(readState!= lastButtonState)
{
delay(50);

}

if(readState == lastButtonState)
{
    readState != lastButtonState;
    delay(100);
}
}

void Counter()
{
    counter1++;
    if(counter1 >= 60)
    {
        counter1 = 0;
    }

}
int Caculater(int a,int b)
{
    int result;
    result = a+b;

    return result;


}

