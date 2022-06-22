/*這支程式是可以按按鈕1選擇跑馬燈PROGRAM，
按下按鈕2可以執行，再按一下按鈕1可以中斷PROGRAM，
而且還能從SPEED SETTING 調整delay速度*/


#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//定義跑馬燈當中的參數
int BlockFitst = 0;//LCD螢幕的起始
int BlockLast = 15;//LCD螢幕的終點
int minSpeed = 0;
int maxSpeed = 20;

int blockCnt1;//儲存螢幕格數的變數
int blockCnt2;
int delayTime = 10;
int rate = 2;
int delayset = 90;

int set5int;
int delayoffset = 10;
//定義按鈕
int button1 = 6;
int button2 = 7;

int pgmstate = 0;
bool comfrim = false;

int pgmCnt = 3;

//按鈕Debunce參數
int button;
boolean lastButtonState = LOW;
boolean reading1;

void setup()
{
pinMode(13, OUTPUT);
pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
lcd.backlight();
lcd.init();
}

void loop()
{


reading1 = digitalRead(button1);

debunce();
if(button1 == lastButtonState == reading1)
    {
    lcd.clear();
    comfrim = false;
    pgmstate++;
    }
if(pgmstate == pgmCnt)
    {
    pgmstate = 0;
    }


reading1 = digitalRead(button2);
debunce();
if(button2 == lastButtonState == reading1 )
    {
    comfrim = true;
    lcd.clear();
    }



switch(pgmstate)
    {
    case 0://program 1
    if(comfrim == false)
    {
    lcd.setCursor(0,0);
    lcd.print("PROGRAM 1");
    break;
    }
    if(pgmstate == 0 && comfrim == true)
    {
        
        program1();
        break;
    }
    break;

    case 1://program 2
    if(comfrim == false)
    {
    lcd.setCursor(0,0);
    lcd.print("PROGRAM 2");
    break;
    }

    if(pgmstate ==1 && comfrim == true)
    {
        program2();
        break;
    }
    break;

    case 2://setting speed
    
    if(comfrim == false)
    {
    
    lcd.setCursor(0,0); 
    lcd.print("Rate Setting");
    
    break;
    }
   
        if(pgmstate ==2 && comfrim == true)
        {
        
        lcd.setCursor(0,1); 
        lcd.print("speed = ");
        lcd.setCursor(12,1); 
        lcd.print(delayTime);
        }

        if(button2 == lastButtonState == reading1)
        {
            delayTime = delayTime +10;
            if(delayTime > delayset)
            {
                delayTime =10;
            }

        }

        if(digitalRead(button1) == LOW)
        {
        
        pgmstate = pgmstate-1;
        return;    
        }
      
    break;


  
}
}
//以下是小function



void set1()
{
lcd.setCursor(blockCnt1,0);
lcd.print("*");
delay(delayTime);   
//依序顯示*字號  
}

void set2()
{
lcd.setCursor(blockCnt1,0);
lcd.print(" ");
delay(delayTime);
//依序顯示空白    
}

void set3()
{
lcd.setCursor(blockCnt1,1);
lcd.print("*");
delay(delayTime);   
//依序顯示*字號  
}


void set4()//*字號依序閃滅
{
lcd.setCursor(blockCnt1,1);
lcd.print(" ");
delay(delayTime);
//依序顯示空白  
}

void set5()
{
lcd.setCursor(blockCnt1,0);
lcd.print("*");
lcd.setCursor(BlockLast-blockCnt1,1);
lcd.print("*");
delay(delayTime*4);
lcd.setCursor(blockCnt1,0);
lcd.print(" ");
lcd.setCursor(BlockLast-blockCnt1,1);
lcd.print(" ");
delay(1);
}


void btRead()
{
digitalRead(button1);
digitalRead(button2);

}

void returnStop()
{
    if(button1 == lastButtonState == reading1)
        {
            return;
        }
}



//program1

void program1()
{
for(blockCnt1 = BlockFitst;blockCnt1<=BlockLast;blockCnt1++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set5();
}

for(blockCnt1 = BlockLast-1;blockCnt1>BlockFitst;blockCnt1--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set5();
}

}

//Program2

void program2()
{
for(blockCnt1 = BlockFitst; blockCnt1 <= BlockLast; blockCnt1++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set1();//執行set1內容
}
for(blockCnt1 = BlockFitst; blockCnt1 <= BlockLast; blockCnt1++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set2();//執行set2內容
}
for(blockCnt1 = BlockLast; blockCnt1 >= BlockFitst; blockCnt1--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set3();//執行set1內容
}
for(blockCnt1 = BlockLast; blockCnt1 >= BlockFitst; blockCnt1--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
set4();//執行set2內容
}

}



//function
void debunce()//按鈕debunce的function
{

if(reading1 != lastButtonState)
{
delay(20);

}

if(reading1 == lastButtonState)
{
    reading1 != lastButtonState;
    delay(200);
}
}

