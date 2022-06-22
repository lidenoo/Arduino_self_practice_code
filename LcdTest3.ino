#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);


int BlockFitst = 0;
int BlockLast = 15;
int minSpeed = 0;
int maxSpeed = 20;

int blockCnt1;
int blockCnt2;
int delayTime;
int rate = 2;
int delayset4 = 150;



void setup()
{
pinMode(13, OUTPUT);
lcd.backlight();
lcd.init();
}

void loop()
{

for(blockCnt1 = BlockFitst;blockCnt1<=BlockLast;blockCnt1++)
{
set5();
}

}



//以下都是小function



void set1()
{
lcd.setCursor(blockCnt1,1);
lcd.print("*");
delay(delayTime);   
//依序顯示*字號  
}

void set2()
{
lcd.setCursor(blockCnt1,1);
lcd.print(" ");
delay(delayTime);
//依序顯示空白    
}

void set3()
{
    //執行顯示*字號之後再以空白字元洗掉*字號
    for(blockCnt1 = BlockFitst; blockCnt1 <= BlockLast; blockCnt1++)
    {
    set1();//執行set1內容
    }
    for(blockCnt1 = BlockFitst; blockCnt1 <= BlockLast; blockCnt1++)
    {
    set2();//執行set2內容
    }
}


void set4()//*字號依序閃滅
{
lcd.setCursor(blockCnt1,0);
lcd.print("*");
delay(delayset4);
lcd.setCursor(blockCnt1,0);
lcd.print(" ");
delay(1);


}

void set5()
{
lcd.setCursor(blockCnt1,0);
lcd.print("*");
lcd.setCursor(BlockLast-blockCnt1,1);
lcd.print("*");
delay(delayset4);
lcd.setCursor(blockCnt1,0);
lcd.print(" ");
lcd.setCursor(BlockLast-blockCnt1,1);
lcd.print(" ");
delay(1);
}