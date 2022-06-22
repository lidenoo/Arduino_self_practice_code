//E-SCROLL V1.2
//作者 SHANE
//2022.02.15
//更簡化程式碼

/*這支程式是可以按按鈕1選擇跑馬燈PROGRAM，
按下按鈕2可以執行，再按一下按鈕1可以中斷PROGRAM，
而且還能從SPEED SETTING 調整delay速度*/


#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//定義跑馬燈當中的參數
int BlockFitst = 0;//LCD螢幕的起始
int BlockLast = 15;//LCD螢幕的終點


int blockCnt;//儲存螢幕格數的變數
int rowCnt;

int delayTime = 10;
int rate = 2;
int delayset = 90;


int delayoffset = 10;
//定義按鈕
int button1 = 6;
int button2 = 7;

int pgmstate = 0;
bool comfrim = false;


int pgmCnt = 4;

//按鈕Debunce參數
int button;
boolean lastButtonState = LOW;
boolean reading1;
boolean reading2;

boolean btnState1;

void setup()
{
pinMode(13, OUTPUT);
pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
lcd.backlight();
lcd.init();
lcd.setCursor(0,0);
lcd.print("Wellcome!!");
delay(1500);
lcd.clear();
lcd.print("E-SCROLL");
delay(1500);
lcd.setCursor(12,1);
lcd.print("V1.2");
delay(1500);
lcd.clear();
Serial.println("1");
}

void loop()
{


reading1 = digitalRead(button1);

debunce(reading1);
if(reading1 == lastButtonState)
    {
    lcd.clear();
    comfrim = false;
    pgmstate++;
    Serial.println(String("按鈕是PGM")+int(pgmstate)+String("狀態"));

    }
if(pgmstate == pgmCnt)
    {
    pgmstate = 0;
    }


reading2 = digitalRead(button2);
debunce(reading2);
if(reading2 == lastButtonState  )
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

    case 2://program 3
    if(comfrim == false)
    {
    lcd.setCursor(0,0);
    lcd.print("PROGRAM 3");
    break;
    }

    if(pgmstate ==2 && comfrim == true)
    {
        program3();
        break;
    }
    break;

    case 3://setting speed
    
    if(comfrim == false)
    {
    
    lcd.setCursor(0,0); 
    lcd.print("Rate Setting");
    
    break;
    }
   
        if(pgmstate ==3 && comfrim == true)
        {
        
        lcd.setCursor(0,0); 
        lcd.print("Delay");
        lcd.setCursor(2,1); 
        lcd.print("time = ");
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
//set內容



void set1()
{
lcd.setCursor(blockCnt,rowCnt);
lcd.print("*");
   
//依序顯示*字號  
}

void set2()
{
lcd.setCursor(blockCnt,rowCnt);
lcd.print(" ");

//依序顯示空白    
}




void set3()
{
lcd.setCursor(BlockLast-blockCnt,rowCnt);
lcd.print("*");


}

void set4()
{
lcd.setCursor(BlockLast-blockCnt,rowCnt);
lcd.print(" ");


}





//BUTTON 訊號讀取
void btRead()
{
digitalRead(button1);
digitalRead(button2);

}





//program1

void program1()
{
for(blockCnt = BlockFitst;blockCnt<=BlockLast;blockCnt++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set1();
rowCnt = 1;
set3();
delay(delayTime*4);
rowCnt = 0;
set2();
rowCnt = 1;
set4();
delay(delayTime);
}

for(blockCnt = BlockLast-1;blockCnt>BlockFitst;blockCnt--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set1();
rowCnt = 1;
set3();
delay(delayTime*4);
rowCnt = 0;
set2();
rowCnt = 1;
set4();
delay(delayTime);
}

}

//Program2

void program2()
{
for(blockCnt = BlockFitst; blockCnt <= BlockLast; blockCnt++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set1();//執行set1內容
delay(delayTime);
}
for(blockCnt = BlockFitst; blockCnt <= BlockLast; blockCnt++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set2();//執行set2內容
delay(delayTime);
}
for(blockCnt = BlockLast; blockCnt >= BlockFitst; blockCnt--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 1;
set1();//執行set1內容
delay(delayTime);
}
for(blockCnt = BlockLast; blockCnt >= BlockFitst; blockCnt--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 1;
set2();
delay(delayTime);
}

}

void program3()
{
for(blockCnt = BlockFitst; blockCnt <= BlockLast; blockCnt++)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set1();
rowCnt = 1;
set3();
delay(delayTime);

}
for(blockCnt = BlockLast;blockCnt>BlockFitst;blockCnt--)
{
if(digitalRead(button1) == LOW)
{
pgmstate = pgmstate-1;
return;    
}
rowCnt = 0;
set2();
rowCnt = 1;
set4();
delay(delayTime);

}


}



//function
void debunce(boolean readState)//按鈕debunce的function
{

if(readState != lastButtonState)
{
delay(20);

}

if(readState == lastButtonState)
{
    readState != lastButtonState;
    delay(200);
}
}

