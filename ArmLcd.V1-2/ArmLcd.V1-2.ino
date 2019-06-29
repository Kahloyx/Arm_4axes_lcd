#include <VarSpeedServo.h>
#include <LiquidCrystal.h>
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

VarSpeedServo servo1;   //four servos defined
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;

int potpin1 = 1;        //Définir le port A0 d'entrée horizontale du joystick gauche
int potpin2 = 0;        //Définissez le joystick gauche pour entrer le port A1 dans le sens vertical
int potpin3 = 2;        //Définir le port d'entrée droite du joystick horizontal A2
int potpin4 = 3;        //Définissez le joystick droit pour entrer le port A3 verticalement.

int val1;
int val2;
int val3;
int val4;

static int base = 70;         //Définit l'angle initial du servo de base à 70
static int minibras = 110;    //Définir l'angle initial du servo de base à 110
static int bras = 100;        //Définir l'angle initial du grand appareil à 100
static int pince = 80;        //Définir l'angle initial du servo de patte à 80

void setup()
{
  //pinMode(L3, INPUT);
  lcd.begin(16, 2);                                             //déclaration de l'écran LCD
  lcd.clear();
  lcd.print("Initialisating..");
  servo1.attach(11);                                            //definition de l'attache de chaque servo sur les bornes 11 ect
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
  lcd.setCursor(0, 1);
  lcd.print("Please wait.....");
  servo1.write(70);                                             //base
  servo2.write(110);                                            //bras
  servo3.write(100);                                            //mini bras
  servo4.write(80);                                             //pince 80-120
  delay(timer);
  lcd.clear();
}
void loop()
{
  /////LCD Headquarters///////
  pinMode(L3, INPUT);
  boolean screencfg = analogRead(L3);
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
  if (screencfg == 0)
  {
    if ( page == 0)
    page = 1;
    else
    page = 0;
    delay(500);
  }

  /////Contrôle de base///////
  val1 = analogRead(potpin1);                                   //de 10 à 170

  if (val1 < 100)
  {
    base = base - 1;
    if (base <= 10)
    {
      base = 10;
    }
    servo1.write(base); delay(50);
  }
  if (val1 > 900)
  {
    base = base + 1;
    if (base >= 170)
    {
      base = 170;
    }
    servo1.write(base); delay(50);
  }

  //////Bras de commande de direction///////
  val2 = analogRead(potpin2);     //10 à 170

  if (val2 > 900)
  {
    minibras = minibras - 1;
    if (minibras <= 10)
    {
      minibras = 10;
    }
    servo2.write(minibras); delay(50);
  }
  if (val2 < 100)
  {
    minibras = minibras + 1;
    if (minibras >= 170)
    {
      minibras = 170;
    }
    servo2.write(minibras); delay(50);
  }

  //////Commande de direction à gros bras///////
  val3 = analogRead(potpin3);              //10 to170


  if (val3 < 100)
  {
    bras = bras - 1;
    if (bras <= 10)
    {
      bras = 10;
    }
    servo3.write(bras);

    delay(50);
  }
  if (val3 > 900)
  {
    bras = bras + 1;
    if (bras >= 170)
    {
      bras = 170;
    }
    servo3.write(bras);

    delay(50);
  }

  //////Pince///////
  val4 = analogRead(potpin4);               //80 to 130

  if (val4 < 100)
  {
    pince = pince - 1;
    if (pince <= 80)
    {
      pince = 80;
    }
    servo4.write(pince);


    delay(50);
  }
  if (val4 > 900)
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
