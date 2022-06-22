#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);


int BlockFitst = 0;
int BlockLast = 15;
int minSpeed = 0;
int maxSpeed = 20;
int blockCnt;
int delayTime;
int rate = 2;

void setup()
{
pinMode(13, OUTPUT);
lcd.backlight();
lcd.init();



}

void loop()

{

for(delayTime = minSpeed; delayTime <= maxSpeed; delayTime=delayTime+rate)
{
     set3();//執行set3內容
     if(delayTime == maxSpeed)
    {
         for(delayTime = maxSpeed; delayTime >= minSpeed; delayTime=delayTime-rate)
            {
                set3();//執行set3內容
            }
    }
}
lcd.init();//螢幕重置
delay(1);//緩衝0.001秒

}



//以下都是小function



void set1()
{
lcd.setCursor(blockCnt,1);
lcd.print("*");
delay(delayTime);   
//依序顯示*字號  
    

}
void set2()
{
lcd.setCursor(blockCnt,1);
lcd.print(" ");
delay(delayTime);
//依序顯示空白    

}

void set3()
{
    //執行顯示*字號之後再以空白字元洗掉*字號
    for(blockCnt = BlockFitst; blockCnt <= BlockLast; blockCnt++)
    {
    set1();//執行set1內容
    }
    for(blockCnt = BlockFitst; blockCnt <= BlockLast; blockCnt++)
    {
    set2();//執行set2內容
    }
}
