/* WIP by kahloyx kahloyx@gmail.com 2020 
    Works with an arduino uno, 16x2 LCD non-i2c at the moment*/

#include <VarSpeedServo.h>
#include <LiquidCrystal.h>

VarSpeedServo servo1;   //Definition of 4 servos in the LibVarSpeedServo
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;

int RS = 7;
int E = 5;
int D4 = 3;
int D5 = 2;
int D6 = 1;
int D7 = 0;
int timer = 1500;
int L3 = A4;
bool page = true;

LiquidCrystal lcd (RS, E, D4, D5, D6, D7); //(rs,e,d4,d5,d6,d7)

int axeX1 = 0;        //Def of horizontal axe left joystick pin to read
int axeY1 = 1;        //Def of vertical axe left joystick pin to read
int axeX2 = 2;        //Def of horizontal axe right joystick pin to read
int axeY2 = 3;        //Def of vertical axe right joystick pin to read

int X1;                   //Buffer for sticks values
int Y1;
int X2;
int Y2;

static int base = 70;
static int minibras = 110;
static int bras = 100;
static int pince = 80;

void setup()
{
  pinMode(L3, INPUT);
  lcd.begin(16, 2);                                             //Necessary LCD init
  lcd.clear();
  lcd.print("Initialisating..");
  lcd.print("Please wait.....");
  servo1.attach(11);                                            //Physical declaration of the 45 servos to work with
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
  lcd.setCursor(0, 1);
  servo1.write(70);                                             //base
  servo2.write(110);                                            //bras
  servo3.write(100);                                            //mini bras
  servo4.write(80);                                             //pince 80-120
  delay(timer);
  lcd.clear();
}
void loop()
{
  ///////   LCD  ///////

  if (page == 0)
  {
    lcd.clear();
    lcd.print("base :");
    lcd.setCursor(7, 0);
    lcd.print(base);
    lcd.setCursor(0, 1);
    lcd.print("mini :");
    lcd.setCursor(7, 1);
    lcd.print(minibras);
    delay(88);
  }
  else
  {
    lcd.clear();
    lcd.print("bras :");
    lcd.setCursor(7, 0);
    lcd.print(bras);
    lcd.setCursor(0, 1);
    lcd.print("pince :");
    lcd.setCursor(8, 1);
    lcd.print(pince);
    delay(88);
  }
  //////////Switch lcd page 1>2 2>1//////////
  boolean swpage = analogRead(L3);
  if (swpage == false)
  {
    if ( page == false)
      page = 1;
    else
      page = 0;
    delay(500);
  }

  /////Contrôle de base///////
  X1 = analogRead(axeX1);

  if (X1 < 100)
  {
    base = base - 1;
    if (base <= 10)
    {
      base = 10;
    }
    servo1.write(base); delay(50);
  }
  if (X1 > 900)
  {
    base = base + 1;
    if (base >= 170)
    {
      base = 170;
    }
    servo1.write(base); delay(50);
  }

  //////Bras de commande de direction///////
  Y1 = analogRead(axeY1);

  if (Y1 > 900)
  {
    minibras = minibras - 1;
    if (minibras <= 10)
    {
      minibras = 10;
    }
    servo2.write(minibras); delay(50);
  }
  if (Y1 < 100)
  {
    minibras = minibras + 1;
    if (minibras >= 170)
    {
      minibras = 170;
    }
    servo2.write(minibras); delay(50);
  }

  //////Commande de direction à gros bras///////
  X2 = analogRead(axeX2);


  if (X2 < 100)
  {
    bras = bras - 1;
    if (bras <= 10)
    {
      bras = 10;
    }
    servo3.write(bras);

    delay(50);
  }
  if (X2 > 900)
  {
    bras = bras + 1;
    if (bras >= 170)
    {
      bras = 170;
    }
    servo3.write(bras);

    delay(50);
  }

  //////Hook///////
  Y2 = analogRead(axeY2);

  if (Y2 < 100)
  {
    pince = pince - 1;
    if (pince <= 80)
    {
      pince = 80;
    }
    servo4.write(pince);


    delay(50);
  }
  if (Y2 > 900)
  {
    pince = pince + 1;
    if (pince >= 130)
    {
      pince = 130;
    }
    servo4.write(pince);

    delay(50);
  }

}
